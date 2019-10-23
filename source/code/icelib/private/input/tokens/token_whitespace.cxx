#pragma once
#include <ice/input/tokens.hxx>
#include <cstdio>

namespace ice::input
{
    namespace detail
    {

        static constexpr char c_nl = '\n';
        static constexpr char c_cr = '\r';

    } // namespace detail

    auto parse_whitespace_token(std::istream& stream, Position& position, int& character) noexcept -> token
    {
        token result{
            .type = TokenType::Whitespace,
            .position = position
        };

        while (std::isspace(character) && (character != detail::c_nl && character != detail::c_cr))
        {
            result.value += static_cast<char>(character);
            position.line_position += 1;
            character = stream.get();
        }

        return std::move(result);
    }

} // namespace ice::input
