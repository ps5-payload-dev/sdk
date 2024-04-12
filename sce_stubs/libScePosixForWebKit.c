
asm(".global __wrap_access\n"
    ".type __wrap_access @function\n"
    "__wrap_access:\n");

asm(".global __wrap_clock_gettime\n"
    ".type __wrap_clock_gettime @function\n"
    "__wrap_clock_gettime:\n");

asm(".global __wrap_fchown\n"
    ".type __wrap_fchown @function\n"
    "__wrap_fchown:\n");

asm(".global __wrap_getcwd\n"
    ".type __wrap_getcwd @function\n"
    "__wrap_getcwd:\n");

asm(".global __wrap_getenv\n"
    ".type __wrap_getenv @function\n"
    "__wrap_getenv:\n");

asm(".global __wrap_link\n"
    ".type __wrap_link @function\n"
    "__wrap_link:\n");

asm(".global __wrap_lstat\n"
    ".type __wrap_lstat @function\n"
    "__wrap_lstat:\n");

asm(".global __wrap_mmap\n"
    ".type __wrap_mmap @function\n"
    "__wrap_mmap:\n");

asm(".global __wrap_readlink\n"
    ".type __wrap_readlink @function\n"
    "__wrap_readlink:\n");

asm(".global __wrap_statvfs\n"
    ".type __wrap_statvfs @function\n"
    "__wrap_statvfs:\n");

asm(".global __wrap_symlink\n"
    ".type __wrap_symlink @function\n"
    "__wrap_symlink:\n");

asm(".global arc4random\n"
    ".type arc4random @function\n"
    "arc4random:\n");

asm(".global arc4random_buf\n"
    ".type arc4random_buf @function\n"
    "arc4random_buf:\n");

asm(".global clock_gettime_np\n"
    ".type clock_gettime_np @function\n"
    "clock_gettime_np:\n");

asm(".global closedir\n"
    ".type closedir @function\n"
    "closedir:\n");

asm(".global fnmatch\n"
    ".type fnmatch @function\n"
    "fnmatch:\n");

asm(".global freeaddrinfo\n"
    ".type freeaddrinfo @function\n"
    "freeaddrinfo:\n");

asm(".global gai_strerror\n"
    ".type gai_strerror @function\n"
    "gai_strerror:\n");

asm(".global getaddrinfo\n"
    ".type getaddrinfo @function\n"
    "getaddrinfo:\n");

asm(".global getenv_np\n"
    ".type getenv_np @function\n"
    "getenv_np:\n");

asm(".global gethostbyname\n"
    ".type gethostbyname @function\n"
    "gethostbyname:\n");

asm(".global gethostbyname_r\n"
    ".type gethostbyname_r @function\n"
    "gethostbyname_r:\n");

asm(".global getnameinfo\n"
    ".type getnameinfo @function\n"
    "getnameinfo:\n");

asm(".global getservbyname\n"
    ".type getservbyname @function\n"
    "getservbyname:\n");

asm(".global isatty\n"
    ".type isatty @function\n"
    "isatty:\n");

asm(".global mkstemp\n"
    ".type mkstemp @function\n"
    "mkstemp:\n");

asm(".global mmap_np\n"
    ".type mmap_np @function\n"
    "mmap_np:\n");

asm(".global msetname\n"
    ".type msetname @function\n"
    "msetname:\n");

asm(".global opendir\n"
    ".type opendir @function\n"
    "opendir:\n");

asm(".global pthread_setname_np\n"
    ".type pthread_setname_np @function\n"
    "pthread_setname_np:\n");

asm(".global pthread_setschedparam_np\n"
    ".type pthread_setschedparam_np @function\n"
    "pthread_setschedparam_np:\n");

asm(".global readdir\n"
    ".type readdir @function\n"
    "readdir:\n");

asm(".global readdir_r\n"
    ".type readdir_r @function\n"
    "readdir_r:\n");

asm(".global setenv_np\n"
    ".type setenv_np @function\n"
    "setenv_np:\n");

asm(".global strcasestr\n"
    ".type strcasestr @function\n"
    "strcasestr:\n");

asm(".global sysinfo\n"
    ".type sysinfo @function\n"
    "sysinfo:\n");
