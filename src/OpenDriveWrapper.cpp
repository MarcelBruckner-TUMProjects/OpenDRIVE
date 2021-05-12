//
// Created by brucknem on 22.02.21.
//

#include "OpenDRIVE/OpenDriveWrapper.hpp"

namespace opendrive {

    template
    class OpenDriveWrapper<OpenDRIVE>;

    template
    class OpenDriveWrapper<road>;

    template
    class OpenDriveWrapperWithCoordinate<object>;

    template
    class OpenDriveWrapperWithCoordinate<geometry>;

    template
    class OpenDriveWrapperWithCoordinate<elevation>;

    template
    class OpenDriveWrapperWithCoordinate<superelevation>;

    template<class S>
    OpenDriveWrapper<S>::OpenDriveWrapper(const S &openDriveObject) :openDriveObject(
            std::make_shared<S>(openDriveObject)) {
    }

    template<class S>
    bool OpenDriveWrapper<S>::isValid() const {
        return openDriveObject != nullptr;
    }

    template<class S>
    const std::shared_ptr<S> &OpenDriveWrapper<S>::getOpenDriveObject() const {
        return openDriveObject;
    }

    template<class T>
    OpenDriveWrapperWithCoordinate<T>::OpenDriveWrapperWithCoordinate(const T &openDriveObject) :
            OpenDriveWrapper<T>(openDriveObject) {
    }

    template<class T>
    double OpenDriveWrapperWithCoordinate<T>::getSCoordinate() const {
        return OpenDriveWrapper<T>::getOpenDriveObject()->s().get();
    }
}