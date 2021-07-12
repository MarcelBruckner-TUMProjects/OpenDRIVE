//
// Created by brucknem on 12.07.21.
//

#ifndef OPENDRIVE_1_6_FACTORYMETHODS_HPP
#define OPENDRIVE_1_6_FACTORYMETHODS_HPP


namespace opendrive {
    namespace opendrive_1_6 {

        /**
         * Factory method for opendrive V1.6 wrapper object instantiation.
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


#endif //OPENDRIVE_1_6_FACTORYMETHODS_HPP
