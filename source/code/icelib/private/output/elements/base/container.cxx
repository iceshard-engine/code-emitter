#include <ice/output/elements/base/container.hxx>
#include <ice/output/writer.hxx>
#include <algorithm>

namespace ice::output
{

    template<>
    auto ice::output::identifier(const Container& data) noexcept -> std::string
    {
        return "container:" + data.name;
    }

    ASTContainer::ASTContainer(const Container& container_data) noexcept
        : ASTContainerElement{ ice::output::identifier(container_data) }
        , _indented{ container_data.indented}
    { }

    ASTContainer::ASTContainer(std::string identifier_value, bool indented) noexcept
        : ASTContainerElement{ std::move(identifier_value) }
        , _indented{ indented }
    { }

    void ASTContainer::serialize(Writer& writer) const noexcept
    {
        if (_indented)
        {
            writer << push;
        }

        for (auto& child : _elements)
        {
            child->serialize(writer);
        }

        if (_indented)
        {
            writer << pop;
        }
    }

    auto ASTContainer::get(const std::string& id) const noexcept -> ASTElement*
    {
        auto it = std::find_if(_elements.begin(), _elements.end(), [&](auto& e)
            {
                return e->identifier() == id;
            });

        return it == _elements.end() ? nullptr : it->get();
    }

    auto ASTContainer::set(std::unique_ptr<ASTElement> element) noexcept -> ASTElement*
    {
        auto* result = element.get();
        _elements.emplace_back(std::move(element));
        return result;
    }

} // namespace ice::output
