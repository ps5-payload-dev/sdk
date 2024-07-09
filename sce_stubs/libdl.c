
asm(".weak dlclose\n"
    ".type dlclose @function\n"
    "dlclose:\n");

asm(".weak dlerror\n"
    ".type dlerror @function\n"
    "dlerror:\n");

asm(".weak dlopen\n"
    ".type dlopen @function\n"
    "dlopen:\n");

asm(".weak dlsym\n"
    ".type dlsym @function\n"
    "dlsym:\n");
