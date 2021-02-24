//
// Created by brucknem on 24.02.21.
//

#include "Projector.hpp"
#include <memory>

namespace opendrive {
    Projector::Projector(const std::string &projectionString) {
        context = proj_context_create();
        projection = proj_create_crs_to_crs(context,
                                            projectionString.c_str(),
                                            "+proj=longlat +datum=WGS84",
                                            nullptr);
        if (nullptr == projection) {
            throw std::invalid_argument("Couldn't create projection");
        }

        PJ *P_for_GIS = proj_normalize_for_visualization(context, projection);
        if (nullptr == P_for_GIS) {
            throw std::invalid_argument("Couldn't create projection");
        }
        proj_destroy(projection);
        projection = P_for_GIS;
    }

    Projector::~Projector() {
        proj_destroy(projection);
        proj_context_destroy(context);
    }

    Vector Projector::project(const Vector &vector) const {
        PJ_COORD a, b;

        a = proj_coord(vector.getX(), vector.getY(), vector.getZ(), 0);
        b = proj_trans(projection, PJ_FWD, a);

        return {b.lp.phi, b.lp.lam, 0};
    }

    std::string Projector::toGoogleMapsLink(const Vector &vector) {
        return "https://www.google.de/maps/place/" + vector.formatXY(52, false);
    }
}