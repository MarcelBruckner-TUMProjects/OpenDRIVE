//
// Created by brucknem on 22.02.21.
//

#include "OpenDRIVE/OpenDriveWrapper.hpp"

namespace opendrive {

    OpenDriveWrapper::OpenDriveWrapper(double s) : s(s) {

    }

    double OpenDriveWrapper::getS() const {
        return s;
    }
}