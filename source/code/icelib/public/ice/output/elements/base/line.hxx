#pragma once
#include <ice/output/element.hxx>

namespace ice::output
{


    struct Line
    {
        std::string value{ "" };

        struct Unique
        {
            std::string value{ };
        };

        Unique unique{ "" };
    };


    template<>
    auto identifier(const Line&) noexcept -> std::string;


    class ASTLine : public ASTElement
    {
    public:
        explicit ASTLine(const ice::output::Line& data) noexcept;
    };


} // namespace ice::output
