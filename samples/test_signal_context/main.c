/* Copyright (C) 2026 Mihawk
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <inttypes.h>
#include <setjmp.h>
#include <signal.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <ucontext.h>

_Static_assert(offsetof(ucontext_t, uc_mcontext) == 64, "PS5 mcontext offset");
_Static_assert(offsetof(ucontext_t, uc_mcontext.mc_rip) == 224, "PS5 RIP offset");

static sigjmp_buf escape;
static volatile uint64_t saved_rax;
static volatile uintptr_t saved_rip;
extern void context_trigger(void);
extern const char context_fault[];

/* UD2 gives a known faulting instruction and a caller-saved register marker. */
__asm__(".text\n"
        ".global context_trigger\n"
        ".type context_trigger,@function\n"
        "context_trigger:\n"
        "movabs $0x5a17000000001234, %rax\n"
        ".global context_fault\n"
        "context_fault:\n"
        "ud2\n"
        "ret\n");

static void
handle_fault(int signal_number, siginfo_t *info, void *opaque) {
  const ucontext_t *context = opaque;
  (void)signal_number;
  (void)info;
  saved_rax = context->uc_mcontext.mc_rax;
  saved_rip = context->uc_mcontext.mc_rip;
  siglongjmp(escape, 1);
}

int
main(void) {
  struct sigaction action = {0}, previous;
  action.sa_sigaction = handle_fault;
  action.sa_flags = SA_SIGINFO;
  sigemptyset(&action.sa_mask);
  if(sigaction(SIGILL, &action, &previous) != 0) {
    perror("sigaction");
    return 1;
  }
  if(sigsetjmp(escape, 1) == 0) {
    context_trigger();
  }
  if(sigaction(SIGILL, &previous, NULL) != 0) {
    perror("restore sigaction");
    return 1;
  }
  printf("RAX=%016" PRIx64 " RIP=%" PRIxPTR " expected RIP=%" PRIxPTR "\n",
         saved_rax, saved_rip, (uintptr_t)context_fault);
  return saved_rax != UINT64_C(0x5a17000000001234) ||
         saved_rip != (uintptr_t)context_fault;
}
