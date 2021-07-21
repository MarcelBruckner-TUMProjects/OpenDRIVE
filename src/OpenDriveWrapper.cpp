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

    bool operator<(const OpenDriveWrapper &lhs, const OpenDriveWrapper &rhs) {
        return lhs.getS() < rhs.getS();
    }

    bool operator>(const OpenDriveWrapper &lhs, const OpenDriveWrapper &rhs) {
        return rhs < lhs;
    }
}