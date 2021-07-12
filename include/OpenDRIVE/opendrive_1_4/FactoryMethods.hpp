//
// Created by brucknem on 12.07.21.
//

#ifndef OPENDRIVE_1_4_FACTORYMETHODS_HPP
#define OPENDRIVE_1_4_FACTORYMETHODS_HPP

#include <string>
#include <map>
#include <OpenDRIVE/HDMap.hpp>
#include <opendrive_1_4/OpenDRIVE_1.4H_Schema_Files.hxx>
#include "OpenDRIVE/Road.hpp"

namespace opendrive {
    namespace opendrive_1_4 {

        /**
         * Factory method for opendrive V1.4 wrapper object instantiation.
         *
         * @tparam T The resulting object type.
         * @tparam V The input object type.
         * @param obj The raw object.
         * @return The wrapper object of type T.
         */
        template<typename T, typename V>
        T create(const V &obj);
    }
}


#endif //OPENDRIVE_1_4_FACTORYMETHODS_HPP
