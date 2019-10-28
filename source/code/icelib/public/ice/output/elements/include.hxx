#pragma once
#include <ice/output/elements/base/container.hxx>
#include <vector>

namespace ice::output
{

    struct Include
    {
        std::string path;

        bool is_sysinclude{ false };
    };

    template<>
    auto identifier(Include const& data) noexcept -> std::string;

} // namespace ice::output
