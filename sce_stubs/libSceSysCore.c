
asm(".global _sceApplicationGetAppId\n"
    ".type _sceApplicationGetAppId @function\n"
    "_sceApplicationGetAppId:\n");

asm(".global sceApplicationAddProcess2\n"
    ".type sceApplicationAddProcess2 @function\n"
    "sceApplicationAddProcess2:\n");

asm(".global sceApplicationBeginSclkChange\n"
    ".type sceApplicationBeginSclkChange @function\n"
    "sceApplicationBeginSclkChange:\n");

asm(".global sceApplicationBlockingKill2\n"
    ".type sceApplicationBlockingKill2 @function\n"
    "sceApplicationBlockingKill2:\n");

asm(".global sceApplicationBlockingKill3\n"
    ".type sceApplicationBlockingKill3 @function\n"
    "sceApplicationBlockingKill3:\n");

asm(".global sceApplicationContinue\n"
    ".type sceApplicationContinue @function\n"
    "sceApplicationContinue:\n");

asm(".global sceApplicationCrashSyscore\n"
    ".type sceApplicationCrashSyscore @function\n"
    "sceApplicationCrashSyscore:\n");

asm(".global sceApplicationCrashSystemProcess\n"
    ".type sceApplicationCrashSystemProcess @function\n"
    "sceApplicationCrashSystemProcess:\n");

asm(".global sceApplicationEndSclkChange\n"
    ".type sceApplicationEndSclkChange @function\n"
    "sceApplicationEndSclkChange:\n");

asm(".global sceApplicationExitSpawn\n"
    ".type sceApplicationExitSpawn @function\n"
    "sceApplicationExitSpawn:\n");

asm(".global sceApplicationExitSpawn2\n"
    ".type sceApplicationExitSpawn2 @function\n"
    "sceApplicationExitSpawn2:\n");

asm(".global sceApplicationExitSpawn3\n"
    ".type sceApplicationExitSpawn3 @function\n"
    "sceApplicationExitSpawn3:\n");

asm(".global sceApplicationFinalize\n"
    ".type sceApplicationFinalize @function\n"
    "sceApplicationFinalize:\n");

asm(".global sceApplicationGetAppInfoByAppId\n"
    ".type sceApplicationGetAppInfoByAppId @function\n"
    "sceApplicationGetAppInfoByAppId:\n");

asm(".global sceApplicationGetAppPackageInfoForCoredump\n"
    ".type sceApplicationGetAppPackageInfoForCoredump @function\n"
    "sceApplicationGetAppPackageInfoForCoredump:\n");

asm(".global sceApplicationGetCompiledSdkVersionByAppId\n"
    ".type sceApplicationGetCompiledSdkVersionByAppId @function\n"
    "sceApplicationGetCompiledSdkVersionByAppId:\n");

asm(".global sceApplicationGetCoredumpDirAndFileName\n"
    ".type sceApplicationGetCoredumpDirAndFileName @function\n"
    "sceApplicationGetCoredumpDirAndFileName:\n");

asm(".global sceApplicationGetCoredumpState\n"
    ".type sceApplicationGetCoredumpState @function\n"
    "sceApplicationGetCoredumpState:\n");

asm(".global sceApplicationGetCpuUsage\n"
    ".type sceApplicationGetCpuUsage @function\n"
    "sceApplicationGetCpuUsage:\n");

asm(".global sceApplicationGetCpuUsage2\n"
    ".type sceApplicationGetCpuUsage2 @function\n"
    "sceApplicationGetCpuUsage2:\n");

asm(".global sceApplicationGetDbgExecutablePath\n"
    ".type sceApplicationGetDbgExecutablePath @function\n"
    "sceApplicationGetDbgExecutablePath:\n");

asm(".global sceApplicationGetMode\n"
    ".type sceApplicationGetMode @function\n"
    "sceApplicationGetMode:\n");

asm(".global sceApplicationGetProcs\n"
    ".type sceApplicationGetProcs @function\n"
    "sceApplicationGetProcs:\n");

asm(".global sceApplicationGetShellCoreAppId\n"
    ".type sceApplicationGetShellCoreAppId @function\n"
    "sceApplicationGetShellCoreAppId:\n");

asm(".global sceApplicationGetStateForDebugger\n"
    ".type sceApplicationGetStateForDebugger @function\n"
    "sceApplicationGetStateForDebugger:\n");

asm(".global sceApplicationInitialize\n"
    ".type sceApplicationInitialize @function\n"
    "sceApplicationInitialize:\n");

asm(".global sceApplicationInitializeForShellCore\n"
    ".type sceApplicationInitializeForShellCore @function\n"
    "sceApplicationInitializeForShellCore:\n");

asm(".global sceApplicationIsCrashReportBeingProcessed\n"
    ".type sceApplicationIsCrashReportBeingProcessed @function\n"
    "sceApplicationIsCrashReportBeingProcessed:\n");

asm(".global sceApplicationIsPrimaryProcess\n"
    ".type sceApplicationIsPrimaryProcess @function\n"
    "sceApplicationIsPrimaryProcess:\n");

asm(".global sceApplicationIsResumable\n"
    ".type sceApplicationIsResumable @function\n"
    "sceApplicationIsResumable:\n");

asm(".global sceApplicationIsSuspendable\n"
    ".type sceApplicationIsSuspendable @function\n"
    "sceApplicationIsSuspendable:\n");

asm(".global sceApplicationKickCoredump\n"
    ".type sceApplicationKickCoredump @function\n"
    "sceApplicationKickCoredump:\n");

asm(".global sceApplicationKickCoredump2\n"
    ".type sceApplicationKickCoredump2 @function\n"
    "sceApplicationKickCoredump2:\n");

asm(".global sceApplicationKickCoredump3\n"
    ".type sceApplicationKickCoredump3 @function\n"
    "sceApplicationKickCoredump3:\n");

asm(".global sceApplicationKill\n"
    ".type sceApplicationKill @function\n"
    "sceApplicationKill:\n");

asm(".global sceApplicationLocalProcessKill\n"
    ".type sceApplicationLocalProcessKill @function\n"
    "sceApplicationLocalProcessKill:\n");

asm(".global sceApplicationLocalProcessKill2\n"
    ".type sceApplicationLocalProcessKill2 @function\n"
    "sceApplicationLocalProcessKill2:\n");

asm(".global sceApplicationLocalProcessResume\n"
    ".type sceApplicationLocalProcessResume @function\n"
    "sceApplicationLocalProcessResume:\n");

asm(".global sceApplicationLocalProcessSuspend\n"
    ".type sceApplicationLocalProcessSuspend @function\n"
    "sceApplicationLocalProcessSuspend:\n");

asm(".global sceApplicationNotifyCoredumpRequestEnd\n"
    ".type sceApplicationNotifyCoredumpRequestEnd @function\n"
    "sceApplicationNotifyCoredumpRequestEnd:\n");

asm(".global sceApplicationNotifyCoredumpRequestProgress\n"
    ".type sceApplicationNotifyCoredumpRequestProgress @function\n"
    "sceApplicationNotifyCoredumpRequestProgress:\n");

asm(".global sceApplicationNotifyUnmountForExitSpawn\n"
    ".type sceApplicationNotifyUnmountForExitSpawn @function\n"
    "sceApplicationNotifyUnmountForExitSpawn:\n");

asm(".global sceApplicationNotifyVshMainOnStandby\n"
    ".type sceApplicationNotifyVshMainOnStandby @function\n"
    "sceApplicationNotifyVshMainOnStandby:\n");

asm(".global sceApplicationNotifyVshReady\n"
    ".type sceApplicationNotifyVshReady @function\n"
    "sceApplicationNotifyVshReady:\n");

asm(".global sceApplicationOnAllResourceReleased\n"
    ".type sceApplicationOnAllResourceReleased @function\n"
    "sceApplicationOnAllResourceReleased:\n");

asm(".global sceApplicationRaiseException\n"
    ".type sceApplicationRaiseException @function\n"
    "sceApplicationRaiseException:\n");

asm(".global sceApplicationRaiseExceptionToLocalPid\n"
    ".type sceApplicationRaiseExceptionToLocalPid @function\n"
    "sceApplicationRaiseExceptionToLocalPid:\n");

asm(".global sceApplicationRaiseExceptionToPid\n"
    ".type sceApplicationRaiseExceptionToPid @function\n"
    "sceApplicationRaiseExceptionToPid:\n");

asm(".global sceApplicationRequestToChangeRenderingMode\n"
    ".type sceApplicationRequestToChangeRenderingMode @function\n"
    "sceApplicationRequestToChangeRenderingMode:\n");

asm(".global sceApplicationRestore\n"
    ".type sceApplicationRestore @function\n"
    "sceApplicationRestore:\n");

asm(".global sceApplicationResume\n"
    ".type sceApplicationResume @function\n"
    "sceApplicationResume:\n");

asm(".global sceApplicationSave\n"
    ".type sceApplicationSave @function\n"
    "sceApplicationSave:\n");

asm(".global sceApplicationSendDebugSpawnResult2\n"
    ".type sceApplicationSendDebugSpawnResult2 @function\n"
    "sceApplicationSendDebugSpawnResult2:\n");

asm(".global sceApplicationSendResultOfDebuggerKillRequest\n"
    ".type sceApplicationSendResultOfDebuggerKillRequest @function\n"
    "sceApplicationSendResultOfDebuggerKillRequest:\n");

asm(".global sceApplicationSendResultOfDebuggerRestoreRequest\n"
    ".type sceApplicationSendResultOfDebuggerRestoreRequest @function\n"
    "sceApplicationSendResultOfDebuggerRestoreRequest:\n");

asm(".global sceApplicationSendResultOfDebuggerResumeRequest\n"
    ".type sceApplicationSendResultOfDebuggerResumeRequest @function\n"
    "sceApplicationSendResultOfDebuggerResumeRequest:\n");

asm(".global sceApplicationSendResultOfDebuggerSaveRequest\n"
    ".type sceApplicationSendResultOfDebuggerSaveRequest @function\n"
    "sceApplicationSendResultOfDebuggerSaveRequest:\n");

asm(".global sceApplicationSendResultOfDebuggerSuspendRequest\n"
    ".type sceApplicationSendResultOfDebuggerSuspendRequest @function\n"
    "sceApplicationSendResultOfDebuggerSuspendRequest:\n");

asm(".global sceApplicationSendResultOfDebuggerTitleIdLaunchRequest\n"
    ".type sceApplicationSendResultOfDebuggerTitleIdLaunchRequest @function\n"
    "sceApplicationSendResultOfDebuggerTitleIdLaunchRequest:\n");

asm(".global sceApplicationSetApplicationFocus\n"
    ".type sceApplicationSetApplicationFocus @function\n"
    "sceApplicationSetApplicationFocus:\n");

asm(".global sceApplicationSetControllerFocus\n"
    ".type sceApplicationSetControllerFocus @function\n"
    "sceApplicationSetControllerFocus:\n");

asm(".global sceApplicationSetControllerFocusPermissionToSubProcess\n"
    ".type sceApplicationSetControllerFocusPermissionToSubProcess @function\n"
    "sceApplicationSetControllerFocusPermissionToSubProcess:\n");

asm(".global sceApplicationSetMemoryPstate\n"
    ".type sceApplicationSetMemoryPstate @function\n"
    "sceApplicationSetMemoryPstate:\n");

asm(".global sceApplicationSignalShellCoreHeartBeat\n"
    ".type sceApplicationSignalShellCoreHeartBeat @function\n"
    "sceApplicationSignalShellCoreHeartBeat:\n");

asm(".global sceApplicationSpawn2\n"
    ".type sceApplicationSpawn2 @function\n"
    "sceApplicationSpawn2:\n");

asm(".global sceApplicationSuspend\n"
    ".type sceApplicationSuspend @function\n"
    "sceApplicationSuspend:\n");

asm(".global sceApplicationSuspendSystemForDebugger\n"
    ".type sceApplicationSuspendSystemForDebugger @function\n"
    "sceApplicationSuspendSystemForDebugger:\n");

asm(".global sceApplicationSwitchToBaseMode\n"
    ".type sceApplicationSwitchToBaseMode @function\n"
    "sceApplicationSwitchToBaseMode:\n");

asm(".global sceApplicationSwitchToNeoMode\n"
    ".type sceApplicationSwitchToNeoMode @function\n"
    "sceApplicationSwitchToNeoMode:\n");

asm(".global sceApplicationSwitchToNeoMode2\n"
    ".type sceApplicationSwitchToNeoMode2 @function\n"
    "sceApplicationSwitchToNeoMode2:\n");

asm(".global sceApplicationSwitchToPprNativeMode\n"
    ".type sceApplicationSwitchToPprNativeMode @function\n"
    "sceApplicationSwitchToPprNativeMode:\n");

asm(".global sceApplicationSystemReboot\n"
    ".type sceApplicationSystemReboot @function\n"
    "sceApplicationSystemReboot:\n");

asm(".global sceApplicationSystemShutdown2\n"
    ".type sceApplicationSystemShutdown2 @function\n"
    "sceApplicationSystemShutdown2:\n");

asm(".global sceApplicationSystemSuspend\n"
    ".type sceApplicationSystemSuspend @function\n"
    "sceApplicationSystemSuspend:\n");

asm(".global sceApplicationSystemSuspend2\n"
    ".type sceApplicationSystemSuspend2 @function\n"
    "sceApplicationSystemSuspend2:\n");

asm(".global sceApplictionGetStateForDebugger\n"
    ".type sceApplictionGetStateForDebugger @function\n"
    "sceApplictionGetStateForDebugger:\n");

asm(".global sceSysCoreGetEventCount\n"
    ".type sceSysCoreGetEventCount @function\n"
    "sceSysCoreGetEventCount:\n");

asm(".global sceSysCoreReceiveEvent\n"
    ".type sceSysCoreReceiveEvent @function\n"
    "sceSysCoreReceiveEvent:\n");
