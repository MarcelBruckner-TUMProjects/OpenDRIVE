//
// Created by brucknem on 18.02.21.
//

#ifndef OPENDRIVE_HEADER_HPP
#define OPENDRIVE_HEADER_HPP

#include <memory>
#include <string>
#include "pugixml.hpp"
#include "boost/lexical_cast.hpp"
#include "proj.h"
#include "GeoReference.hpp"

namespace opendrive {

/**
 * Wrapper for the OpenDRIVE header.
 * https://www.asam.net/index.php?eID=dumpFile&t=f&f=3495&token=56b15ffd9dfe23ad8f759523c806fc1f1a90a0e8#_file_structure
 */
    class Header {
    private:

        /**
         * The georeference projection string.
         */
        std::shared_ptr<GeoReference> geoReference;

    public:
        /**
         * Major revision number of OpenDRIVE format
         */
        const ushort revMajor;

        /**
         * Minor revision number of OpenDRIVE format; 6 for OpenDrive 1.6
         */
        const ushort revMinor;

        /**
         * Database name
         */
        const std::string name;

        /**
         * Version of this road network
         */
        const std::string version;

        /**
         * Time/date of database creation according to ISO 8601 (preference: YYYY-MM-DDThh:mm:ss)
         */
        const std::string date;

        /**
         * Maximum inertial y value
         */
        const double north;

        /**
         * Minimum inertial y value
         */
        const double south;

        /**
         * Maximum inertial x value
         */
        const double east;

        /**
         * Minimum inertial x value
         */
        const double west;

        /**
         * Vendor name
         */
        const std::string vendor;

        /**
         * @constructor
         */
        Header(ushort revMajor, ushort revMinor, std::string name, std::string version,
               std::string date, double north, double south, double east, double west,
               std::string vendor);

        /**
         * @constructor
         */
        explicit Header(pugi::xpath_node headerNode);

        /**
         * @destructor
         */
        virtual ~Header() = default;

        /**
         * @operator
         */
        friend std::ostream &operator<<(std::ostream &os, const Header &obj);

        /**
         * @get
         */
        const std::shared_ptr<GeoReference> &getGeoReference() const;

        /**
         * @set
         */
        void setGeoReference(const GeoReference &geoReference);

        /**
         * @set
         */
        void setGeoReference(pugi::xpath_node geoReferenceNode);
    };
}

#endif //OPENDRIVE_HEADER_HPP
