#pragma once
#include <ice/output/element.hxx>

namespace ice::output
{

    struct Value
    {
        std::string value{ "" };

        bool quote_value{ false };

        struct Unique
        {
            std::string value{ "" };
        };

        Unique unique{ "not_unique" };
    };

    template<>
    auto identifier(Value const&) noexcept -> std::string;

} // namespace ice::output
