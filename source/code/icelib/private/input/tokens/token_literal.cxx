#pragma once
#include <ice/input/tokens.hxx>
#include <ice/assert.hxx>

namespace ice::input
{
    namespace detail
    {

        constexpr int c_lf = '\n';
        constexpr int c_endoffile = -1;

    } // namespace detail

    auto parse_literal_token(std::istream& stream, Position& position, int& character) noexcept -> token
    {
        token result{
            .type = TokenType::Literal,
            .position = position
        };

        while (true)
        {
            character = stream.get();

            // Escape sequence character
            if (character == '\\')
            {
                character = stream.peek();
                // Escape the '"' character or the escape character itself.
                if (character == '\"' || character == '\\')
                {
                    result.value += '\\';
                    character = stream.get();
                    result.value += static_cast<char>(character);
                }
                else
                {
                    ht_assert(character != detail::c_lf, "Unexcpected input character! [ '{:c}' ]", character);
                    ht_assert(character != detail::c_endoffile, "Unexcpected input character! [ '{:c}' ]", character);
                    result.value += static_cast<char>(character);
                }
            }
            else
            {
                // If it's not the end of the literal, continue
                ht_assert(character != detail::c_endoffile, "Unexcpected input character! [ '{:c}' ]", character);
                if (character == '\"')
                {
                    break;
                }

                result.value += static_cast<char>(character);
            }
        }

        character = stream.get();
        position.line_position += static_cast<uint32_t>(result.value.length());

        return std::move(result);
    }

} // namespace ice::input
