#pragma once
#include <ice/input/tokens.hxx>

namespace ice::input
{

    auto parse_number_token(std::istream& stream, Position& position, int& character) noexcept -> token
    {
        token result{
            .type = TokenType::Number,
            .position = position
        };

        // Helper values
        bool number_is_integer = false;
        bool number_is_float = false;

        // Parse token
        result.value += static_cast<char>(character);

        if (character == '0')
        {
            character = stream.peek();
            if (character == 'x' || character == 'X')
            {
                character = stream.get();
                result.value += static_cast<char>(character);

                character = stream.get();
                while (std::isxdigit(character) || character == '\'')
                {
                    result.value += static_cast<char>(character);
                    character = stream.get();
                }

                number_is_integer = true;
            }

            if (character == '0' || character == '1')
            {
                character = stream.get();
                result.value += static_cast<char>(character);

                character = stream.get();
                while (character == '0' || character == '1' || character == '\'')
                {
                    result.value += static_cast<char>(character);
                    character = stream.get();
                }

                number_is_integer = true;
            }

            if (character == '.' || character == 'f')
            {
                number_is_float = true;
                result.value += static_cast<char>(character);
                character = stream.get();
            }

            if (number_is_float)
            {
                character = stream.get();

                while (std::isdigit(character) || character == '\'')
                {
                    result.value += static_cast<char>(character);
                    character = stream.get();
                }

                if (character == 'f')
                {
                    result.value += static_cast<char>(character);
                    character = stream.get();
                }
            }
            else if (!number_is_integer)
            {
                number_is_integer = true;
                character = stream.get();
            }
        }
        else
        {
            character = stream.get();
            while (std::isdigit(character) || character == '\'')
            {
                result.value += static_cast<char>(character);
                character = stream.get();
            }

            number_is_integer = true;

            if (character == '.')
            {
                number_is_float = true;
                result.value += static_cast<char>(character);
                character = stream.get();
            }

            if (number_is_float)
            {
                while (std::isdigit(character) || character == '\'')
                {
                    result.value += static_cast<char>(character);
                    character = stream.get();
                }
            }

            if (character == 'f')
            {
                result.value += static_cast<char>(character);
                number_is_float = true;
                character = stream.get();
            }
        }

        position.line_position += static_cast<uint32_t>(result.value.length());

        return std::move(result);
    }

} // namespace ice::input
