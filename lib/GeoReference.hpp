//
// Created by brucknem on 18.02.21.
//

#ifndef OPENDRIVE_GEOREFERENCE_HPP
#define OPENDRIVE_GEOREFERENCE_HPP

#include <string>
#include <pugixml.hpp>

namespace opendrive {

    /**
     * Wrapper for the OpenDRIVE georeference.
     * https://www.asam.net/index.php?eID=dumpFile&t=f&f=3495&token=56b15ffd9dfe23ad8f759523c806fc1f1a90a0e8#_georeferencing_in_opendrive
     */
    class GeoReference {
    public:
        /**
         * The raw geo reference string.
         */
        const std::string geoReference;

        /**
         * @constructor
         */
        explicit GeoReference(pugi::xpath_node elevationNode);

        /**
         * @destructor
         */
        virtual ~GeoReference() = default;

        /**
         * @constructor
         */
        explicit GeoReference(std::string geoReference);

        /**
         * @operator
         */
        friend std::ostream &operator<<(std::ostream &os, const GeoReference &obj);
    };
}

#endif //OPENDRIVE_GEOREFERENCE_HPP
