#pragma once
#include <ice/output/elements/base/container.hxx>
#include <ice/output/writer.hxx>
#include <unordered_map>

namespace ice::output
{


    struct AccessSpecifier
    {
        enum class Type
        {
            Private,
            Protected,
            Public,
        };

        Type type;

        struct Unique
        {
            std::string value;
        };

        Unique unique{ "default" };
    };


    struct UserType
    {
        enum class Type
        {
            Class,
            Struct
        };

        Type type;

        std::string name;

        struct Parent
        {
            std::string type;

            AccessSpecifier::Type access_type{ AccessSpecifier::Type::Public };
        };

        std::vector<Parent> parents{ };

        std::string parent_namespace{ "" };

        std::string metadata{ };

        struct TemplateArgument
        {
            std::string name;

            std::string specialization{ };

            std::string default_value{ };
        };

        std::vector<TemplateArgument> template_arguments{ };

        bool is_declaration{ false };
        bool is_friend_declaration{ false };
    };


    template<>
    auto identifier(const AccessSpecifier& data) noexcept -> std::string;

    template<>
    auto identifier(const UserType& data) noexcept -> std::string;


    auto to_string(AccessSpecifier::Type type) noexcept -> std::string;

    auto to_string(UserType::Type type) noexcept -> std::string;


    class ASTAccessSpecifier : public ASTContainer
    {
    public:
        ASTAccessSpecifier(const AccessSpecifier&) noexcept;
    };


    class ASTUserType : public ASTContainer
    {
    public:
        ASTUserType(const UserType& usertype_data) noexcept;
    };


} // namespace ice::output
