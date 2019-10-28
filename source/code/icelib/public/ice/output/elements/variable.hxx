#pragma once
#include <ice/output/element.hxx>
#include <ice/output/elements/type.hxx>

namespace ice::output
{

    struct Variable
    {
        std::string name;

        Type type;

        bool is_array{ false };

        std::string array_index{ "" };

        bool is_declaration{ false };

        bool is_static{ false };

        bool is_constexpr{ false };

        struct Unique
        {
            std::string value{ "" };
        };

        Unique unique{};
    };

    template<>
    auto identifier(Variable const&) noexcept -> std::string;

    class ASTVariable : public ASTElement
    {
    public:
        ASTVariable(Variable const& variable_data) noexcept;

        template<class T>
        auto chain_element(T const& data) noexcept -> auto&;

        template<class T>
        auto append_element(T const& data) noexcept -> auto&;

        template<class T>
        auto initialize(T const& data) noexcept -> auto&;

    protected:
        virtual auto get_element(std::string uuid) const noexcept -> ASTElement* = 0;

        virtual auto set_element(std::unique_ptr<ASTElement> element, bool chained) noexcept -> ASTElement* = 0;
    };

    template<class T>
    auto ASTVariable::initialize(T const& element_data) noexcept -> auto&
    {
        return append_element(element_data);
    }

    template<class T>
    auto ASTVariable::chain_element(T const& element_data) noexcept -> auto&
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
    auto ASTVariable::append_element(T const& element_data) noexcept -> auto&
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
