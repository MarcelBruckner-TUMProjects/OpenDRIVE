#!/bin/bash

zipFileName="OpenDRIVE_1.4__release_by_VIRES_Simulationstechnologie_GmbH__01.zip"

if [ ! -f "$zipFileName" ]; then
  echo "Usage:"
  echo "Open https://www.asam.net/standards/detail/opendrive/ and download OpenDRIVE V1.4 by VIRES Simulationstechnologie GmbH."
  echo "You can find the link in the 'Older Versions' section."
  echo "This downloads a ZIP archive named $zipFileName"
  echo "Copy the downloaded $zipFileName into this folder."
  echo "Run this script again."
  return
fi

unzip OpenDRIVE_1.4__release_by_VIRES_Simulationstechnologie_GmbH__01.zip
xsdcxx cxx-tree --std c++11 --reserved-name access=parkingSpace_access --reserved-name link=lane_link OpenDRIVE_1.4H_Schema_Files.xsd
#xsdcxx cxx-tree --std c++11 OpenDRIVE_1.4H_Schema_Files.xsd
