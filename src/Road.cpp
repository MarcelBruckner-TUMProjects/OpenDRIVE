//
// Created by brucknem on 22.02.21.
//

#include "OpenDRIVE/Road.hpp"
#include <string>
#include <iomanip>
#include <utility>
#include<algorithm>

namespace opendrive {


    Road::Road(std::string id, std::string name, double length, std::string junction,
               std::vector<Type> type, std::vector<Object> objects,
               std::vector<Geometry> planView, std::vector<Elevation> elevationProfile,
               std::vector<SuperElevation> lateralProfile) : OpenDriveWrapper(0), id(std::move(id)),
                                                             name(std::move(name)),
                                                             length(length),
                                                             junction(std::move(junction)), type(std::move(type)),
                                                             objects(std::move(objects)),
                                                             planView(std::move(planView)),
                                                             elevationProfile(std::move(elevationProfile)),
                                                             lateralProfile(std::move(lateralProfile)) {

        std::sort(planView.begin(), planView.end(), [](const Geometry &lhs, const Geometry &rhs) {
            return lhs.getS() < rhs.getS();
        });
        std::sort(elevationProfile.begin(), elevationProfile.end(), [](const Elevation &lhs, const Elevation &rhs) {
            return lhs.getS() < rhs.getS();
        });
        std::sort(lateralProfile.begin(), lateralProfile.end(),
                  [](const SuperElevation &lhs, const SuperElevation &rhs) {
                      return lhs.getS() < rhs.getS() || lhs.getT() < rhs.getT();
                  });
    }


    bool Road::operator==(const std::string &roadId) {
        return roadId == id;
    }


#pragma region PlainGetters

    const std::vector<Object> &Road::getObjects() const {
        return objects;
    }

    const std::vector<Geometry> &Road::getPlanView() const {
        return planView;
    }

    const std::vector<Elevation> &Road::getElevationProfile() const {
        return elevationProfile;
    }

    const std::vector<SuperElevation> &Road::getLateralProfile() const {
        return lateralProfile;
    }

#pragma endregion PlainGetters

#pragma region TemplateGetters

    template<typename T>
    const T &Road::getElement(const std::vector<T> &map, double ss) const {
        if (ss < 0) {
            throw std::invalid_argument(std::to_string(ss) + " is not on the road.");
        }
        for (int i = 0; i < map.size(); i++) {
            double getS = map[i].getS();
            if (getS > ss) {
                return map[i - 1];
            }
        }
        return map[map.size() - 1];
    }

    template<>
    const Object &Road::getElement<Object>(const std::string &id) const {
        for (const auto &entry : objects) {
            if (entry.getId() == id) {
                return entry;
            }
        }
        throw std::invalid_argument("There exists no object " + id + ".");
    }

    template<typename T>
    std::vector<double> Road::getStartCoordinates(std::vector<T> map, bool omitLastElement) const {
        std::vector<double> result;

        int i = 0;
        for (const auto &entry : map) {
            if (omitLastElement && i >= map.size() - 1) {
                break;
            }
            result.emplace_back(entry.getS());
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

    std::vector<Object> Road::filterObjects(const std::string &type, const std::string &name) const {
        std::vector<Object> filtered;
        for (const auto &entry : objects) {
            if (entry.getType() == type &&
                entry.getName() == name) {
                filtered.emplace_back(entry);
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
    Vector Road::getWorldPosition(const Geometry &object) const {
        auto position = interpolate(object.getS());
        return position;
    }

    template<>
    Vector Road::getWorldPosition(const Object &object) const {
        auto position = interpolate(object.getS(), object.getT());
        auto zOffset = object.getZOffset();
        return position + Vector{0, 0, zOffset};
    }

    template<>
    Vector Road::getWorldPosition<opendrive::Object>(const std::string &id) const {
        return getWorldPosition(getElement<Object>(id));
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

    const std::vector<Road::Type> &Road::getType() const {
        return type;
    }


#pragma endregion Calculations

    Road::Type::Type(const double s, std::string type) : OpenDriveWrapper(s), type(std::move(type)) {}

    const std::string &Road::Type::getType() const {
        return type;
    }
}
