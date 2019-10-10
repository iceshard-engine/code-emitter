#pragma once
#include <ice/output/element.hxx>
#include <ice/output/elements/types.hxx>

namespace ice::output
{


    struct Invoke
    {
        std::string name;

        std::vector<std::string> arguments{ };

        Type result_type{ ice::output::t_void };

        bool is_unlimited{ false };

        std::string parent_namespace{ };

        struct Unique
        {
            std::string value{ };
        };

        Unique unique{ "" };
    };


    struct Initializer : Invoke
    {
    };


    template<>
    auto identifier(const Invoke& data) noexcept -> std::string;

    template<>
    auto identifier(const Initializer& data) noexcept -> std::string;


    class ASTInvokeable : public ASTElement
    {
    public:
        explicit ASTInvokeable(const Invoke& invoke_data) noexcept;

        template<class T>
        auto set_argument(std::string name, const T& element_data, bool new_line = false) noexcept -> auto&;

        template<class T>
        auto chain_element(const T& data) noexcept -> auto&;

        template<class T>
        auto append_element(const T& data) noexcept -> auto&;

    protected:
        explicit ASTInvokeable(std::string element_identifier) noexcept;

        virtual auto get_element(
            std::string dataid
        ) const noexcept -> ASTElement* = 0;

        virtual auto set_element(
            std::unique_ptr<ASTElement> element
            , bool chained
        ) noexcept -> ASTElement* = 0;

        virtual auto get_argument_value(
            std::string argname
            , std::string argid
        ) const noexcept -> ASTElement* = 0;

        virtual auto set_argument_value(
            std::string argname
            , std::unique_ptr<ASTElement> element
            , bool newline
        ) noexcept -> ASTElement* = 0;
    };

    template<class T>
    auto ASTInvokeable::set_argument(std::string name, const T& element_data, bool new_line /*= false*/) noexcept -> auto&
    {
        using return_type_raw = decltype(factory().create(element_data));
        using return_type = typename std::decay_t<return_type_raw>::element_type;

        auto* element = static_cast<return_type*>(get_argument_value(name, ice::output::identifier(element_data)));
        if (element == nullptr)
        {
            element = static_cast<return_type*>(set_argument_value(
                std::move(name),
                factory().create(element_data),
                new_line
            ));
        }
        return *element;
    }

    template<class T>
    auto ASTInvokeable::chain_element(const T& element_data) noexcept -> auto&
    {
        using return_type_raw = decltype(factory().create(element_data));
        using return_type = typename std::decay_t<return_type_raw>::element_type;

        auto result = get_element(ice::output::identifier(element_data));
        if (nullptr == result)
        {
            result = set_element(factory().create(element_data), true);
        }
        return *static_cast<return_type*>(result);
    }

    template<class T>
    auto ASTInvokeable::append_element(const T& element_data) noexcept -> auto&
    {
        using return_type_raw = decltype(factory().create(element_data));
        using return_type = typename std::decay_t<return_type_raw>::element_type;

        auto result = get_element(ice::output::identifier(element_data));
        if (nullptr == result)
        {
            result = set_element(factory().create(element_data), false);
        }
        return *static_cast<return_type*>(result);
    }


} // namespace ice::output
