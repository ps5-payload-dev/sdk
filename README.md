# ps5-payload-sdk
This is an SDK for developing payloads targeted at exploited PS5s running an ELF
loader, e.g., [ps5-payload-elfldr][elfldr], the [BD-J ps5-payload-loader][bdj],
or the [webkit approached from Specter][webkit]. Several artifacts in this
repository originate from the [PS5SDK][PS5SDK] project.

## Prerequisites
On Debian-flavored operating systems, you can invoke the following command to
install dependencies used by the SDK.
```console
john@localhost:ps5-payload-dev/sdk$ sudo apt-get install bash socat cmake pkg-config clang-15 lld-15
```

## Quick-start
To download and install a binary distribution for GNU/Linux:
```console
john@localhost:tmp$ wget https://github.com/ps5-payload-dev/sdk/releases/download/v0.17/ps5-payload-sdk.tar.gz
john@localhost:tmp$ mkdir -p /opt/ps5-payload-sdk-0.17/
john@localhost:tmp$ tar xvf ps5-payload-sdk.tar.gz -C /opt/ps5-payload-sdk-0.17/
```

## Building
```console
john@localhost:ps5-payload-dev/sdk$ make
john@localhost:ps5-payload-dev/sdk$ make DESTDIR=/opt/ps5-payload-sdk install
```

## Usage
```console
john@localhost:ps5-payload-dev/sdk$ export PS5_PAYLOAD_SDK=/opt/ps5-payload-sdk
john@localhost:ps5-payload-dev/sdk$ make -C samples/hello_world
john@localhost:ps5-payload-dev/sdk$ export PS5_HOST=ps5; export PS5_PORT=9021
john@localhost:ps5-payload-dev/sdk$ make -C samples/hello_world test
```

## Adding new SCE Libs
If you have decrypted sprx files that you would like to interact with, you can
build stubs for them as follows:
```console
john@localhost:ps5-payload-dev/sdk$ sudo apt-get install wget python3 python3-pyelftools
john@localhost:ps5-payload-dev/sdk$ ln -s /path/to/sprx/libSceXYZ.sprx sce_stubs/libSceXYZ.sprx
john@localhost:ps5-payload-dev/sdk$ make -C sce_stubs stubs
john@localhost:ps5-payload-dev/sdk$ make DESTDIR=/opt/ps5-payload-sdk install
```

## Reporting Bugs
If you encounter problems with the SDK, please [file a github issue][issues].
If you plan on sending pull requests which affect more than a few lines of code,
please file an issue before you start to work on you changes. This will allow us
to discuss the solution properly before you commit time and effort.

## License
Files in the include_bsd directory are licenced under BSD licences.
Unless otherwhise explicitly stated inside a file, the rest are licensed under
the GPLv3+.

[bdj]: https://github.com/john-tornblom/bdj-sdk/tree/master/samples/ps5-payload-loader
[issues]: https://github.com/ps5-payload-dev/sdk/issues/new
[elfldr]: https://github.com/ps5-payload-dev/elfldr
[PS5SDK]: https://github.com/PS5Dev/PS5SDK
[webkit]: https://github.com/Cryptogenic/PS5-IPV6-Kernel-Exploit
