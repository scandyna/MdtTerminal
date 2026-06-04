[[_TOC_]]

# Get the source code

Get the sources:
```bash
git clone https://gitlab.com/scandyna/mdtterminal.git
```

# Build MdtTerminal

This section describes how to build
to work on MdtTerminal.

Create a build directory and cd to it:
```bash
mkdir build
cd build
```

## Install the dependencies

The recommended way is to use Conan to install the dependencies.
The examples are based on that.

Note: there is a `conanfile.py` at the root of the project tree.
This file is only used to install dependencies to work on MdtTerminal.
To create Conan packages, see [README](packaging/conan/README.md) in the conan packaging folder.

### Using Conan profiles

When using Conan for dependency management,
it is recommended to use Conan profiles.
This permits to have personal binary repository,
avoiding to recompile everything every time.

This requires modifications in the `settings_user.yml` Conan configuration,
and also some profile files.
See my [conan-config repository](https://gitlab.com/scandyna/conan-config) for more informations.

Some following sections will rely on Conan profiles.

### Conan install command

```bash
conan install --output-folder . --profile:build $CONAN_PROFILE --profile:host $CONAN_PROFILE --settings:build build_type=Release --settings:host build_type=$BUILD_TYPE --options:host "&:shared=$BUILD_SHARED_LIBS" --options:host "&:enable_serialport_userspace_usb_support=True"  ..
```

## Build MdtTerminal

If dependencies are managed by Conan,
update the environment of the current shell for the build:
```bash
source conanbuild.sh
```

Configure the project:
```bash
cmake -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTS=ON -DBUILD_BENCHMARKS=ON -DBUILD_EXAMPLES=ON ..
```

Maybe adjust some settings:
```bash
cmake-gui .
```

Build:
```bash
cmake --build . --config $BUILD_TYPE -j4
```

Restore the environment for the build (if dependencies are managed by Conan):
```bash
source deactivate_conanbuild.sh
```
Note: once the project was completely configured,
the environment for the build should not be needed anymore.


If dependencies are managed by Conan,
update the environment of the current shell to run the tests:
```bash
source conanrun.sh
```
Note: the environment to run the tests will probably be required everytime.
[mdt-cmake-modules](https://gitlab.com/scandyna/mdt-cmake-modules)
provides a helper that build an environment with CMake to execute the tests,
but its currently not working.
For details, see: https://gitlab.com/scandyna/mdt-cmake-modules/-/issues/12

To run the tests:
```bash
ctest . --output-on-failure -C $BUILD_TYPE -j4
```

Restore the environment (if dependencies are managed by Conan):
```bash
source deactivate_conanrun.sh
```
