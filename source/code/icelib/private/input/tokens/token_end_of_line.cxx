#pragma once
#include <ice/input/tokens.hxx>
#include <ice/assert.hxx>

namespace ice::input
{
    namespace detail
    {

        static constexpr char c_nl = '\n';
        static constexpr char c_cr = '\r';

    } // namespace detail

    auto parse_end_of_line_token(std::istream& stream, Position& position, int& character) noexcept -> token
    {
        auto result = token{
            .type = TokenType::EndOfLine,
            .position = position,
            .value = "\\n"
        };

        if (character == detail::c_cr)
        {
            character = stream.get();
            result.value = "\\r\\n";
        }

        ht_assert_pos(
            position,
            character == detail::c_nl,
            "Invalid character while parsing <end-of-line> token."
        );

        position.line += 1;
        position.line_position = 1;

        character = stream.get();

        return std::move(result);
    }

} // namespace ice::input
