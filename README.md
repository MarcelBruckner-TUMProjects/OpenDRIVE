# OpenDRIVE

This serves as an OpenDRIVE 1.4 parser for my [Guided Research](https://github.com/Brucknem/GuidedResearch) at the
[Providentia++](https://innovation-mobility.com/) project.

It is made to extract the world positions of landmarks from the OpenDRIVE HD maps that have been bought during the
project.

# Dependencies

Install these on your system:

- [Code Synthesis](https://www.codesynthesis.com/products/xsd/download.xhtml)
- [Xerces-context++](https://xerces.apache.org/xerces-c/download.cgi)

Automatically built by CMake:

- [GoogleTest](https://github.com/google/googletest.git)

# Setup

Before running any code you have to download the OpenDRIVE V1.4 standard by VIRES Simulationstechnologie GmbH and use
the XSD schema to generate context++ data bindings.

To make this process easier there is the `bootstrap.sh` script. Run it and follow the instructions to download and
generate the standard.

# Run
```shell
mkdir build && cd build
cmake ..
cmake --build . -j8
./standalone -h
```
