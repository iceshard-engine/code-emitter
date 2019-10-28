#include <ice/output/elements/assignment.hxx>

namespace ice::output
{

    template<>
    auto ice::output::identifier(Assignment const& data) noexcept -> std::string
    {
        return { "operator:'" + data.operator_value + "'" };
    }

    ASTAssignment::ASTAssignment(Assignment const& assignment_data) noexcept
        : ASTElement{ ice::output::identifier(assignment_data) }
    {
    }

} // namespace ice::output
