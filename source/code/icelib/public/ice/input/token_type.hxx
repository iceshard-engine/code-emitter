#pragma once
#include <cinttypes>
#include <string>
#include <fmt/format.h>

namespace ice::input
{

    //! \brief Defines all know token types.
    enum class TokenType : uint32_t
    {
        //! Invalid token (can be anything)
        Invalid = 0x00,

        //! Number token
        Symbol = 0x01,
        Number,
        Literal,
        ConstLiteral,
        Punctuation,
        Whitespace,

        EoL,
        EndOfLine = EoL,
        EoF,
        EndOfFile = EoF,

        Custom = 0x100
    };

    auto to_string(TokenType token_type) noexcept -> std::string;

} // namespace ice::input

template <>
struct fmt::formatter<ice::input::TokenType> : formatter<std::string>
{
    template <typename FormatContext>
    auto format(ice::input::TokenType token_type, FormatContext& ctx)
    {
        return formatter<std::string>::format(to_string(token_type), ctx);
    }
};
