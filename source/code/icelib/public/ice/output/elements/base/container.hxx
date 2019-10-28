#pragma once
#include <ice/output/element.hxx>
#include <vector>

namespace ice::output
{

    struct Container
    {
        std::string name;

        bool indented{ false };
    };

    template<>
    auto identifier(Container const&) noexcept -> std::string;

    class ASTContainer : public ASTContainerElement
    {
    public:
        explicit ASTContainer(Container const& container_data) noexcept;

        void serialize(Writer& writer) const noexcept override;

    protected:
        explicit ASTContainer(std::string identifier_value, bool indented) noexcept;

        auto get(std::string const& id) const noexcept -> ASTElement* override final;

        auto set(std::unique_ptr<ASTElement> element) noexcept -> ASTElement* override final;

        bool empty() const noexcept { return _elements.empty(); }

    private:
        const bool _indented;

        std::vector<std::unique_ptr<ASTElement>> _elements{};
    };

} // namespace ice::output
