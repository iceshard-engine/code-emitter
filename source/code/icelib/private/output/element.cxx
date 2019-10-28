#include <ice/output/element.hxx>

namespace ice::output
{

    ASTElement::ASTElement(std::string element_uuid) noexcept
        : _identifier{ std::move(element_uuid) }
    {
    }

    auto ASTElement::identifier() const noexcept -> std::string_view
    {
        return _identifier;
    }

    ASTContainerElement::ASTContainerElement(std::string element_uuid) noexcept
        : ASTElement{ std::move(element_uuid) }
    {
    }

} // namespace ice::output
