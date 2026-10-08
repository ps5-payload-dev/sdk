/* Copyright (C) 2026 Mihawk
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

/* Link-time symbols only; implementations are provided by the system module. */

asm(".global sceAgcDriverGetHsOffchipParam\n"
    ".type sceAgcDriverGetHsOffchipParam @function\n"
    "sceAgcDriverGetHsOffchipParam:\n");

asm(".global sceAgcDriverGetTFRing\n"
    ".type sceAgcDriverGetTFRing @function\n"
    "sceAgcDriverGetTFRing:\n");

asm(".global sceAgcDriverGetWaitRenderingPacketSizeInDwords\n"
    ".type sceAgcDriverGetWaitRenderingPacketSizeInDwords @function\n"
    "sceAgcDriverGetWaitRenderingPacketSizeInDwords:\n");

asm(".global sceAgcDriverSetHsOffchipParam\n"
    ".type sceAgcDriverSetHsOffchipParam @function\n"
    "sceAgcDriverSetHsOffchipParam:\n");

asm(".global sceAgcDriverSetTFRing\n"
    ".type sceAgcDriverSetTFRing @function\n"
    "sceAgcDriverSetTFRing:\n");

asm(".global sceAgcDriverSubmitDcb\n"
    ".type sceAgcDriverSubmitDcb @function\n"
    "sceAgcDriverSubmitDcb:\n");

asm(".global sceAgcDriverWaitUntilSafeForRendering\n"
    ".type sceAgcDriverWaitUntilSafeForRendering @function\n"
    "sceAgcDriverWaitUntilSafeForRendering:\n");
