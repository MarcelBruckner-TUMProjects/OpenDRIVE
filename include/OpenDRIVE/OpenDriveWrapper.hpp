//
// Created by brucknem on 22.02.21.
//

#ifndef OPENDRIVE_LISTCOMPOSITE_H
#define OPENDRIVE_LISTCOMPOSITE_H

#include <string>
#include <memory>
#ifndef OPENDRIVE_1_6
#include "standard_1_4/OpenDRIVE_1.4H_Schema_Files.hxx"
#endif
#include "Vector.hpp"

namespace opendrive {

    /**
     * Templated wrapper for the OpenDRIVE classes from the parser.
     * @tparam T The parser type of the OpenDRIVE object.
     */
    template<class T>
    class OpenDriveWrapper {

    protected:

        /**
         * A Pointer to the original parsing result.
         */
        std::shared_ptr<T> openDriveObject;

    public:

        /**
         * @constructor
         */
        explicit OpenDriveWrapper() = default;

        /**
         * @constructor
         */
        explicit OpenDriveWrapper(const T &openDriveObject);

        /**
         * @destructor
         */
        virtual ~OpenDriveWrapper() = default;

        /**
         * @get
         */
        const std::shared_ptr<T> &getOpenDriveObject() const;

        /**
         * @get true if the object is valid, i.e. there exists an underlying parser object, false else.
         */
        bool isValid() const;
    };


    /**
     * Templated wrapper for the OpenDRIVE classes from the parser for objects with a s coordinate.
     * @tparam T The parser type of the OpenDRIVE object.
     */
    template<class T>
    class OpenDriveWrapperWithCoordinate : public OpenDriveWrapper<T> {
    public:
        /**
         * @constructor
         */
        explicit OpenDriveWrapperWithCoordinate() = default;

        /**
         * @constructor
         */
        explicit OpenDriveWrapperWithCoordinate(const T &openDriveObject);

        /**
         * @destructor
         */
        virtual ~OpenDriveWrapperWithCoordinate() = default;

        /**
         * @get s-coordinate of start position.
         */
        virtual double getSCoordinate() const;
    };
}


#endif //OPENDRIVE_LISTCOMPOSITE_H
