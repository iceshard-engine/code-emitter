#include <ice/output/elements/assignment.hxx>

namespace ice::output
{

    template<>
    auto ice::output::identifier(const Assignment& data) noexcept -> std::string
    {
        return { "operator:'" + data.operator_value + "'" };
    }

    ASTAssignment::ASTAssignment(const Assignment& assignment_data) noexcept
        : ASTElement{ ice::output::identifier(assignment_data) }
    { }

} // namespace output
