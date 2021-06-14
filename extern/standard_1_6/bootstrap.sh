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
xsdcxx cxx-tree --std c++11 --reserved-name access=parkingSpace_access --reserved-name link=lane_link --reserved-name signal=signals_signal deliverable/xsd_schema/*.xsd
#xsdcxx cxx-tree --std c++11 OpenDRIVE_1.4H_Schema_Files.xsd
