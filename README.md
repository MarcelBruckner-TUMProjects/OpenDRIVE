# OpenDRIVE

- [See the project website of Providentia++](https://innovation-mobility.com/en)
- [See the overview repository for general information about my Guided Research](https://github.com/Brucknem/GuidedResearch)
- [See the Static Calibration project that uses the parser](https://github.com/Brucknem/StaticCalibration)
- [See the website for information and evaluation results of the project](https://brucknem.github.io/StaticCalibration)

***

# Overview

This serves as an OpenDRIVE 1.4 parser for my [Guided Research](https://github.com/Brucknem/GuidedResearch) at the
[Providentia++](https://innovation-mobility.com/en) project. The parser extracts the world positions of landmarks from
the OpenDRIVE HD maps that are used within the project.

***

# Setup

Before running any code you have to download the OpenDRIVE V1.4 standard by _VIRES Simulationstechnologie GmbH_ and use
the XSD schema to generate c++ data bindings.

To make this process easier there is the `bootstrap.sh` script in `extern/standard`.  
You have to run it from within the `extern/standard` directory and follow the instructions to download and generate the
data bindings.

***

# Running in Standalone Mode

### See below for the necessary dependencies.

### Compiling

```shell
mkdir build && cd build
cmake ..
cmake --build . -j8
```

#### CMake Configure Options

```shell
# Default is OFF for all options

-DWITH_TESTS=ON/OFF     # Build with tests.
```

### Running

```shell
./app/Converter -h  # Prints the help message.
                    # See it for the required input data and further usage.
```

### Testing

```shell
ctest --verbose
```

***

# Dependencies

Install these on your system:

- [Code Synthesis](https://www.codesynthesis.com/products/xsd/download.xhtml)
- [Xerces-context++](https://xerces.apache.org/xerces-c/download.cgi)
- [PROJ](https://proj.org/)

To facilitate the setup of the dependencies you can run the installation script `extern/dependencies.sh`.

## Internal Dependencies

These dependencies are pulled by CMake when the project is built. You `do not` have to install them manually.

- [GoogleTest](https://github.com/google/googletest) `# Only built if compiling with -DWITH_TESTS=ON`
- [YAML-CPP](https://github.com/jbeder/yaml-cpp.git)

***

# Known Issues

***

### XMLNS Attribute

The parser fails if there is the `xmlns` attribute set.

### Workaround

Change `<OpenDRIVE xmlns="http://www.opendrive.org">` to `<OpenDRIVE>`

***