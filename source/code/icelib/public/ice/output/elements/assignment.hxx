#pragma once
#include <ice/output/elements/types.hxx>

namespace ice::output
{

    struct Assignment
    {
        std::string operator_value{ "=" };

        Type target_type{ ice::output::t_auto };

        Type source_type{ ice::output::t_auto };
    };

    template<>
    auto identifier(Assignment const&) noexcept -> std::string;

    class ASTAssignment : public ASTElement
    {
    public:
        ASTAssignment(Assignment const& assignment_data) noexcept;

        template<class T>
        auto append_element(T const& data) noexcept -> auto&;

    protected:
        virtual auto get_element(std::string const& dataid) const noexcept -> ASTElement* = 0;

        virtual auto set_element(std::unique_ptr<ASTElement> element) noexcept -> ASTElement* = 0;
    };

    template<class T>
    auto ASTAssignment::append_element(T const& element_data) noexcept -> auto&
    {
        using return_type_raw = decltype(factory().create(element_data));
        using return_type = typename std::decay_t<return_type_raw>::element_type;

        auto result = get_element(ice::output::identifier(element_data));
        if (nullptr == result)
        {
            result = set_element(factory().create(element_data));
        }
        return *static_cast<return_type*>(result);
    }

} // namespace ice::output
