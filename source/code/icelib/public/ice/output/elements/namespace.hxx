#pragma once
#include <ice/output/elements/base/container.hxx>

namespace ice::output
{


    struct Namespace
    {
        std::string name;

        bool emit_unnamed{ true };
    };


    template<>
    auto identifier(const Namespace& data) noexcept -> std::string;


    class ASTNamespace : public ASTContainer
    {
    public:
        explicit ASTNamespace(const Namespace& data) noexcept;
    };


} // namespace ice::output
