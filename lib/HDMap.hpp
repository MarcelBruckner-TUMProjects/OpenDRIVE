//
// Created by brucknem on 16.02.21.
//

#ifndef OPENDRIVE_HDMAP_HPP
#define OPENDRIVE_HDMAP_HPP


#include <string>
#include <vector>
#include <map>

#include "proj.h"

#include "standard/OpenDRIVE_1.4H_Schema_Files.hxx"

#include "Road.hpp"
#include "Geometry.hpp"

namespace opendrive {

    /**
     * A class for parsing and querying the OpenDrive HD maps.
     */
    class HDMap : public OpenDriveWrapper<OpenDRIVE> {
    private:

        /**
         * The filename of the OpenDrive HD map.
         */
        std::string filename;

        std::map<std::string, Road> roads;


        void setRoads();

    public:
        /**
         * @constructor
         */
        explicit HDMap(std::string filename);

        /**
         * @destructor
         */
        virtual ~HDMap() = default;

        /**
         * @get
         */
        const Road &getRoad(const std::string &id) const;

        bool operator==(const std::string &roadId) override;

        Point interpolate(double s, double t) override;
    };
}
#endif //OPENDRIVE_HDMAP_HPP
