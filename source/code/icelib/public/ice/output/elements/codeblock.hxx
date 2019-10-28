#pragma once
#include <ice/output/element.hxx>

namespace ice::output
{

    struct CodeBlock
    {
        std::string name;
    };

    template<>
    auto identifier(CodeBlock const&) noexcept -> std::string;

} // namespace ice::output
