//
// Created by brucknem on 22.02.21.
//

#include "OpenDRIVE/Road.hpp"
#include <string>
#include <iomanip>
#include <utility>

namespace opendrive {


    Road::Road(std::string id, std::string name, double length, std::string junction,
               std::map<double, std::string> type, std::map<std::string, Object> objects,
               std::map<double, Geometry> planView, std::map<double, Elevation> elevationProfile,
               std::map<double, SuperElevation> lateralProfile) : OpenDriveWrapper(0), id(std::move(id)),
                                                                  name(std::move(name)),
                                                                  length(length),
                                                                  junction(std::move(junction)), type(std::move(type)),
                                                                  objects(std::move(objects)),
                                                                  planView(std::move(planView)),
                                                                  elevationProfile(std::move(elevationProfile)),
                                                                  lateralProfile(std::move(lateralProfile)) {}


    bool Road::operator==(const std::string &roadId) {
        return roadId == id;
    }


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
    const T &Road::getElement(const std::map<double, T> &map, double ss) const {
        if (ss < 0) {
            throw std::invalid_argument(std::to_string(ss) + " is not on the road.");
        }
        double previous = 0;
        for (const auto &entry : map) {
            double getS = entry.second.getS();
            if (getS > ss) {
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
            if (entry.second.getId() == id) {
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
            if (omitLastElement && i >= map.size() - 1) {
                break;
            }
            result.emplace_back(entry.first);
            i++;
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
            if (entry.second.getType() == type &&
                entry.second.getName() == name) {
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
        auto position = interpolate(object.getS(), object.getT());
        auto zOffset = object.getZOffset();
        return position + Vector{0, 0, zOffset};
    }

    template<typename T>
    Vector Road::getWorldPosition(const T &object) const {
        return interpolate(object.getS());
    }

    template<>
    Vector Road::getWorldPosition<Geometry>(double s) const {
        return getWorldPosition(getElement<Geometry>(s));
    }

    const std::string &Road::getId() const {
        return id;
    }

    const std::string &Road::getName() const {
        return name;
    }

    double Road::getLength() const {
        return length;
    }

    const std::string &Road::getJunction() const {
        return junction;
    }

    const std::map<double, std::string> &Road::getType() const {
        return type;
    }


#pragma endregion Calculations

}
