//
// Created by brucknem on 22.02.21.
//

#include "Road.hpp"

namespace opendrive {

    Road::Road(const road &openDriveRoad) : OpenDriveWrapper<road>(openDriveRoad) {
        setObjects();
    }

    void Road::setObjects() {
        for (const auto &object : openDriveObject->objects().get().object()) {
            objects.emplace(object.id().get(), Object(object));
        }
    }

    const std::map<std::string, Object> &Road::getObjects() const {
        return objects;
    }


    bool Road::operator==(const std::string &roadId) {
        return std::strcmp(roadId.c_str(), openDriveObject->id()->c_str());
    }

    const Object &Road::getObject(const std::string &id) const {
        const auto &iterator = objects.find(id);
        if (iterator != objects.end()) {
            return iterator->second;
        }
        return Object::empty();
    }

    Road &Road::empty() {
        static Road instance;
        return instance;
    }

}
