//
// Created by brucknem on 22.02.21.
//

#ifndef OPENDRIVE_LISTCOMPOSITE_H
#define OPENDRIVE_LISTCOMPOSITE_H

#include <string>
#include <memory>
#include "standard/OpenDRIVE_1.4H_Schema_Files.hxx"

namespace opendrive {

    /**
     * Templated wrapper for the OpenDRIVE classes from the parser.
     * @tparam S The parser type of the OpenDRIVE object.
     */
    template<class S>
    class OpenDriveWrapper {

    protected:

        /**
         * A pointer to the original parsing result.
         */
        std::shared_ptr<S> openDriveObject;

    public:

        /**
         * @constructor
         */
        explicit OpenDriveWrapper() = default;

        /**
         * @constructor
         */
        explicit OpenDriveWrapper(const S &openDriveObject);

        /**
         * @get
         */
        const std::shared_ptr<S> &getOpenDriveObject() const;

        /**
         * @get true if the object is valid, i.e. there exists an underlying parser object, false else.
         */
        bool isValid() const;

        /**
         * @operator true if the id of the underlying parser object is equal to the given id, false else.
         */
        virtual bool operator==(const std::string &id) = 0;

    };

}


#endif //OPENDRIVE_LISTCOMPOSITE_H
