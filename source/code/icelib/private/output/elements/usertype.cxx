#include <ice/output/elements/usertype.hxx>
#include <algorithm>
#include <numeric>

namespace ice::output
{

    auto to_string(AccessSpecifier::Type type) noexcept -> std::string
    {
        switch (type)
        {
#define CASE(value, name) \
    case value:           \
        return name
            CASE(AccessSpecifier::Type::Private, "private");
            CASE(AccessSpecifier::Type::Protected, "protected");
            CASE(AccessSpecifier::Type::Public, "public");
#undef CASE
        }
        return "<unknown>";
    }

    auto to_string(UserType::Type type) noexcept -> std::string
    {
        switch (type)
        {
#define CASE(value, name) \
    case value:           \
        return name
            CASE(UserType::Type::Class, "class");
            CASE(UserType::Type::Struct, "struct");
#undef CASE
        }
        return "<unknown>";
    }

    template<>
    auto ice::output::identifier(AccessSpecifier const& data) noexcept -> std::string
    {
        return { "access_specifier:" + to_string(data.type) + ":" + data.unique.value, true };
    }

    template<>
    auto ice::output::identifier(UserType const& data) noexcept -> std::string
    {
        std::string result{ "usertype:" + to_string(data.type) + ":" };
        result += data.is_friend_declaration ? "friend-" : "";
        result += (data.is_declaration || data.is_friend_declaration) ? "declaration:" : "";
        result += data.parent_namespace + ".";
        result += data.name;
        result += std::accumulate(data.template_arguments.begin(), data.template_arguments.end(), std::string{ "{" }, [](std::string left, const UserType::TemplateArgument& arg) {
            return std::move(left) + "," + arg.name + (arg.specialization.empty() ? "" : "{" + arg.specialization + "}");
        });
        return result;
    }

} // namespace ice::output
