//
// Created by brucknem on 22.02.21.
//

#include "Road.hpp"
#include <string>

#include <iomanip>

namespace opendrive {

#pragma region Setters

    template<>
    void Road::set<Object>() {
        if (openDriveObject->objects().present()) {
            for (const auto &objectNode : openDriveObject->objects().get().object()) {
                objects.emplace(objectNode.id().get(), Object(objectNode));
            }
        }
    }

    template<>
    void Road::set<Geometry>() {
        for (const auto &geometryNode : openDriveObject->planView().geometry()) {
            planView.emplace(geometryNode.s().get(), Geometry(geometryNode));
        }
    }

    template<>
    void Road::set<Elevation>() {
        for (const auto &elevationNode : openDriveObject->elevationProfile().get().elevation()) {
            elevationProfile.emplace(elevationNode.s().get(), Elevation(elevationNode));
        }
    }

    template<>
    void Road::set<SuperElevation>() {
        for (const auto &superElevationNode : openDriveObject->lateralProfile().get().superelevation()) {
            lateralProfile.emplace(superElevationNode.s().get(), SuperElevation(superElevationNode));
        }
    }

#pragma endregion Setters

#pragma region ObjectOrientedFunctions

    Road::Road(const road &openDriveRoad) : OpenDriveWrapper<road>(openDriveRoad) {
        set<Geometry>();
        set<Elevation>();
        set<SuperElevation>();
        set<Object>();
    }

    bool Road::operator==(const std::string &roadId) {
        return std::strcmp(roadId.c_str(), openDriveObject->id()->c_str()) == 0;
    }

#pragma endregion ObjectOrientedFunctions

#pragma region PlainGetters

    double Road::getLength() const {
        return openDriveObject->length().get();
    }

    const std::map<std::string, Object> &Road::getObjects() const {
        return objects;
    }

    const std::map<double, Geometry> &Road::getPlanView() const {
        return planView;
    }

    const std::map<double, Elevation> &Road::getElevationProfile() const {
        return elevationProfile;
    }

    const std::map<double, SuperElevation> &Road::getLateralProfile() const {
        return lateralProfile;
    }

#pragma endregion PlainGetters

#pragma region TemplateGetters

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

    template<>
    const Object &Road::getElement<Object>(const std::string &id) const {
        for (const auto &entry : objects) {
            if (std::strcmp(entry.second.getOpenDriveObject()->id()->c_str(), id.c_str()) == 0) {
                return objects.at(entry.first);
            }
        }
        return throwObjectNotFound(id);
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

    template<>
    std::vector<double> Road::getStartCoordinates<Geometry>(bool omitLastElement) const {
        return getStartCoordinates(planView, omitLastElement);
    }

    template<>
    std::vector<double> Road::getStartCoordinates<Elevation>(bool omitLastElement) const {
        return getStartCoordinates(elevationProfile, omitLastElement);
    }

    template<>
    std::vector<double> Road::getStartCoordinates<SuperElevation>(bool omitLastElement) const {
        return getStartCoordinates(lateralProfile, omitLastElement);
    }

    template<>
    const Geometry &Road::getElement<Geometry>(double s) const {
        const auto &geometry = getElement<Geometry>(planView, s);
        if (s > geometry.getSCoordinate() + geometry.getLength()) {
            return throwNotOnRoad<Geometry>(s);
        }
        return geometry;
    }

    template<>
    const Elevation &Road::getElement<Elevation>(double s) const {
        return getElement<Elevation>(elevationProfile, s);
    }

    template<>
    const SuperElevation &Road::getElement<SuperElevation>(double s) const {
        return getElement<SuperElevation>(lateralProfile, s);
    }

#pragma endregion TemplateGetters

#pragma region Exceptions

    template<typename T>
    const T &Road::throwNotOnRoad(double s) const {
        throw std::invalid_argument(std::to_string(s) + " is not on the road.");
        return *new T();
    }

    const Object &Road::throwObjectNotFound(const std::string &id) {
        throw std::invalid_argument("There exists no object " + id + ".");
        return *new Object();
    }

#pragma endregion Exceptions

#pragma region Other

    std::map<std::string, Object> Road::filterObjects(const std::string &type, const std::string &name) const {
        std::map<std::string, Object> filtered;
        for (const auto &entry : objects) {
            if (std::strcmp(entry.second.getType().c_str(), type.c_str()) == 0 &&
                std::strcmp(entry.second.getName().c_str(), name.c_str()) == 0) {
                filtered.emplace(entry.first, entry.second);
            }
        }
        return filtered;
    }

#pragma endregion Other

#pragma region Calculations


    Vector Road::interpolate(double s, double t) const {
        Geometry geometry = getElement<Geometry>(s);
        auto height = getElement<Elevation>(s).interpolate(s);

        Vector tangent = geometry.calculateTangent(s);
        Vector normal = geometry.calculateNormal(s);

        double roll = getElement<SuperElevation>(s).interpolate(s);
        normal = normal.rotate(tangent, roll).normalized();

        return geometry.interpolate(s) + t * normal + Vector{0, 0, 1} * height;
    }

    template<>
    Vector Road::getWorldPosition<Object>(const std::string &id) const {
        auto object = getElement<Object>(id);
        return interpolate(object.getSCoordinate(), object.getTCoordinate());
    }

    template<typename T>
    Vector Road::getWorldPosition(const T &object) const {
        return interpolate(object.getSCoordinate());
    }

    template<>
    Vector Road::getWorldPosition<Geometry>(double s) const {
        return getWorldPosition(getElement<Geometry>(s));
    }

    std::string Road::getName() const {
        return openDriveObject->name()->c_str();
    }

    std::string Road::getId() const {
        return openDriveObject->id()->c_str();
    }


#pragma endregion Calculations

}
