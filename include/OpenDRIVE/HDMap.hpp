//
// Created by brucknem on 16.02.21.
//

#ifndef OPENDRIVE_HDMAP_HPP
#define OPENDRIVE_HDMAP_HPP


#include <string>
#include <vector>
#include <map>


#include "opendrive_1_4/OpenDRIVE_1.4H_Schema_Files.hxx"

#include "Road.hpp"
#include "Geometry.hpp"
#include "OpenDRIVE/utils/Projector.hpp"

namespace opendrive {

    /**
     * A class for parsing and querying the OpenDrive HD maps.
     * https://www.asam.net/index.php?eID=dumpFile&t=f&f=3495&token=56b15ffd9dfe23ad8f759523c806fc1f1a90a0e8
     */
    class HDMap : public OpenDriveWrapper {
    private:

        /**
         * The filename of the OpenDRIVE HD map.
         */
        std::string filename;

        /**
         * The roads that are specified in the OpenDRIVE HD map.
         */
        std::map<std::string, Road> roads;

        /**
         * @set Converts the parser roads to Road objects.
         */
        void setRoads(const OpenDRIVE &openDriveObject);

        /**
         * The header of the map.
         */
        struct Header {
            /**
             * The proj geo reference string.
             */
            std::string geoReference;

            /**
             * The vendor.
             */
            std::string vendor;

            /**
             * The displacement in the compass directions.
             */
            double north, south, east, west;
        } header;

    public:


        /**
         * @constructor Reads and parses the given OpenDRIVE HD map.
         */
        explicit HDMap(const std::string &filename);


        /**
         * @destructor
         */
        ~HDMap() override = default;

        /**
         * @get Tries to find a road with the given id in the OpenDRIVE HD map.
         *
         * @throws invalid_argument if no road with the given id is found.
         */
        const Road &getRoad(const std::string &id) const;

        /**
         * @get Tries to find an object with the given id in the OpenDRIVE HD map.
         *
         * @throws invalid_argument if no object with the given id is found.
         */
        const Object &getObject(const std::string &id) const;

        /**
         * @get The PROJ projection string from the header.
         */
        std::string getGeoReference() const;

        /**
         * @get
         */
        const std::map<std::string, Road> &getRoads() const;

        /**
         * @get
         */
        const std::string &getFilename() const;

        /**
         * @get
         */
        template<typename T>
        Vector getPosition(const std::string &id) const;

        /**
         * @get
         */
        const Header &getHeader() const;
    };
}
#endif //OPENDRIVE_HDMAP_HPP
