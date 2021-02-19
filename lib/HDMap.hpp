//
// Created by brucknem on 16.02.21.
//

#ifndef OPENDRIVE_HDMAP_HPP
#define OPENDRIVE_HDMAP_HPP


#include <string>
#include <vector>

#include "proj.h"

#include "standard/OpenDRIVE_1.4H_Schema_Files.hxx"

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
         * The parsed open drive object model.
         */
        std::unique_ptr<OpenDRIVE> _openDrive;

    public:
        /**
         * @constructor
         */
        explicit HDMap(const std::string &filename);

        /**
         * @destructor
         */
        virtual ~HDMap() = default;

        /**
         * @get
         */
        const std::unique_ptr<OpenDRIVE> &openDrive() const;

        /**
         * @get
         */
        const road &getRoad(const std::string &id) const;

    };
}
#endif //OPENDRIVE_HDMAP_HPP
