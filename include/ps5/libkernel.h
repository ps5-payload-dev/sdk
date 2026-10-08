/* Copyright (C) 2026 Mihawk
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * Exported libkernel APIs used by PS5 homebrew. Error-returning SCE APIs
 * return zero on success and an SCE error code on failure, not POSIX errno.
 * Access to an exported API may still depend on the process privileges.
 */
#ifndef PS5_LIBKERNEL_H
#define PS5_LIBKERNEL_H

#include <stddef.h>
#include <pthread.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PS5_KERNEL_PROT_CPU_READ 0x01
#define PS5_KERNEL_PROT_CPU_WRITE 0x02
#define PS5_KERNEL_PROT_CPU_EXEC 0x04
#define PS5_KERNEL_PROT_GPU_READ 0x10
#define PS5_KERNEL_PROT_GPU_WRITE 0x20

#define PS5_KERNEL_MAP_FIXED 0x10

#define PS5_KERNEL_DIRECT_TYPE_CPU 12

#define PS5_KERNEL_PAGE_SIZE ((size_t)0x4000)
#define PS5_KERNEL_DIRECT_ALIGNMENT ((size_t)0x10000)

int32_t sceKernelAllocateDirectMemory(int64_t search_start, int64_t search_end, size_t length,
                                      size_t alignment, int memory_type, int64_t *physical_start);
int32_t sceKernelReleaseDirectMemory(int64_t start, size_t length);
int32_t sceKernelMapDirectMemory(void **address, size_t length, int protection, int flags,
                                 int64_t direct_start, size_t alignment);
int64_t sceKernelGetDirectMemorySize(void);
int32_t sceKernelAvailableDirectMemorySize(int64_t search_start, int64_t search_end, size_t alignment,
                                           int64_t *physical_start, size_t *available);

int32_t sceKernelMprotect(const void *address, size_t length, int protection);
int32_t sceKernelReserveVirtualRange(void **address, size_t length, int flags, size_t alignment);
int32_t sceKernelMunmap(void *address, size_t length);
int32_t sceKernelQueryMemoryProtection(void *address, void **start, void **end, uint32_t *protection);

int32_t sceKernelAvailableFlexibleMemorySize(size_t *available);
int32_t sceKernelConfiguredFlexibleMemorySize(size_t *configured);

int32_t sceKernelJitCreateSharedMemory(const char *name, size_t length, int max_protection, int *fd);
int32_t sceKernelJitCreateAliasOfSharedMemory(int fd, int max_protection, int *alias_fd);
int32_t sceKernelJitMapSharedMemory(int fd, int protection, void **address);

uint64_t sceKernelReadTsc(void);

int32_t sceKernelGetCurrentCpu(void);

int32_t scePthreadGetaffinity(pthread_t thread, uint64_t *mask);
int32_t scePthreadSetaffinity(pthread_t thread, uint64_t mask);
uint64_t sceKernelGetTscFrequency(void);

/* Set size to sizeof(struct ps5_kernel_sw_version) before querying. */
struct ps5_kernel_sw_version {
   size_t size;
   char text[0x1c];
   uint32_t version;
};
int32_t sceKernelGetSystemSwVersion(struct ps5_kernel_sw_version *version);

#ifdef __cplusplus
}
#endif

#endif
