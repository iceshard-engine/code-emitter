#include <ice/output/elements/type.hxx>
#include <ice/assert.hxx>
#include <unordered_map>
#include <regex>
#include "..\..\..\public\ice\output\elements\type.hxx"

namespace ice::output
{

    namespace detail
    {

        bool type_all_args_specialized(
            std::vector<std::string> const& args,
            std::unordered_map<std::string, std::string> const& specialized)
        {
            bool result = true;
            std::for_each(args.begin(), args.end(), [&](const auto& arg) {
                result &= specialized.count(arg) > 0;
            });
            return result;
        }

        std::string type_template_args(
            std::vector<std::string> const& args,
            std::unordered_map<std::string, std::string> const& specialized,
            std::string const& prefix,
            bool ignore_specialized)
        {
            if (args.empty())
            {
                return "";
            }

            std::vector<std::string> results;
            for (auto const& arg : args)
            {
                auto spec_arg_it = specialized.find(arg);
                if (ignore_specialized && spec_arg_it != specialized.end())
                {
                    continue;
                }

                if (spec_arg_it != specialized.end())
                {
                    results.emplace_back(spec_arg_it->second);
                }
                else
                {
                    results.emplace_back(arg);
                }
            }

            if (results.empty())
            {
                return "";
            }

            auto it = results.begin();
            auto end = results.end();

            std::string result = "<" + prefix + *it;
            std::for_each(std::next(it), end, [&](std::string const& str) {
                result += ", " + prefix + str;
            });
            return result + ">";
        }

        std::string type_template_args_identifier(std::vector<std::string> const& args, std::unordered_map<std::string, std::string> const& specialized)
        {
            return type_template_args(args, specialized, "", false);
        }

    } // namespace detail

    Type::Type()
        : _name{ "void" }
        , _template_args{}
        , _specialized_args{}
        , _properties{ Property::NATIVE }
    {
    }

    Type::Type(std::string name)
        : _name{ std::move(name) }
        , _template_args{}
        , _specialized_args{}
        , _properties{}
    {
    }

    Type::Type(std::string name, std::vector<std::string> template_args)
        : _name{ std::move(name) }
        , _template_args{ std::move(template_args) }
        , _specialized_args{}
        , _properties{}
    {
        if (!_template_args.empty())
        {
            _properties.insert(Property::TEMPLATE);
        }
    }

    Type::Type(std::string name, std::set<Property> properties)
        : _name{ std::move(name) }
        , _template_args{}
        , _specialized_args{}
        , _properties{ std::move(properties) }
    {
    }

    Type::Type(std::string name, std::vector<std::string> template_args, std::set<Property> properties)
        : _name{ std::move(name) }
        , _template_args{ std::move(template_args) }
        , _specialized_args{}
        , _properties{ std::move(properties) }
    {
        if (!_template_args.empty())
        {
            _properties.insert(Property::TEMPLATE);
        }
    }

    Type::Type(Type const& other, std::string name)
        : _name{ std::move(name) }
        , _template_args{ other._template_args }
        , _specialized_args{ other._specialized_args }
        , _properties{ other._properties }
    {
    }

    ice::output::Type Type::transform(std::string const& format)
    {
        return { *this, std::regex_replace(format, std::regex{ R"_(\{\})_" }, _name) };
    }

    ice::output::Type Type::specialize(std::unordered_map<std::string, std::string> const& specialization_map)
    {
        // If the map is empty just return the copy of this type
        if (specialization_map.empty())
        {
            return *this;
        }

        ht_assert(has(Property::TEMPLATE), "Cannot specialize a non-template type! [ type identifier: {} ]", identifier());
        Type new_type{ _name, _template_args, _properties };

        // Copy old values
        new_type._specialized_args = _specialized_args;

        // Set new values to the map.
        for (const auto& entry : specialization_map)
        {
            if (new_type._specialized_args.count(entry.first) > 0)
            {
                new_type._specialized_args.erase(entry.first);
            }
            new_type._specialized_args.emplace(entry.first, entry.second);
        }

        new_type._properties.insert(Property::TEMPLATE_SPECIALIZED);
        return new_type;
    }

    auto Type::identifier() const noexcept -> std::string
    {
        return "";
    }

    Type Type::to_const() const
    {
        ht_assert(!has(Property::LOCKED), "Cannot modify a locked type! [ type identifier: {} ]", identifier());

        auto new_properties = _properties;
        if (has(Property::POINTER))
        {
            new_properties.emplace(Property::CONSTANT_POINTER);
        }
        else
        {
            new_properties.emplace(Property::CONSTANT);
        }

        if (has(Property::TEMPLATE_SPECIALIZED))
        {
            new_properties.emplace(Property::TEMPLATE_SPECIALIZED);
        }

        Type new_type = { _name, _template_args, new_properties };
        new_type._specialized_args = _specialized_args;
        return new_type;
    }

    Type Type::to_pointer() const
    {
        ht_assert(!has(Property::LOCKED), "Cannot modify a locked type! [ type identifier: {} ]", identifier());

        auto new_properties = _properties;
        new_properties.emplace(Property::POINTER);

        if (has(Property::TEMPLATE_SPECIALIZED))
        {
            new_properties.emplace(Property::TEMPLATE_SPECIALIZED);
        }

        Type new_type = { _name, _template_args, new_properties };
        new_type._specialized_args = _specialized_args;
        return new_type;
    }

    Type Type::to_reference() const
    {
        ht_assert(!has(Property::LOCKED), "Cannot modify a locked type! [ type identifier: {} ]", identifier());

        auto new_properties = _properties;
        new_properties.emplace(Property::REFERENCE);

        if (has(Property::TEMPLATE_SPECIALIZED))
        {
            new_properties.emplace(Property::TEMPLATE_SPECIALIZED);
        }

        Type new_type = { _name, _template_args, new_properties };
        new_type._specialized_args = _specialized_args;
        return new_type;
    }

    Type Type::to_base() const
    {
        std::set<Property> properties;

        if (is_native())
        {
            properties.emplace(Property::NATIVE);
        }

        if (is_template())
        {
            properties.emplace(Property::TEMPLATE);
        }

        if (has(Property::LOCKED))
        {
            properties.emplace(Property::LOCKED);
        }

        return { _name, _template_args, _properties };
    }

    bool Type::has(Property prop) const
    {
        return _properties.count(prop) > 0;
    }

} // namespace ice::output
