#pragma once
#include <ice/input/tokens.hxx>
#include <ice/assert.hxx>

namespace ice::input
{

    auto parse_invalid_token(std::istream& stream, Position& position, int& character) noexcept -> token
    {
        auto result = token{
            .type = TokenType::Invalid,
            .position = position,
            .value = std::string(1, static_cast<char>(character))
        };

        position.line_position += 1;
        character = stream.get();

        return std::move(result);
    }

} // namespace ice::input
