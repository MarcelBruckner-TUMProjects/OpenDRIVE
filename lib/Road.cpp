//
// Created by brucknem on 22.02.21.
//

#include "Road.hpp"
#include <string>

namespace opendrive {

    Road::Road(const road &openDriveRoad) : OpenDriveWrapper<road>(openDriveRoad) {
        setGeometries();
        setElevations();
        setObjects();
    }

    void Road::setObjects() {
        for (const auto &objectNode : openDriveObject->objects().get().object()) {
            Object object = Object(objectNode);
            object.setWorldPosition(interpolate(object.getSCoordinate(), object.getTCoordinate()));
            objects.emplace(objectNode.id().get(), object);
        }
    }

    void Road::setGeometries() {
        for (const auto &geometryNode : openDriveObject->planView().geometry()) {
            planView.emplace(geometryNode.s().get(), Geometry(geometryNode));
        }
    }

    void Road::setElevations() {
        for (const auto &elevationNode : openDriveObject->elevationProfile().get().elevation()) {
            Elevation elevation = Elevation(elevationNode);
            elevationProfile.emplace(elevationNode.s().get(), elevation);
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

    template<typename T>
    std::vector<double> Road::getStartCoordinates(std::map<double, T> map, bool omitLastElement) const {
        std::vector<double> result;

        int i = 0;
        for (const auto &entry : map) {
            if (omitLastElement && i++ >= map.size() - 1) {
                break;
            }
            result.emplace_back(entry.first);
        }

        return result;
    }

    std::vector<double> Road::getGeometryStartCoordinates(bool omitLastElement) const {
        return getStartCoordinates(planView, omitLastElement);
    }

    std::vector<double> Road::getElevationStartCoordinates(bool omitLastElement) const {
        return getStartCoordinates(elevationProfile, omitLastElement);
    }

    template<typename T>
    const T &Road::getElement(const std::map<double, T> &map, double s) const {
        if (s < 0) {
            return throwNotOnRoad<T>(s);
        }
        double previous = 0;
        for (const auto &entry : map) {
            double getS = entry.second.getSCoordinate();
            if (getS > s) {
                break;
            }
            previous = getS;
        }
        const T &geometry = map.at(previous);
        return geometry;
    }

    const Geometry &Road::getGeometry(double s) const {
        const auto &geometry = getElement<Geometry>(planView, s);
        if (s > geometry.getSCoordinate() + geometry.getLength()) {
            return throwNotOnRoad<Geometry>(s);
        }
        return geometry;
    }

    const Elevation &Road::getElevation(double s) const {
        return getElement<Elevation>(elevationProfile, s);
    }

    double Road::getLength() const {
        return openDriveObject->length().get();
    }

    const Object &Road::throwObjectNotFound(const std::string &id) {
        throw std::invalid_argument("There exists no object " + id + ".");
        return *new Object();
    }

    Vector Road::interpolate(double s, double t) const {
        Geometry geometry = getGeometry(s);
        auto height = getElevation(s).interpolate(s);
        return geometry.interpolate(s) + t * geometry.calculateReferenceNormal(s) + height;
    }

    std::map<std::string, Object> Road::getObjects(const std::string &type, const std::string &name) const {
        std::map<std::string, Object> filtered;
        for (const auto &entry : objects) {
            if (std::strcmp(entry.second.getType().c_str(), type.c_str()) == 0 &&
                std::strcmp(entry.second.getName().c_str(), name.c_str()) == 0) {
                filtered.emplace(entry.first, entry.second);
            }
        }
        return filtered;
    }

    template<typename T>
    const T &Road::throwNotOnRoad(double s) const {
        throw std::invalid_argument(std::to_string(s) + " is not on the road.");
        return *new T();
    }

    const std::map<double, Elevation> &Road::getElevationProfile() const {
        return elevationProfile;
    }
}
