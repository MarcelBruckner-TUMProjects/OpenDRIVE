//
// Created by brucknem on 22.02.21.
//

#include "OpenDRIVE/Road.hpp"
#include <string>
#include <set>
#include <iomanip>
#include <utility>
#include<algorithm>
#include <OpenDRIVE/utils/ArrayUtils.hpp>

namespace opendrive {


    Road::Road(std::string id, std::string name, double length, std::string junction,
               std::vector<Type> type, std::vector<Object> objects,
               std::vector<Geometry> planView, std::vector<Elevation> elevationProfile,
               std::vector<SuperElevation> lateralProfileSuperElevations,
               std::vector<Shape> lateralProfileShapes, const opendrive::Lanes &lanes) :
            OpenDriveWrapper(0),
            id(std::move(id)),
            name(std::move(name)),
            length(length),
            junction(std::move(junction)),
            type(std::move(type)),
            objects(std::move(objects)),
            planView(std::move(planView)),
            elevationProfile(std::move(elevationProfile)),
            lateralProfileSuperElevations(std::move(lateralProfileSuperElevations)),
            lateralProfileShapes(std::move(lateralProfileShapes)),
            lanes(lanes) {

        sort();
        extractExplicitRoadMarks();
    }

    void Road::sort() {
        std::sort(planView.begin(), planView.end(), [](const Geometry &lhs, const Geometry &rhs) {
            return lhs.getS() < rhs.getS();
        });
        std::sort(elevationProfile.begin(), elevationProfile.end(),
                  [](const Elevation &lhs, const Elevation &rhs) {
                      return lhs.getS() < rhs.getS();
                  });
        std::sort(lateralProfileSuperElevations.begin(), lateralProfileSuperElevations.end(),
                  [](const SuperElevation &lhs, const SuperElevation &rhs) {
                      return lhs.getS() < rhs.getS();
                  });
        // TODO somehow including the next creates a SIGSEV
//        std::sort(lateralProfileShapes.begin(), lateralProfileShapes.end(),
//                  [](const Shape &lhs, const Shape &rhs) {
//                      return (lhs.getS() < rhs.getS()) || (lhs.getT() < rhs.getT());
//                  });
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

    template<>
    const std::vector<SuperElevation> &Road::getLateralProfile() const {
        return lateralProfileSuperElevations;
    }

    template<>
    const std::vector<Shape> &Road::getLateralProfile() const {
        return lateralProfileShapes;
    }

#pragma endregion PlainGetters

#pragma region TemplateGetters

    std::vector<Shape> Road::getElements(const std::vector<Shape> &map, double s, double t) const {
        if (s < 0) {
            throw std::invalid_argument(std::to_string(s) + " is not on the road.");
        }
        if (map.empty()) {
            return {};
        }
        auto possibleShapes = getElements(map, s);

        double upperBound = std::numeric_limits<double>::max();
        double lowerBound = -upperBound;

        for (const auto &i : possibleShapes) {
            auto current = i.getT();
            if (current > lowerBound && current <= t) {
                lowerBound = current;
                continue;
            }
            if (current <= upperBound && current > t) {
                upperBound = current;
                continue;
            }
            break;
        }

        std::vector<Shape> result;
        for (const auto &i : possibleShapes) {
            double getT = i.getT();
            if (lowerBound <= getT && getT < upperBound) {
                result.emplace_back(i);
            }
        }

        if (result.empty()) {
            int add = -1;
            int startIndex = (int) (possibleShapes.size() - 1);
            if (map[0].getT() > t) {
                add = 1;
                startIndex = 0;
            }

            int i = startIndex;
            result.emplace_back(possibleShapes[i]);
            while (((i += add) >= 0) && i < possibleShapes.size() && possibleShapes[i].getT() == result[0].getT()) {
                result.template emplace_back(possibleShapes[i]);
            }
            std::reverse(result.begin(), result.end());
        }
        return result;
    }

    template<typename T>
    std::vector<T> Road::getElements(const std::vector<T> &map, double s) const {
        if (s < 0 || s > length) {
            throw std::invalid_argument(std::to_string(s) + " is not on the road.");
        }

        auto indices = opendrive::utils::getNextSmallerElementsIndices<T, double>(map, s, [](const T &element) {
            return element.getS();
        });

        std::vector<T> result;
        std::transform(indices.begin(), indices.end(), std::back_inserter(result), [&map](int index) {
            return map[index];
        });
        return result;
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
        return getStartCoordinates(lateralProfileSuperElevations, omitLastElement);
    }

    template<>
    std::vector<double> Road::getStartCoordinates<Shape>(bool omitLastElement) const {
        return getStartCoordinates(lateralProfileShapes, omitLastElement);
    }

    template<>
    Geometry Road::getElement<Geometry>(double s) const {
        auto geometry = getElements<Geometry>(planView, s);
        if (s > geometry[0].getEndSCoordinate() + 1e-8) {
            throw std::invalid_argument(std::to_string(s) + " is not on the road.");
        }
        return geometry[0];
    }

    template<>
    Elevation Road::getElement<Elevation>(double s) const {
        return getElements<Elevation>(elevationProfile, s)[0];
    }

    template<>
    SuperElevation Road::getElement<SuperElevation>(double s) const {
        return getElements<SuperElevation>(lateralProfileSuperElevations, s)[0];
    }

    Shape *Road::getElement(double s, double t) const {
        std::vector<Shape> shapes = getElements(lateralProfileShapes, s, t);
        if (shapes.empty()) {
            return nullptr;
        }
        return new Shape(shapes[0]);
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

        Vector tangent = geometry.calculateTangent(s);
        Vector normal = geometry.calculateNormal(s);
        normal = (normal * t);

        auto height = getElement<Elevation>(s).interpolate(s);
        double roll = getElement<SuperElevation>(s).interpolate(s);

        Shape *shape = getElement(s, t);
        if (shape != nullptr) {
            auto shapeHeight = shape->interpolate(t);
            normal += {0, 0, shapeHeight};
        }

//        std::cout << normal.length() << std::endl;
        normal = normal.rotate(tangent, roll);
//        std::cout << normal.length() << std::endl;

        auto result = geometry.interpolate(s) + normal + Vector{0, 0, 1} * height;
//        std::cout << s << " x " << t << " -> " << result << std::endl;

        return result;
    }


    template<>
    Vector Road::getWorldPosition(const Geometry &object) const {
        auto position = interpolate(object.getS());
        return position;
    }

    const static std::vector<std::string> OBJECT_NAMES_TO_EXCLUDE{"guardRail", "trafficIsland", "raisedMedian", "wall"};

    template<>
    Vector Road::getWorldPosition(const Object &object) const {
        auto position = interpolate(object.getS(), object.getT());

        auto zOffset = object.getZOffset();

        Vector result;
        if (object.getType() == "barrier" &&
            std::find(OBJECT_NAMES_TO_EXCLUDE.begin(), OBJECT_NAMES_TO_EXCLUDE.end(), object.getName()) ==
            OBJECT_NAMES_TO_EXCLUDE.end()) {
            result = Vector{position[0], position[1], zOffset};
        } else {
            result = position + Vector{0, 0, zOffset};
        }
        return result;
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

    const Lanes &Road::getLanes() const {
        return lanes;
    }

    std::vector<double> Road::sampleSCoordinates(double interval) const {
        std::vector<double> result;
        if (length < interval) {
            result = {0, length};
        } else {
            int steps = (int) (length / interval);
            for (int step = 0; step < steps; step++) {
                double s = step * interval;
                result.emplace_back(s);
            }

            if (*result.end() < length) {
                result.emplace_back(length);
            }
        }

        for (const auto &laneSection : getLanes().getLaneSections()) {
            if (laneSection.getS() == 0) {
                continue;
            }
            result.emplace_back(laneSection.getS());
            result.emplace_back(laneSection.getS() - 1e-10);
        }

        std::set<double> removeDuplicates(result.begin(), result.end());
        result.assign(removeDuplicates.begin(), removeDuplicates.end());
        std::sort(result.begin(), result.end());

        return result;
    }

    void Road::addSample(double laneSectionS, int laneId, double s, double t) {
        auto sample = interpolate(s, t);
//        std::cout << s << " x " << t << " -> " << sample << std::endl;
        for (const auto &element : sample.getElements()) {
            if (element != element) {
                // s is NaN
                return;
            }
        }
        sampledLanePoints[laneSectionS][laneId].emplace_back(sample);
    }

    void Road::sampleLanes(double interval) {
        auto sCoordinates = sampleSCoordinates(interval);

        for (const auto &s : sCoordinates) {
            double laneSectionS = lanes.getLaneSection(s).getS();
            for (const auto &width : lanes.calculateLaneTOffsets(s)) {
                addSample(laneSectionS, width.first, s, width.second);
            }
        }
    }

    int Road::getNumberOfSampledLanePoints() {
        int sum = 0;
        for (const auto &laneSection : sampledLanePoints) {
            for (const auto &entry : laneSection.second) {
                sum += int(entry.second.size());
            }
        }
        return sum;
    }

    void Road::addExplicitRoadMarks(double laneSectionS, int laneId, double startS, double endS, double startT,
                                    double endT) {
        auto start = interpolate(startS, startT);
        auto end = interpolate(endS, endT);
        explicitRoadMarks[laneSectionS][laneId].emplace_back(std::make_pair(start, end));
    }

    void Road::extractExplicitRoadMarks() {
        for (const auto &laneSection : lanes.calculateExplicitRoadMarks()) {
            for (const auto &lane : laneSection.second) {
                for (const auto &explicitRoadMark : lane.second) {
                    addExplicitRoadMarks(laneSection.first, lane.first, explicitRoadMark[0], explicitRoadMark[1],
                                         explicitRoadMark[2], explicitRoadMark[3]);
                }
            }
        }
    }

    const std::map<double, std::map<int, std::vector<std::pair<Vector, Vector>>>> &
    Road::getExplicitRoadMarks() const {
        return explicitRoadMarks;
    }

    const std::map<double, std::map<int, std::vector<Vector>>> &Road::getSampledLanePoints() const {
        return sampledLanePoints;
    }

#pragma endregion Calculations

    Road::Type::Type(
            const double s, std::string
    type) : OpenDriveWrapper(s), type(std::move(type)) {}

    const std::string &Road::Type::getType() const {
        return type;
    }

}
