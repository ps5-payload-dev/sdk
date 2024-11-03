#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <libgen.h>

int
main(int argc, char** argv, char** envp) {
    char sdkdir[PATH_MAX-32];
    char ldscript[PATH_MAX];
    char cmd[0x4000];
    const char* str;

    if((str=getenv("PS5_PAYLOAD_SDK"))) {
        strcpy(sdkdir, str);
    } else if((str=dirname(argv[0]))) {
        _fullpath(sdkdir, str, sizeof(sdkdir)-1);
        strcat(sdkdir, "/..");
    }

    sprintf(ldscript, " %s/ldscripts/elf_x86_64.x", sdkdir);

    memset(cmd, 0, sizeof(cmd));
    strcat(cmd, "ld.lld");
    strcat(cmd, " -m elf_x86_64");
    strcat(cmd, " -pie");
    strcat(cmd, " --eh-frame-hdr");
    strcat(cmd, " -z max-page-size=0x4000");
    strcat(cmd, " -T");
    strcat(cmd, ldscript);

    for(int i=1; i<argc; i++) {
        strcat(cmd, " ");
        strcat(cmd, argv[i]);
    }

    return system(cmd);
}
