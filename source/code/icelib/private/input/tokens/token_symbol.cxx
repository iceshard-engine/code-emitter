#pragma once
#include <ice/input/tokens.hxx>

namespace ice::input
{

    auto parse_symbol_token(std::istream& stream, Position& position, int& character) noexcept -> token
    {
        token result{
            .type = TokenType::Symbol,
            .position = position
        };

        while (character == '_' || std::isalnum(character))
        {
            result.value += static_cast<char>(character);
            position.line_position += 1;
            character = stream.get();
        }

        return std::move(result);
    }

} // namespace ice::input
