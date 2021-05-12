//
// Created by brucknem on 25.02.21.
//

#include "OpenDRIVE/Elevation.hpp"

namespace opendrive {

    template
    class ElevationBase<elevation>;

    template
    class ElevationBase<superelevation>;

    template<class T>
    ElevationBase<T>::ElevationBase(const T &openDriveObject):OpenDriveWrapperWithCoordinate<T>(openDriveObject) {}

    template<class T>
    double ElevationBase<T>::interpolate(double s) const {
        double ds = s - OpenDriveWrapperWithCoordinate<T>::getSCoordinate();
        double ds2 = ds * ds;
        double ds3 = ds2 * ds;

        double elev =
                OpenDriveWrapperWithCoordinate<T>::getOpenDriveObject()->a().get() +
                OpenDriveWrapperWithCoordinate<T>::getOpenDriveObject()->b().get() * ds +
                OpenDriveWrapperWithCoordinate<T>::getOpenDriveObject()->c().get() * ds2 +
                OpenDriveWrapperWithCoordinate<T>::getOpenDriveObject()->d().get() * ds3;
        return elev;
    }

    template<class T>
    double ElevationBase<T>::interpolateStart() const {
        return interpolate(OpenDriveWrapperWithCoordinate<T>::getSCoordinate());
    }

    Elevation::Elevation(const elevation &openDriveObject) : ElevationBase<elevation>(
            openDriveObject) {}

    SuperElevation::SuperElevation(const superelevation &openDriveObject) : ElevationBase<superelevation>(
            openDriveObject) {}
}
