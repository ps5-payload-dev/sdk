#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <libgen.h>

#define PATH_LDSCRIPT "/ldscripts/elf_x86_64.x"
#define PATH_LIBDIR1 "/target/lib"
#define PATH_LIBDIR2 "/target/user/homebrew/lib"
#define PATH_CRT1OBJ "/target/lib/crt1.o"

int
main(int argc, char** argv, char** envp) {
    char sdkdir[PATH_MAX-32];
    char ldscript[PATH_MAX];
    char libdir1[PATH_MAX];
    char libdir2[PATH_MAX];
    char crt1obj[PATH_MAX];
    char cmd[0x4000];
    const char* str;

    if((str=getenv("PS5_PAYLOAD_SDK"))) {
        strcpy(sdkdir, str);
    } else if((str=dirname(argv[0]))) {
        _fullpath(sdkdir, str, sizeof(sdkdir)-1);
        strcat(sdkdir, "/..");
    }

    sprintf(ldscript, " %s"PATH_LDSCRIPT, sdkdir);
    sprintf(libdir1, " %s"PATH_LIBDIR1, sdkdir);
    sprintf(libdir2, " %s"PATH_LIBDIR2, sdkdir);
    sprintf(crt1obj, " %s"PATH_CRT1OBJ, sdkdir);

    memset(cmd, 0, sizeof(cmd));
    strcat(cmd, "ld.lld");
    strcat(cmd, " -m elf_x86_64");
    strcat(cmd, " -pie");
    strcat(cmd, " --eh-frame-hdr");
    strcat(cmd, " -z max-page-size=0x4000");
    strcat(cmd, " -T");
    strcat(cmd, ldscript);
    strcat(cmd, " -L");
    strcat(cmd, libdir1);
    strcat(cmd, " -L");
    strcat(cmd, libdir2);

    for(int i=1; i<argc; i++) {
        strcat(cmd, " ");
        strcat(cmd, argv[i]);
    }

    strcat(cmd, crt1obj);

    return system(cmd);
}
