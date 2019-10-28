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
    auto identifier(Alias const& alias_data) noexcept -> std::string;

} // namespace ice::output
