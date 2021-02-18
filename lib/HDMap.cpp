//
// Created by brucknem on 16.02.21.
//

#include <algorithm>
#include <cstring>
#include "HDMap.hpp"
#include "GeoReference.hpp"

namespace opendrive {

    HDMap::HDMap(std::string _filename) : filename(std::move(_filename)) {
        pugi::xml_parse_result result = doc.load_file(filename.c_str());

        if (!result) {
            throw std::invalid_argument("XML file parsing failed: " + std::string(result.description()));
        }
    }

    void HDMap::parseHeader() {
        auto headerNode = findNodesByXPath("//OpenDRIVE/header")[0];
        header = std::make_shared<Header>(headerNode);
        header->setGeoReference(headerNode.node().select_nodes("//geoReference")[0]);

        projection = proj_create_crs_to_crs(
                PJ_DEFAULT_CTX,
                header->getGeoReference()->geoReference.c_str(),
                "+proj=longlat +datum=WGS84",
                nullptr
        );
        if (projection == nullptr) {
            throw std::invalid_argument("Cannot create projection");
        }
    }

    void HDMap::parse() {
        parseHeader();

        for (const auto &roadNode : doc.select_nodes("//road")) {
            auto road = Road(roadNode);
            road.setType(roadNode.node().select_node("//type"));
            roads.emplace_back(road);
        }
    }

    pugi::xpath_node_set HDMap::findNodesByType(const std::string &type) {
        return findNodesByXPath("//" + type);
    }

    pugi::xpath_node_set HDMap::findNodesByXPath(const std::string &path) {
        return doc.select_nodes((path).c_str());
    }

    bool HDMap::hasRoad(const std::string &id) {
        return std::any_of(roads.begin(), roads.end(), [id](const Road &road) {
            if (road.id == id) {
                return true;
            }
            return false;
        });
    }

    Road HDMap::getRoad(const std::string &id) const {
        for (const auto &road : getRoads()) {
            if (road.id == id) {
                return road;
            }
        }
        throw std::invalid_argument("Cannot find road");
    }

    std::string HDMap::getRoadSelector(pugi::xpath_node road) {
        if (std::strcmp(road.node().name(), "road") != 0) {
            return "//fdsnhjkgbnkfdhgbjhf";
        }
        return getRoadSelector(road.node().attribute("id").value());
    }

    std::string HDMap::getRoadSelector(std::string id) {
        return "//road[@id = '" + std::string(std::move(id)) + "']";
    }

    pugi::xpath_node_set HDMap::getObjects(pugi::xpath_node road) {
        return findNodesByXPath(getRoadSelector(road) + "/objects/object");
    }

    pugi::xpath_node_set HDMap::getSignals(pugi::xpath_node road) {
        return findNodesByXPath(getRoadSelector(road) + "/signals/signal");
    }

    std::vector<Geometry> HDMap::getGeometries(pugi::xpath_node road) {
        auto nodes = findNodesByXPath(getRoadSelector(road) + "/planView/geometry");

        std::vector<Geometry> geometries;
        for (const auto &geometry : nodes) {
            if (std::strcmp(geometry.node().first_child().name(), "paramPoly3") == 0) {
                geometries.emplace_back(geometry, projection);
            }
        }
        return geometries;
    }


    HDMap::~HDMap() {
        proj_destroy(projection);
    }

    const std::vector<Road> &HDMap::getRoads() const {
        return roads;
    }

    const std::shared_ptr<Header> &HDMap::getHeader() const {
        return header;
    }
}