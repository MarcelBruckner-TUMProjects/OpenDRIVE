//
// Created by brucknem on 16.02.21.
//

#ifndef OPENDRIVE_HDMAP_HPP
#define OPENDRIVE_HDMAP_HPP


#include <string>
#include <vector>

#include "pugixml.hpp"
#include "proj.h"
#include "Road.hpp"
#include "Geometry.hpp"
#include "Header.hpp"

namespace opendrive {


    /**
     * A class for parsing and querying the OpenDrive HD maps.
     */
    class HDMap {
    private:

        /**
         * The filename of the OpenDrive HD map.
         */
        std::string filename;

        /**
         * The parsed XML document.
         */
        pugi::xml_document doc;

        /**
         * The projectionString defining the coordinate system.
         */
        std::string projectionString;

        /**
         * The coordinate transformation.
         */
        PJ *projection{};

        /**
         * The OpenDRIVE roads.
         */
        std::vector<Road> roads;

        /**
         * The OpenDRIVE header.
         */
        std::shared_ptr<Header> header;

        static std::string getRoadSelector(pugi::xpath_node road);

        static std::string getRoadSelector(std::string id);

    public:

        /**
         * @constructor
         */
        explicit HDMap(std::string filename);

        /**
         * @destructor
         */
        virtual ~HDMap();

        /**
         * @get
         */
        const std::vector<Road> &getRoads() const;

        /**
         * Finds all nodes by the given type.
         */
        pugi::xpath_node_set findNodesByType(const std::string &type);

        /**
         * Finds all nodes by the given XPath.
         */
        pugi::xpath_node_set findNodesByXPath(const std::string &path);

        /**
         * @get Gets the objects of the given road.
         */
        pugi::xpath_node_set getObjects(pugi::xpath_node road);

        /**
         * @get Gets the signals of the given road.
         */
        pugi::xpath_node_set getSignals(pugi::xpath_node road);

        /**
         * @get Gets the geometries of the given road.
         */
        std::vector<Geometry> getGeometries(pugi::xpath_node road);

        /**
         * @get Checks if the road with the given id exists.
         */
        bool hasRoad(const std::string &id);

        /**
         * @get Gets a specific road with the given id.
         * @throws invalid_argument if no road with the given id is found.
         */
        Road getRoad(const std::string &id) const;

        void parse();

        void parseHeader();

        /**
         * @get
         */
        const std::shared_ptr<Header> &getHeader() const;
    };
}
#endif //OPENDRIVE_HDMAP_HPP
