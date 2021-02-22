//
// Created by brucknem on 22.02.21.
//

#include "Road.hpp"

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
        auto iterator = std::find_if(
                objects.begin(),
                objects.end(),
                [&id](const std::pair<std::string, Object> &entry) {
                    return std::strcmp(entry.second.getOpenDriveObject()->id()->c_str(), id.c_str()) == 0;
                }
        );
        return iterator->second;
    }

    Road &Road::empty() {
        static Road instance;
        return instance;
    }

    Point Road::interpolate(double s, double t) {
        return {0, 0};
    }

    const std::map<double, Geometry> &Road::getPlanView() const {
        return planView;
    }

    const Geometry &Road::getGeometry(double s) const {
        auto iterator = std::find_if(
                planView.begin(),
                planView.end(),
                [&s](const std::pair<double, Geometry> &entry) {
                    return entry.second.getS() > s;
                }
        );
        return (--iterator)->second;
    }

    double Road::getLength() const {
        return openDriveObject->length().get();
    }
}
