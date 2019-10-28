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
    auto identifier(Namespace const& data) noexcept -> std::string;

} // namespace ice::output
