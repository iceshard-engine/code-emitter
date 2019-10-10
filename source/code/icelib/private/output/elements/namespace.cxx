#include <ice/output/elements/namespace.hxx>

namespace ice::output
{

    template<>
    auto ice::output::identifier(const Namespace& data) noexcept -> std::string
    {
        return "namespace:" + data.name;
    }

    ASTNamespace::ASTNamespace(const Namespace& data) noexcept
        : ASTContainer{ ice::output::identifier(data), false }
    { }

} // namespace ice::output
