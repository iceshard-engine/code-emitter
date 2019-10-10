#pragma once
#include <ice/output/elements/base/container.hxx>
#include <ice/output/elements/type.hxx>

#include <unordered_map>
#include <vector>

namespace ice::output
{


    struct Constructor
    {
        std::string name;

        std::string parent_namespace{ };

        struct Argument
        {
            Type type;

            std::string name{ "" };

            bool maybe_unused{ false };
        };

        std::vector<Argument> arguments{ };

        bool is_inline{ false };

        bool is_explicit{ false };

        bool is_noexcept{ false };

        bool is_default{ false };

        bool is_delete{ false };

        bool is_declaration{ false };
    };

    struct Destructor
    {
        std::string name;

        std::string parent_namespace{ };

        bool is_virtual{ false };

        bool is_inline{ false };

        bool is_noexcept{ false };

        bool is_override{ false };

        bool is_final{ false };

        bool is_abstract{ false };

        bool is_default{ false };

        bool is_declaration{ false };
    };


    template<>
    auto identifier(const Constructor& data) noexcept->std::string;

    template<>
    auto identifier(const Destructor& data) noexcept->std::string;


    class ASTConstructor : public ASTContainer
    {
    public:
        ASTConstructor(const Constructor& constructor_data) noexcept;

        template<class T>
        auto add_initializer(std::string name, const T& element_data) noexcept -> auto&;

    protected:
        virtual auto get_initializer_value(const std::string& name, const std::string& dataid) const noexcept -> ASTElement* = 0;

        virtual auto set_initializer_value(std::string name, std::unique_ptr<ASTElement> element) noexcept -> ASTElement* = 0;
    };


    template<class T>
    auto ASTConstructor::add_initializer(std::string name, const T& element_data) noexcept -> auto&
    {
        using return_type_raw = decltype(factory().create(element_data));
        using return_type = typename std::decay_t<return_type_raw>::element_type;

        auto* element = static_cast<return_type*>(get_initializer_value(name, ice::output::identifier(element_data)));
        if (element == nullptr)
        {
            element = static_cast<return_type*>(set_initializer_value(
                std::move(name),
                factory().create(element_data)
            ));
        }
        return *element;
    }


} // namespace ice::output
