//
// Created by brucknem on 22.02.21.
//

#include "OpenDRIVE/Road.hpp"
#include "OpenDRIVE/Elevation.hpp"
#include "OpenDRIVE/SuperElevation.hpp"
#include <string>

#include <iomanip>

namespace opendrive {


#pragma region Setters

    template<>
    void Road::set<Object>(const class road &openDriveObject) {
        if (openDriveObject.objects().present()) {
            for (const auto &objectNode : openDriveObject.objects().get().object()) {
                objects.emplace(objectNode.id().get(), Object(objectNode));
            }
        }
    }

    template<>
    void Road::set<Geometry>(const class road &openDriveObject) {
        for (const auto &geometryNode : openDriveObject.planView().geometry()) {
            planView.emplace(geometryNode.s().get(), Geometry(geometryNode));
        }
    }

    template<>
    void Road::set<Elevation>(const class road &openDriveObject) {
        for (const auto &elevationNode : openDriveObject.elevationProfile().get().elevation()) {
            elevationProfile.emplace(elevationNode.s().get(), Elevation(elevationNode));
        }
    }

    template<>
    void Road::set<SuperElevation>(const class road &openDriveObject) {
        for (const auto &superElevationNode : openDriveObject.lateralProfile().get().superelevation()) {
            lateralProfile.emplace(superElevationNode.s().get(), SuperElevation(superElevationNode));
        }
    }

#pragma endregion Setters

#pragma region ObjectOrientedFunctions

    std::map<double, std::string> convertToType(const road &openDriveRoad) {
        std::map<double, std::string> result;
        for (const auto &type : openDriveRoad.type()) {
            result[type.s().get()] = type.type().get().c_str();
        }
        return result;
    }

    Road::Road(const road &openDriveRoad) : OpenDriveWrapper(0),
                                            id(openDriveRoad.id()->c_str()),
                                            name(openDriveRoad.name()->c_str()),
                                            length(openDriveRoad.length().get()),
                                            junction(openDriveRoad.junction().get().c_str()),
                                            type(convertToType(openDriveRoad)) {
        set<Geometry>(openDriveRoad);
        set<Elevation>(openDriveRoad);
        set<SuperElevation>(openDriveRoad);
        set<Object>(openDriveRoad);
    }

    bool Road::operator==(const std::string &roadId) {
        return roadId == id;
    }

#pragma endregion ObjectOrientedFunctions

#pragma region PlainGetters

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
            throw std::invalid_argument(std::to_string(s) + " is not on the road.");
        }
        double previous = 0;
        for (const auto &entry : map) {
            double getS = entry.second.s;
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
            if (entry.second.id == id) {
                return objects.at(entry.first);
            }
        }
        throw std::invalid_argument("There exists no object " + id + ".");
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
        if (s > geometry.getEndSCoordinate()) {
            throw std::invalid_argument(std::to_string(s) + " is not on the road.");
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

#pragma region Other

    std::map<std::string, Object> Road::filterObjects(const std::string &type, const std::string &name) const {
        std::map<std::string, Object> filtered;
        for (const auto &entry : objects) {
            if (entry.second.type == type &&
                entry.second.name == name) {
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
        auto position = interpolate(object.s, object.t);
        auto zOffset = object.zOffset;
        return position + Vector{0, 0, zOffset};
    }

    template<typename T>
    Vector Road::getWorldPosition(const T &object) const {
        return interpolate(object.s);
    }

    template<>
    Vector Road::getWorldPosition<Geometry>(double s) const {
        return getWorldPosition(getElement<Geometry>(s));
    }


#pragma endregion Calculations

}
