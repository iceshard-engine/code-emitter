#pragma once
#include <ice/input/token.hxx>

#include <unordered_map>
#include <vector>
#include <string>

namespace ice::input
{

    //! \brief This type defines a single argument that can be passed to an attribute.
    struct AttributeArgument
    {
        //! \brief Tokens part of the argument.
        std::vector<token> tokens;
    };

    //! \brief This type defines an single attribute instance.
    //!
    //! \details An instance is a single occurance in one or many attribute lists.
    //!     Instances can be the exact duplicates but dont need to be.
    struct AttributeInstance
    {
        //! \brief Arguments passed to the attribute.
        std::vector<AttributeArgument> arguments;
    };

    //! \brief Defines a named attribute.
    struct Attribute
    {
        //! \brief Attribute name.
        std::string name;

        //! \brief All instances of the given attribute.
        std::vector<AttributeInstance> instances;
    };

    //! \brief Defines a list of attributes attached to an entity.
    struct AttributeList
    {
        //! \brief Map of attributes.
        std::unordered_map<std::string, Attribute> attributes;
    };

} // namespace ice::input
