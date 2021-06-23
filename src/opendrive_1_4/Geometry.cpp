//
// Created by brucknem on 22.02.21.
//

#include "OpenDRIVE/opendrive_1_4/Geometry.hpp"
#include "OpenDRIVE/utils/Vector.hpp"

namespace opendrive {
    namespace opendrive_1_4 {


        CubicPolynom extractU(const geometry &openDriveObject) {
            if (openDriveObject.paramPoly3().present()) {
                return {openDriveObject.paramPoly3()->aU().get(),
                        openDriveObject.paramPoly3()->bU().get(),
                        openDriveObject.paramPoly3()->cU().get(),
                        openDriveObject.paramPoly3()->dU().get()};

            } else {
                return {0, 0, 0, 0};
            }
        }

        CubicPolynom extractV(const geometry &openDriveObject) {
            if (openDriveObject.paramPoly3().present()) {
                return {openDriveObject.paramPoly3()->aV().get(),
                        openDriveObject.paramPoly3()->bV().get(),
                        openDriveObject.paramPoly3()->cV().get(),
                        openDriveObject.paramPoly3()->dV().get()};

            } else {
                return {0, 0, 0, 0};
            }
        }

        Geometry::Geometry(const geometry &openDriveObject) : opendrive::Geometry(openDriveObject.s().get(),
                                                                                  extractU(openDriveObject),
                                                                                  extractV(openDriveObject),
                                                                                  openDriveObject.hdg().get(),
                                                                                  openDriveObject.length().get(),
                                                                                  Vector{openDriveObject.x().get(),
                                                                                         openDriveObject.y().get()}) {}
    }
}