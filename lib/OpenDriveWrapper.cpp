//
// Created by brucknem on 22.02.21.
//

#include "OpenDriveWrapper.hpp"

namespace opendrive {

    template
    class OpenDriveWrapper<OpenDRIVE>;

    template
    class OpenDriveWrapper<road>;

    template
    class OpenDriveWrapper<object>;

    template<class S>
    OpenDriveWrapper<S>::OpenDriveWrapper(const S &openDriveObject) :openDriveObject(
            std::make_shared<S>(openDriveObject)) {
    }

    template<class S>
    bool OpenDriveWrapper<S>::isValid() const {
        return openDriveObject == nullptr;
    }

    template<class S>
    const std::shared_ptr<S> &OpenDriveWrapper<S>::getOpenDriveObject() const {
        return openDriveObject;
    }
}