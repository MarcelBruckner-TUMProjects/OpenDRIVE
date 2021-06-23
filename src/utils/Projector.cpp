//
// Created by brucknem on 24.02.21.
//

#include "OpenDRIVE/utils/Projector.hpp"
#include "OpenDRIVE/utils/LongLatProjector.hpp"
#include <memory>

namespace opendrive {

    Projector::Projector(const std::string &fromProjection, const std::string &toProjection) {
        context = proj_context_create();
        projection = proj_create_crs_to_crs(context,
                                            fromProjection.c_str(),
                                            toProjection.c_str(),
                                            nullptr);
        if (nullptr == projection) {
            throw std::invalid_argument("Couldn't create projection");
        }

        PJ *normalizedProjection = proj_normalize_for_visualization(context, projection);
        if (nullptr == normalizedProjection) {
            throw std::invalid_argument("Couldn't create projection");
        }
        proj_destroy(projection);
        projection = normalizedProjection;
    }

    Projector::~Projector() {
        proj_destroy(projection);
        proj_context_destroy(context);
    }

    Vector Projector::project(const Vector &vector, PJ_DIRECTION direction) const {
        PJ_COORD a, b;

        a = proj_coord(vector.getX(), vector.getY(), vector.getZ(), 0);
        b = proj_trans(projection, direction, a);

        return opendrive::Vector{b.xyz.x, b.xyz.y, b.xyz.z};
    }


}