#pragma once
#include <ice/output/element.hxx>

namespace ice::output
{

    struct Line
    {
        std::string value{ "" };

        struct Unique
        {
            std::string value{};
        };

        Unique unique{ "" };
    };

    template<>
    auto identifier(Line const&) noexcept -> std::string;

} // namespace ice::output
