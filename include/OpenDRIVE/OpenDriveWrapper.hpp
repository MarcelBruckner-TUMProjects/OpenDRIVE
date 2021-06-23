//
// Created by brucknem on 22.02.21.
//

#ifndef OPENDRIVE_LISTCOMPOSITE_H
#define OPENDRIVE_LISTCOMPOSITE_H

#include <string>
#include <memory>

#include "opendrive_1_4/OpenDRIVE_1.4H_Schema_Files.hxx"

#include "OpenDRIVE/utils/Vector.hpp"

namespace opendrive {

    /**
     * Wrapper for the OpenDRIVE classes from the parser.
     */
    class OpenDriveWrapper {

        /**
         * The s coordinate of the opendrive object.
         */
        double s;

    public:

        /**
         * @constructor
         */
        explicit OpenDriveWrapper(double s = 0);

        /**
         * @destructor
         */
        virtual ~OpenDriveWrapper() = default;

        /**
         * @get
         */
        double getS() const;

    };
}


#endif //OPENDRIVE_LISTCOMPOSITE_H
