#include <ice/output/elements/alias.hxx>

namespace ice::output
{

    template<>
    auto identifier(const Alias & data) noexcept -> std::string
    {
        return { "alias:" + data.name + "{" + data.type + "}" };
    }

    ASTAlias::ASTAlias(const Alias& alias_data) noexcept
        : ASTElement{ ice::output::identifier(alias_data) }
    { }

} // namespace ice::output
