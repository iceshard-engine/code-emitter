#pragma once
#include <ice/output/element.hxx>
#include <vector>

namespace ice::output
{

    struct Enum
    {
        std::string name;

        struct EnumValue
        {
            std::string name;

            std::string value{};
        };

        std::vector<EnumValue> values;

        bool is_strong{ false };

        std::string base_type{ "" };

        bool is_declaration{ false };
    };

    template<>
    auto identifier(Enum const&) noexcept -> std::string;

} // namespace ice::output
