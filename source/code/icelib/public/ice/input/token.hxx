#pragma once
#include <ice/input/position.hxx>
#include <ice/input/token_type.hxx>
#include <istream>

namespace ice::input
{

    //! \brief This defines token.
    struct token
    {
        //! \brief Type of the token.
        TokenType type;

        //! \brief Position of the token.
        Position position;

        //! \brief Value of the token.
        std::string value;
    };

    //! \brief Creates a string containing all information helpful while debugging.
    auto debug_string(token const& token) noexcept -> std::string;

} // namespace ice::input

template<>
struct fmt::formatter<ice::input::token> : formatter<std::string>
{
    template<typename FormatContext>
    auto format(const ice::input::token& token, FormatContext& ctx)
    {
        return formatter<std::string>::format(debug_string(token), ctx);
    }
};
