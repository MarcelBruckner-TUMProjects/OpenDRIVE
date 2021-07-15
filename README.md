# OpenDRIVE

- [OpenDRIVE 1.6 standard definition](https://www.asam.net/index.php?eID=dumpFile&t=f&f=3495&token=56b15ffd9dfe23ad8f759523c806fc1f1a90a0e8#)
- [See the project website of Providentia++](https://innovation-mobility.com/en)
- [See the overview repository for general information about my Guided Research](https://github.com/Brucknem/GuidedResearch)
- [See the Static Calibration project that uses the parser](https://github.com/Brucknem/StaticCalibration)
- [See the website for information and evaluation results of the project](https://brucknem.github.io/StaticCalibration)

***

# Overview

This serves as an OpenDRIVE parser for my [Guided Research](https://github.com/Brucknem/GuidedResearch) at the
[Providentia++](https://innovation-mobility.com/en) project. The parser extracts the world positions of landmarks from
the OpenDRIVE HD maps that are used within the project.

***

# Setup

Before running any code, you have to download an OpenDRIVE standard. We then generate C++ data bindings for the XSD
files.

For instructions and convenience scripts see:

- OpenDRIVE 1.4: `extern/opendrive_1_4/bootstrap.sh`
- OpenDRIVE 1.6: `extern/opendrive_1_6/bootstrap.sh`

***

# Get Help

I try to be as close as possible to the naming of the classes and attributes specified in
the [OpenDRIVE 1.6 standard](https://www.asam.net/index.php?eID=dumpFile&t=f&f=3495&token=56b15ffd9dfe23ad8f759523c806fc1f1a90a0e8#)
.  
If there are any inconsistencies in the comments or unclear code, please refer to
the [OpenDRIVE 1.6 standard](https://www.asam.net/index.php?eID=dumpFile&t=f&f=3495&token=56b15ffd9dfe23ad8f759523c806fc1f1a90a0e8#)
.

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

-DOPENDRIVE_1_4=ON/OFF  # Build with support for the OpenDRIVE 1.4 standard.

-DOPENDRIVE_1_6=ON/OFF  # Build with support for the OpenDRIVE 1.6 standard.
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

| Dependency | Usage | Installation | Required | 
| ---------- | ----------- | ------------ | -------- |
| [Xerces-context++](https://xerces.apache.org/xerces-c/) | C++ XML Parser | `sudo apt install libxerces-c-dev` | Yes |
| [Code Synthesis](https://www.codesynthesis.com/products/xsd) | XML Data Binding for C++ | `sudo apt install xsdcxx` | Yes |
| [PROJ](https://proj.org/) | Coordinate transformations and projections | `sudo apt-get install proj-bin` | Yes |

## Internal Dependencies

These dependencies are pulled by CMake when the project is built. You `do not` have to install them manually.

| Dependency | Usage | Required | 
| ---------- | ----------- | -------- |
| [YAML-CPP](https://github.com/jbeder/yaml-cpp.git) | YAML parser | Yes |
| [TinyXML-2](https://github.com/leethomason/tinyxml2.git) | XML parser | Yes |
| [GoogleTest](https://github.com/google/googletest) | Google unit testing framework | `-DWITH_TESTS=ON` |

***

# Known Issues

***

### XMLNS Attribute

OpenDRIVE 1.4: The parser may fail if the `xmlns` attribute **is** set.  
OpenDRIVE 1.4: The parser may fail if the `xmlns` attribute **is not exactly** set.

### Workaround

OpenDRIVE 1.4: Change `<OpenDRIVE xmlns="http://www.opendrive.org">` to `<OpenDRIVE>`.  
OpenDRIVE 1.6: The `xmlns` attribute **must** be `xmlns="http://code.asam.net/simulation/standard/opendrive_schema"`.

***
