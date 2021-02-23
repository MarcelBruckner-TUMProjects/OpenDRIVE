//
// Created by brucknem on 22.02.21.
//

#include "Road.hpp"
#include <string>

namespace opendrive {

    Road::Road(const road &openDriveRoad) : OpenDriveWrapper<road>(openDriveRoad) {
        setGeometries();
        setObjects();
    }

    void Road::setObjects() {
        for (const auto &object : openDriveObject->objects().get().object()) {
            objects.emplace(object.id().get(), Object(object));
        }
    }

    void Road::setGeometries() {
        for (const auto &geometry : openDriveObject->planView().geometry()) {
            planView.emplace(geometry.s().get(), Geometry(geometry));
        }
    }

    const std::map<std::string, Object> &Road::getObjects() const {
        return objects;
    }


    bool Road::operator==(const std::string &roadId) {
        return std::strcmp(roadId.c_str(), openDriveObject->id()->c_str());
    }

    const Object &Road::getObject(const std::string &id) const {
        for (const auto &entry : objects) {
            if (std::strcmp(entry.second.getOpenDriveObject()->id()->c_str(), id.c_str()) == 0) {
                return objects.at(entry.first);
            }
        }
        return throwObjectNotFound(id);
    }

    const std::map<double, Geometry> &Road::getPlanView() const {
        return planView;
    }

    const Geometry &Road::getGeometry(double s) const {
        if (s < 0) {
            return throwGeometryNotFound(s);
        }
        double previous = 0;
        for (const auto &entry : planView) {
            double getS = entry.second.getSCoordinate();
            if (getS > s) {
                break;
            }
            previous = getS;
        }
        const Geometry &geometry = planView.at(previous);
        if (s > geometry.getSCoordinate() + geometry.getLength()) {
            return throwGeometryNotFound(s);
        }
        return geometry;
    }

    double Road::getLength() const {
        return openDriveObject->length().get();
    }

    const Geometry &Road::throwGeometryNotFound(double s) {
        throw std::invalid_argument(std::to_string(s) + " is not on the road.");
        return *new Geometry();
    }

    const Object &Road::throwObjectNotFound(const std::string &id) {
        throw std::invalid_argument("There exists no object " + id + ".");
        return *new Object();
    }
}
