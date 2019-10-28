#include <ice/output/elements/invoke.hxx>
#include <algorithm>

namespace ice::output
{

    template<>
    auto ice::output::identifier(Invoke const& data) noexcept -> std::string
    {
        static int lineid = 0;

        auto unique_value{ data.unique.value };
        if (unique_value.empty())
        {
            unique_value = "id." + std::to_string(lineid++);
        }

        std::string result{ "invoke:" + std::move(unique_value) + ":" };
        result += data.is_unlimited ? "unlimited:{" : "{";
        result += data.result_type.identifier() + "}:{";
        result += data.parent_namespace + "::";
        result += data.name + "}";
        return result;
    }

    template<>
    auto ice::output::identifier(Initializer const& data) noexcept -> std::string
    {
        return "initializer:" + ice::output::identifier<Invoke>(data);
    }

    ASTInvokeable::ASTInvokeable(Invoke const& invoke_data) noexcept
        : ASTElement{ ice::output::identifier(invoke_data) }
    {
    }

    ASTInvokeable::ASTInvokeable(std::string uuid) noexcept
        : ASTElement{ std::move(uuid) }
    {
    }

} // namespace ice::output
