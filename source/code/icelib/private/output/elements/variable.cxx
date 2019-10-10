#include <ice/output/elements/variable.hxx>

namespace ice::output
{

    template<>
    auto ice::output::identifier(const Variable& data) noexcept -> std::string
    {
        static int lineid = 0;

        std::string unique_value{ "" };
        if (!data.is_declaration)
        {
            if (data.unique.value.empty())
            {
                unique_value = "id." + std::to_string(lineid++) + ":";
            }
            else
            {
                unique_value = "id." + data.unique.value + ":";
            }
        }

        std::string result{ "variable:" + std::move(unique_value) };
        result += data.name;
        return result;
    }

    ASTVariable::ASTVariable(const Variable& variable_data) noexcept
        : ASTElement{ ice::output::identifier(variable_data) }
    { }

} // namespace ice::output
