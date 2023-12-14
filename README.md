# The practice part of a webinar about unit-testing in C++ with mock objects using

## Prepare

You could use attached scripts as example to install, create and start dependencies ([Git](https://git-scm.com/) and [Docker](https://www.docker.com/) are required).
Also see [.github/workflows/test.yml](./.github/workflows/test.yml) for details.

On Linux run:
```bash
./install.sh
```
on Windows run:
```bash
.\install.cmd
```

To stop database use the command:
```bash
docker-compose --file ./db/docker-compose.yml down
```

## Build

[CMake](https://cmake.org/) and C++ compiler are required.

On Linux:
```bash
mkdir build
cmake -B build -DCMAKE_TOOLCHAIN_FILE=${PWD}/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build
```

On Windows:
```bash
mkdir build
cmake -B build -DCMAKE_TOOLCHAIN_FILE=%CD%/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build
```

## Run

```bash
./build/term
```