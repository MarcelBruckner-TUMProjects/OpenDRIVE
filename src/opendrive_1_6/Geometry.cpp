//
// Created by brucknem on 22.02.21.
//

#include "OpenDRIVE/opendrive_1_6/Geometry.hpp"
#include "OpenDRIVE/utils/Vector.hpp"

namespace opendrive {
    namespace opendrive_1_6 {


        CubicPolynom
        extractU(const class simulation::standard::opendrive_schema::t_road_planView_geometry &openDriveObject) {
            if (openDriveObject.paramPoly3().present()) {
                return {openDriveObject.paramPoly3()->aU(),
                        openDriveObject.paramPoly3()->bU(),
                        openDriveObject.paramPoly3()->cU(),
                        openDriveObject.paramPoly3()->dU()};

            } else {
                return {0, 0, 0, 0};
            }
        }

        CubicPolynom
        extractV(const class simulation::standard::opendrive_schema::t_road_planView_geometry &openDriveObject) {
            if (openDriveObject.paramPoly3().present()) {
                return {openDriveObject.paramPoly3()->aV(),
                        openDriveObject.paramPoly3()->bV(),
                        openDriveObject.paramPoly3()->cV(),
                        openDriveObject.paramPoly3()->dV()};

            } else {
                return {0, 0, 0, 0};
            }
        }

        Geometry::Geometry(
                const class simulation::standard::opendrive_schema::t_road_planView_geometry &openDriveObject)
                : opendrive::Geometry(openDriveObject.s().operator const double &(),
                                      Vector{(double) openDriveObject.x(),
                                             (double) openDriveObject.y()},
                                      (double) openDriveObject.hdg(),
                                      std::strtod(openDriveObject.length().c_str(), nullptr),
                                      extractU(openDriveObject),
                                      extractV(openDriveObject)) {}
    }
}