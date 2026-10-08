/* Copyright (C) 2026 Mihawk
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <stdio.h>

/* Only addresses are used here; this sample does not call these functions. */
extern void sceAgcCbReleaseMem(void);
extern void sceAgcCbSetShRegisterRangeDirect(void);
extern void sceAgcCreateShader(void);
extern void sceAgcDcbDrawIndex(void);
extern void sceAgcDcbDrawIndexAuto(void);
extern void sceAgcDcbSetCxRegistersIndirect(void);
extern void sceAgcDcbSetFlip(void);
extern void sceAgcDcbSetIndexBuffer(void);
extern void sceAgcDcbSetIndexCount(void);
extern void sceAgcDcbSetIndexSize(void);
extern void sceAgcDcbSetNumInstances(void);
extern void sceAgcDcbSetShRegistersIndirect(void);
extern void sceAgcDcbSetUcRegistersIndirect(void);
extern void sceAgcGetRegisterDefaults(void);
extern void sceAgcInit(void);
extern void sceAgcLinkShaders(void);
extern void sceAgcSuspendPoint(void);
extern void sceAgcDriverGetHsOffchipParam(void);
extern void sceAgcDriverGetTFRing(void);
extern void sceAgcDriverGetWaitRenderingPacketSizeInDwords(void);
extern void sceAgcDriverSetHsOffchipParam(void);
extern void sceAgcDriverSetTFRing(void);
extern void sceAgcDriverSubmitDcb(void);
extern void sceAgcDriverWaitUntilSafeForRendering(void);

static const struct {
  const char *name;
  void (*address)(void);
} imports[] = {
  {"sceAgcCbReleaseMem", sceAgcCbReleaseMem},
  {"sceAgcCbSetShRegisterRangeDirect", sceAgcCbSetShRegisterRangeDirect},
  {"sceAgcCreateShader", sceAgcCreateShader},
  {"sceAgcDcbDrawIndex", sceAgcDcbDrawIndex},
  {"sceAgcDcbDrawIndexAuto", sceAgcDcbDrawIndexAuto},
  {"sceAgcDcbSetCxRegistersIndirect", sceAgcDcbSetCxRegistersIndirect},
  {"sceAgcDcbSetFlip", sceAgcDcbSetFlip},
  {"sceAgcDcbSetIndexBuffer", sceAgcDcbSetIndexBuffer},
  {"sceAgcDcbSetIndexCount", sceAgcDcbSetIndexCount},
  {"sceAgcDcbSetIndexSize", sceAgcDcbSetIndexSize},
  {"sceAgcDcbSetNumInstances", sceAgcDcbSetNumInstances},
  {"sceAgcDcbSetShRegistersIndirect", sceAgcDcbSetShRegistersIndirect},
  {"sceAgcDcbSetUcRegistersIndirect", sceAgcDcbSetUcRegistersIndirect},
  {"sceAgcGetRegisterDefaults", sceAgcGetRegisterDefaults},
  {"sceAgcInit", sceAgcInit},
  {"sceAgcLinkShaders", sceAgcLinkShaders},
  {"sceAgcSuspendPoint", sceAgcSuspendPoint},
  {"sceAgcDriverGetHsOffchipParam", sceAgcDriverGetHsOffchipParam},
  {"sceAgcDriverGetTFRing", sceAgcDriverGetTFRing},
  {"sceAgcDriverGetWaitRenderingPacketSizeInDwords", sceAgcDriverGetWaitRenderingPacketSizeInDwords},
  {"sceAgcDriverSetHsOffchipParam", sceAgcDriverSetHsOffchipParam},
  {"sceAgcDriverSetTFRing", sceAgcDriverSetTFRing},
  {"sceAgcDriverSubmitDcb", sceAgcDriverSubmitDcb},
  {"sceAgcDriverWaitUntilSafeForRendering", sceAgcDriverWaitUntilSafeForRendering},
};

int
main(void) {
  for(unsigned i = 0; i < sizeof(imports) / sizeof(imports[0]); i++) {
    printf("%s: %p\n", imports[i].name, (void *)imports[i].address);
    if(!imports[i].address) {
      return 1;
    }
  }
  return 0;
}
