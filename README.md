# ps5-payload-sdk
This is an SDK for developing payloads targeted at exploited PS5s. ELF loaders
known to work include:
- [ps5-payload-elfldr][elfldr]
- [ps5-payload-websrv][websrv]
- [bdj-ipv6-hen][bdj-ipv6-hen]
- [elfloader][elfloader] via [ps5-jar-loader]
- [remote_lua_loader][remote_lua_loader]

Several artifacts in this repository originate from the [PS5SDK][PS5SDK] project.

## Prerequisites
On Debian-flavored operating systems, you can invoke the following commands to
install dependencies used by the SDK.
```console
john@localhost:ps5-payload-dev/sdk$ sudo apt-get update && sudo apt-get upgrade # optional
john@localhost:ps5-payload-dev/sdk$ sudo apt-get install bash clang-18 lld-18 wget # required
john@localhost:ps5-payload-dev/sdk$ sudo apt-get install socat cmake meson pkg-config python3 python3-pyelftools # optional
```

If you are using Fedora, you can install dependencies as follows (tested with version 41):
```console
john@localhost:ps5-payload-dev/sdk$ sudo dnf install bash llvm-devel clang lld wget # required
john@localhost:ps5-payload-dev/sdk$ sudo dnf install socat cmake meson pkg-config python3 python3-pyelftools # optional
```

If you are using macOS, you can install them using the [Homebrew Package Manager][macos-brew] (tested with macOS Sequoia):
```console
john@localhost:ps5-payload-dev/sdk$ brew install llvm@18 wget # required
john@localhost:ps5-payload-dev/sdk$ export LLVM_CONFIG=/opt/homebrew/opt/llvm@18/bin/llvm-config # required
john@localhost:ps5-payload-dev/sdk$ brew install socat cmake meson python && pip3 install pyelftools # optional
```

## Quick-start
You can download a binary distribution of the SDK from [the latest release page][latest-rel],
then install it to your local storage, e.g,
```console
john@localhost:tmp$ wget https://github.com/ps5-payload-dev/sdk/releases/latest/download/ps5-payload-sdk.zip
john@localhost:tmp$ sudo unzip -d /opt ps5-payload-sdk.zip
```
Assuming you have all the prerequisites and you are on a POSIX system,
the binary distribution should work regardless of CPU architecture, e.g., x86_64, aarch64.

## Usage
```console
john@localhost:ps5-payload-dev/sdk$ export PS5_PAYLOAD_SDK=/opt/ps5-payload-sdk
john@localhost:ps5-payload-dev/sdk$ make -C samples/hello_world
john@localhost:ps5-payload-dev/sdk$ export PS5_HOST=ps5; export PS5_PORT=9021
john@localhost:ps5-payload-dev/sdk$ make -C samples/hello_world test
```

## Building the SDK
```console
john@localhost:ps5-payload-dev/sdk$ sudo make DESTDIR=/opt/ps5-payload-sdk install
john@localhost:ps5-payload-dev/sdk$ export PS5_PAYLOAD_SDK=/opt/ps5-payload-sdk
john@localhost:ps5-payload-dev/sdk$ sudo -E ./libcxx.sh # fetch, build, and install libcxx
```

## Headers
The SDK installs its headers under `$PS5_PAYLOAD_SDK/target/include` from three
sources in `include/`:

- `ps5/` - the SDK's own PS5-specific headers: `kernel.h`, `klog.h`, `mdbg.h`,
  `iommu.h`, `nid.h` and `payload.h`. These are the core SDK API.
- `freebsd/` - a full copy of FreeBSD's userland include tree (BSD-licensed).
  It provides the standard C library headers (`stdio.h`, `stdlib.h`, `string.h`,
  `sys/*`, `net/*`, `arpa/*`, ...) that the SDK's libc implements.
- `khronos/` - EGL and OpenGL ES 2.0 headers for graphics payloads.

Because the `freebsd/` tree is carried wholesale, it also contains
kernel-internal headers that are not part of the userland API, e.g. the
ipfilter family (`netinet/ip_*.h`) and `dev/`, `fs/`, `vm/`, `geom/`,
`net80211/`, `rdma/`, `infiniband/`. Those are there only to keep the copy
complete; they are neither used by the SDK nor needed for payload development.
Stick to the standard C library headers plus `ps5/`.

C++ is supported. Build libc++ for the target with `./libcxx.sh`, then see
`samples/hello_cxx` and `samples/hello_cxx23` for examples.

## Adding new SCE Libs
If you have decrypted sprx files that you would like to interact with, you can
build stubs for them as follows (Make sure you have already installed the optional dependencies for your OS):
```console
john@localhost:ps5-payload-dev/sdk$ ln -s /path/to/sprx/libSceXYZ.sprx sce_stubs/libSceXYZ.sprx
john@localhost:ps5-payload-dev/sdk$ make -C sce_stubs stubs
john@localhost:ps5-payload-dev/sdk$ sudo make DESTDIR=/opt/ps5-payload-sdk install
```

## Reporting Bugs
If you encounter problems with the SDK, please [file a github issue][issues].
If you plan on sending pull requests which affect more than a few lines of code,
please file an issue before you start to work on you changes. This will allow us
to discuss the solution properly before you commit time and effort.

## License
Files in the folder include/freebsd are licenced under BSD licences.
Unless otherwhise explicitly stated inside a file, the rest are licensed under
the GPLv3+.

[issues]: https://github.com/ps5-payload-dev/sdk/issues/new
[latest-rel]: https://github.com/ps5-payload-dev/sdk/releases/latest
[elfldr]: https://github.com/ps5-payload-dev/elfldr
[websrv]: https://github.com/ps5-payload-dev/websrv
[bdj-ipv6-hen]: https://github.com/ps5-payload-dev/bdj-ipv6-hen
[remote_lua_loader]: https://github.com/shahrilnet/remote_lua_loader
[elfloader]: https://github.com/cryonumb/elfloader
[ps5-jar-loader]: https://github.com/hammer-83/ps5-jar-loader
[PS5SDK]: https://github.com/PS5Dev/PS5SDK
[macos-brew]: https://brew.sh
