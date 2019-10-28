#pragma once
#include <ice/output/element.hxx>
#include <unordered_map>
#include <set>

namespace ice::output
{

    //! Defines a type object, which holds a given type and may be nested.
    class Type
    {
    public:
        //! Possible type properties.
        enum class Property
        {
            CONSTANT,
            POINTER,
            CONSTANT_POINTER,
            REFERENCE,
            VOLATILE,
            NATIVE,
            TEMPLATE,
            TEMPLATE_SPECIALIZED,
            LOCKED
        };

        //! Creates an 'void' type.
        Type();

        //! Creates a 'Type' object from the given string.
        Type(std::string name);

        //! Creates a 'Type' object from the given string and template parameters.
        Type(std::string name, std::vector<std::string> template_args);

        //! Creates a 'Type' object from the given string and properties.
        Type(std::string name, std::set<Property> properties);

        //! Creates a 'Type' object from the given string and template parameters.
        Type(std::string name, std::vector<std::string> template_args, std::set<Property> properties);

        //! Returns a new type with the same flags using the given format to change the name.
        Type transform(std::string const& format);

        //! Returns a new type specialized with the given vector of values.
        Type specialize(std::unordered_map<std::string, std::string> const& args);

        //! The type identifier.
        auto identifier() const noexcept -> std::string;

        //! The types base name.
        auto basename() const -> auto const& { return _name; }

        //! The type template argument names.
        auto template_arguments() const -> auto const& { return _template_args; }

        //! The type template specialized argument map.
        auto template_specializations() const -> auto const& { return _specialized_args; }

        //! Serializes the type template part if existing.
        void serialize_template(Writer& strm) const;

        //! Returns true if the given type is a complex type.
        bool is_template() const { return has(Property::TEMPLATE); }

        //! Returns true if the given type is a const type.
        bool is_const() const { return has(Property::CONSTANT) || has(Property::CONSTANT_POINTER); }

        //! Returns true if the given type is a native type.
        bool is_native() const { return has(Property::NATIVE); }

        //! Returns true if the given type is a pointer.
        bool is_pointer() const { return has(Property::POINTER) || has(Property::CONSTANT_POINTER); }

        //! Returns true if the given type is a pointer.
        bool is_reference() const { return has(Property::REFERENCE); }

        //! Returns the const version of the given type.
        Type to_const() const;

        //! Returns the pointer version of the given type.
        Type to_pointer() const;

        //! Returns the reference version of the given type.
        Type to_reference() const;

        //! Returns the base type.
        Type to_base() const;

    protected:
        //! Creates copy of the 'Type' object but with a different base name.
        //! \note used by the Type::mutate method.
        Type(Type const& other, std::string name);

        //! Checks for the given property.
        bool has(Property prop) const;

    private:
        //! The type name.
        std::string _name;

        //! The type template arguments.
        std::vector<std::string> _template_args;

        //! The type template specialized arguments.
        std::unordered_map<std::string, std::string> _specialized_args;

        //! The type properties.
        std::set<Property> _properties;
    };

} // namespace ice::output
