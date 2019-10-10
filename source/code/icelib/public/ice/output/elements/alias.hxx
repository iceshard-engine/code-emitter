#pragma once
#include <ice/output/element.hxx>

namespace ice::output
{


    struct Alias
    {
        std::string name;

        std::string type;
    };


    template<>
    auto identifier(const Alias& alias_data) noexcept -> std::string;


    class ASTAlias : public ASTElement
    {
    public:
        explicit ASTAlias(const Alias& alias_data) noexcept;
    };


} // namespace ice::output
