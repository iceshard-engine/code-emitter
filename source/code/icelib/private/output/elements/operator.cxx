#include <ice/output/elements/operator.hxx>
#include <fmt/format.h>

namespace ice::output
{

    template<>
    auto identifier(const UnaryOperator& data) noexcept -> std::string
    {
        std::string result{ "operator:unary." };
        result += data.wrap_expression ? "wrapped." : "";
        result += data.postfix_operator ? "postfix:" : "prefix:";
        result += "'" + data.result_type.identifier() + "'";
        return result;
    }

    template<>
    auto identifier(const BinaryOperator& data) noexcept -> std::string
    {
        std::string result{ "operator:binary." };
        result += data.wrap_expression ? "wrapped." : "";
        result += "'" + data.result_type.identifier() + "'";
        return result;
    }

    template<>
    auto identifier(const InvokeOperator& data) noexcept -> std::string
    {
        static int lineid = 0;

        auto unique_value{ data.unique.value };
        if (unique_value.empty())
        {
            unique_value = "id." + std::to_string(lineid++);
        }

        std::string result{ "operator:" + std::move(unique_value) + ":invoke." };
        result += data.is_unlimited ? "unlimited." : "";
        result += fmt::format("{}{}:", data.brackets.first, data.brackets.second);
        result += "'" + data.result_type.identifier() + "'";
        return result;
    }

    ASTUnaryOperator::ASTUnaryOperator(const UnaryOperator& data) noexcept
        : ASTElement{ ice::output::identifier(data) }
    { }

    ASTBinaryOperator::ASTBinaryOperator(const BinaryOperator& data) noexcept
        : ASTElement{ ice::output::identifier(data) }
    { }

    ASTInvokeOperator::ASTInvokeOperator(const InvokeOperator& data) noexcept
        : ASTElement{ ice::output::identifier(data) }
    { }

} // namespace ice::output
