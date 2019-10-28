#pragma once
#include <ice/output/element.hxx>
#include <vector>

namespace ice::output
{

    struct Pragma
    {
        std::string command;

        std::vector<std::string> arguments{};
    };

    template<>
    auto identifier(Pragma const&) noexcept -> std::string;

} // namespace ice::output
