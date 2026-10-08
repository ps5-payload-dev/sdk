/* Copyright (C) 2026 Mihawk
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

/* Link-time symbols only; implementations are provided by the system module. */

asm(".global sceAgcCbReleaseMem\n"
    ".type sceAgcCbReleaseMem @function\n"
    "sceAgcCbReleaseMem:\n");

asm(".global sceAgcCbSetShRegisterRangeDirect\n"
    ".type sceAgcCbSetShRegisterRangeDirect @function\n"
    "sceAgcCbSetShRegisterRangeDirect:\n");

asm(".global sceAgcCreateShader\n"
    ".type sceAgcCreateShader @function\n"
    "sceAgcCreateShader:\n");

asm(".global sceAgcDcbDrawIndex\n"
    ".type sceAgcDcbDrawIndex @function\n"
    "sceAgcDcbDrawIndex:\n");

asm(".global sceAgcDcbDrawIndexAuto\n"
    ".type sceAgcDcbDrawIndexAuto @function\n"
    "sceAgcDcbDrawIndexAuto:\n");

asm(".global sceAgcDcbSetCxRegistersIndirect\n"
    ".type sceAgcDcbSetCxRegistersIndirect @function\n"
    "sceAgcDcbSetCxRegistersIndirect:\n");

asm(".global sceAgcDcbSetFlip\n"
    ".type sceAgcDcbSetFlip @function\n"
    "sceAgcDcbSetFlip:\n");

asm(".global sceAgcDcbSetIndexBuffer\n"
    ".type sceAgcDcbSetIndexBuffer @function\n"
    "sceAgcDcbSetIndexBuffer:\n");

asm(".global sceAgcDcbSetIndexCount\n"
    ".type sceAgcDcbSetIndexCount @function\n"
    "sceAgcDcbSetIndexCount:\n");

asm(".global sceAgcDcbSetIndexSize\n"
    ".type sceAgcDcbSetIndexSize @function\n"
    "sceAgcDcbSetIndexSize:\n");

asm(".global sceAgcDcbSetNumInstances\n"
    ".type sceAgcDcbSetNumInstances @function\n"
    "sceAgcDcbSetNumInstances:\n");

asm(".global sceAgcDcbSetShRegistersIndirect\n"
    ".type sceAgcDcbSetShRegistersIndirect @function\n"
    "sceAgcDcbSetShRegistersIndirect:\n");

asm(".global sceAgcDcbSetUcRegistersIndirect\n"
    ".type sceAgcDcbSetUcRegistersIndirect @function\n"
    "sceAgcDcbSetUcRegistersIndirect:\n");

asm(".global sceAgcGetRegisterDefaults\n"
    ".type sceAgcGetRegisterDefaults @function\n"
    "sceAgcGetRegisterDefaults:\n");

asm(".global sceAgcInit\n"
    ".type sceAgcInit @function\n"
    "sceAgcInit:\n");

asm(".global sceAgcLinkShaders\n"
    ".type sceAgcLinkShaders @function\n"
    "sceAgcLinkShaders:\n");

asm(".global sceAgcSuspendPoint\n"
    ".type sceAgcSuspendPoint @function\n"
    "sceAgcSuspendPoint:\n");
