#!/bin/bash
shopt -s extglob

zipFileName="standard_download"*".zip"

totalPath="$zipFileName"
echo $totalPath

if [ ! -f $totalPath ]; then
  echo "Usage:"
  echo "Open https://www.asam.net/standards/detail/opendrive/ and 'Download OpenDRIVE V1.4 (by VIRES Simulationstechnologie GmbH)'."
  echo "You can find the link in the 'Older Versions' section."
  echo "This downloads a ZIP archive named $zipFileName"
  echo "Copy the downloaded $zipFileName into the this folder."
  echo "Run this script again."
  exit
fi

unzip $zipFileName
cp deliverable/xsd_schema/*.xsd ./

xsdcxx cxx-tree --std c++11 \
  --reserved-name access=parkingSpace_access \
  --reserved-name link=lane_link \
  --reserved-name signal=signals_signal \
  --reserved-name container=road_container \
  --generate-serialization --generate-polymorphic \
  --root-element-all \
  *.xsd

#  opendrive_16_core.xsd opendrive_16_railroad.xsd opendrive_16_junction.xsd opendrive_16_signal.xsd opendrive_16_road.xsd opendrive_16_lane.xsd opendrive_16_object.xsd
