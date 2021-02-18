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

            for (const auto &geometryNode : roadNode.node().select_nodes("//geometry")) {
                road.add<Geometry>(geometryNode);
                road.getPlanView().back()->setPrimitive(geometryNode.node().select_nodes("//paramPoly3")[0]);
            }

            for (const auto &elevationNode : roadNode.node().select_nodes("//elevation")) {
                road.add<Elevation>(elevationNode);
            }

            for (const auto &superElevationNode : roadNode.node().select_nodes("//superelevation")) {
                road.add<SuperElevation>(superElevationNode);
            }

            roads.emplace_back(std::make_shared<Road>(road));
        }
    }

    pugi::xpath_node_set HDMap::findNodesByXPath(const std::string &path) {
        return doc.select_nodes((path).c_str());
    }

    bool HDMap::hasRoad(const std::string &id) {
        return std::any_of(roads.begin(), roads.end(), [id](const std::shared_ptr<Road> &road) {
            if (road->id == id) {
                return true;
            }
            return false;
        });
    }

    std::shared_ptr<Road> HDMap::getRoad(const std::string &id) const {
        for (const auto &road : getRoads()) {
            if (road->id == id) {
                return road;
            }
        }
        throw std::invalid_argument("Cannot find road");
    }

    HDMap::~HDMap() {
        proj_destroy(projection);
    }

    const std::shared_ptr<Header> &HDMap::getHeader() const {
        return header;
    }

    const std::vector<std::shared_ptr<Road>> &HDMap::getRoads() const {
        return roads;
    }
}