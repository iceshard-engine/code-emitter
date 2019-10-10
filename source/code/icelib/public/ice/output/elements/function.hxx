#pragma once
#include <ice/output/elements/types.hxx>
#include <vector>


namespace ice::output
{


    struct Function
    {
        std::string name;

        std::string parent_namespace{ };

        struct Argument
        {
            Type type;

            std::string name{ "" };

            bool maybe_unused{ false };
        };

        std::vector<Argument> arguments{ };

        Type return_type{ ice::output::t_void };

        std::string metadata{ };

        bool is_const{ false };

        bool is_constexpr{ false };

        bool is_noexcept{ false };

        bool is_friend{ false };

        bool is_virtual{ false };

        bool is_inline{ false };

        bool is_static{ false };

        bool is_delete{ false };

        bool is_override{ false };

        bool is_final{ false };

        bool is_abstract{ false };

        bool is_declaration{ false };
    };


    template<>
    auto identifier(const Function& data) noexcept -> std::string;


} // namespace ice::output
