# OpenDRIVE

This serves as an OpenDRIVE 1.6 parser for my [Guided Research](https://github.com/Brucknem/GuidedResearch) at the
[Providentia++](https://innovation-mobility.com/) project.

It is made to extract the world positions of landmarks from the OpenDRIVE HD maps that have been bought during the
project.

# Completeness

I will not build a complete parser, as I am only interested in the signals and objects positions. If you need more
functionality I am happy if you make a [pull request](https://github.com/Brucknem/OpenDRIVE/pulls) and contribute to the
parser.

### If you plan to make a complete parser, I advise you to download the [official XSD](https://www.asam.net/standards/detail/opendrive/), use a code generator to make some boilerplate code and implement the [Standard](https://www.asam.net/index.php?eID=dumpFile&t=f&f=3495&token=56b15ffd9dfe23ad8f759523c806fc1f1a90a0e8#_foreword).

# Dependencies

None which you have to install. The parsing library and test framework are cloned at configure time.

# References

- XML Parsing: https://github.com/zeux/pugixml
- Testing: https://github.com/google/googletest.git