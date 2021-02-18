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
#include "Elevation.hpp"

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
         * The coordinate transformation.
         */
        PJ *projection{};

        /**
         * The OpenDRIVE header.
         */
        std::shared_ptr<Header> header;

        /**
         * The OpenDRIVE roads.
         */
        std::vector<std::shared_ptr<Road>> roads;


        /**
        * Finds all nodes by the given XPath.
        */
        pugi::xpath_node_set findNodesByXPath(const std::string &path);

    public:

        /**
         * @constructor Parses the given XML document.
         * Does NOT parse the OpenDRIVE elements in the document.
        */
        explicit HDMap(std::string filename);

        /**
        * @destructor
        */
        virtual ~HDMap();

        /**
         * Main parsing function for the OpenDRIVE standard.
         */
        void parse();

        /**
         * Parses the OpenDRIVE header.
         */
        void parseHeader();

        /**
        * @get Checks if the road with the given id exists.
        */
        bool hasRoad(const std::string &id);

        /**
        * @get Gets a specific road with the given id.
        * @throws invalid_argument if no road with the given id is found.
        */
        std::shared_ptr<Road> getRoad(const std::string &id) const;

        /**
         * @get
         */
        const std::shared_ptr<Header> &getHeader() const;

        /**
         * @get
         */
        const std::vector<std::shared_ptr<Road>> &getRoads() const;
    };
}
#endif //OPENDRIVE_HDMAP_HPP
