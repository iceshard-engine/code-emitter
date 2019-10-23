#pragma once
#include <ice/input/tokens.hxx>
#include <ice/assert.hxx>

namespace ice::input
{

    auto parse_punctuation_token(std::istream& stream, Position& position, int& character) noexcept -> token
    {
        token result{
            .type = TokenType::Punctuation,
            .position = position
        };

        result.value = static_cast<char>(character);
        switch (character)
        {
        case '!': // Looking for either ! or !=
        {
            character = stream.peek();
            if (character == '=')
            {
                character = stream.get();
                result.value += static_cast<char>(character);
            }
            break;
        }
        case '#': // Looking for either # or ##
        {
            character = stream.peek();
            if (character == '#')
            {
                character = stream.get();
                result.value += static_cast<char>(character);
            }
            break;
        }
        case '%': // Looking for either % or %=
        {
            character = stream.peek();
            if (character == '=')
            {
                character = stream.get();
                result.value += static_cast<char>(character);
            }
            break;
        }
        case '&': // Looking for either &, && or &=
        {
            character = stream.peek();
            if (character == '&' || character == '=')
            {
                character = stream.get();
                result.value += static_cast<char>(character);
            }
            break;
        }
        case '*': // Looking for either * or *=
        {
            character = stream.peek();
            if (character == '=')
            {
                character = stream.get();
                result.value += static_cast<char>(character);
            }
            break;
        }
        case '+': // Looking for either +, ++, or +=
        {
            character = stream.peek();
            if (character == '+' || character == '=')
            {
                character = stream.get();
                result.value += static_cast<char>(character);
            }
            break;
        }
        case '-': // Looking for either -, --, -=, ->, ->*
        {
            character = stream.peek();
            if (character == '-' || character == '=')
            {
                character = stream.get();
                result.value += static_cast<char>(character);
            }
            else if (character == '>')
            {
                character = stream.get();
                result.value += static_cast<char>(character);

                character = stream.peek();
                if (character == '*')
                {
                    character = stream.get();
                    result.value += static_cast<char>(character);
                }
            }
            break;
        }
        case '.': // Looking for either . , .* or ...
        {
            character = stream.peek();
            if (character == '.')
            {
                character = stream.get();
                character = stream.peek();
                ht_assert(character == '.', "Invalid punctuation found! [ got: '..', expected: '.' or '...' ]");

                character = stream.get();
                result.value += "..";
            }
            else if (character == '*')
            {
                character = stream.get();
                result.value += static_cast<char>(character);
            }
            break;
        }
        case '/': // Looking for either / or /=
        {
            character = stream.peek();
            if (character == '=')
            {
                character = stream.get();
                result.value += static_cast<char>(character);
            }
            break;
        }
        case ':': // Looking for either : or ::
        {
            character = stream.peek();
            if (character == ':')
            {
                character = stream.get();
                result.value += static_cast<char>(character);
            }
            break;
        }
        case '<': // Looking for either < or <=, <<, or <<=
        {
            character = stream.peek();
            if (character == '=')
            {
                character = stream.get();
                result.value += static_cast<char>(character);
            }
            else if (character == '<')
            {
                character = stream.get();
                result.value += static_cast<char>(character);

                character = stream.peek();
                if (character == '=')
                {
                    character = stream.get();
                    result.value += static_cast<char>(character);
                }
            }
            break;
        }
        case '=': // Looking for either = or ==
        {
            character = stream.peek();
            if (character == '=')
            {
                character = stream.get();
                result.value += static_cast<char>(character);
            }
            break;
        }
        case '>': // Looking for either >, >=, >>, or >>=
        {
            character = stream.peek();
            if (character == '=')
            {
                character = stream.get();
                result.value += static_cast<char>(character);
            }
            else if (character == '>')
            {
                character = stream.get();
                result.value += static_cast<char>(character);

                character = stream.peek();
                if (character == '=')
                {
                    character = stream.get();
                    result.value += static_cast<char>(character);
                }
            }
            break;
        }
        case '|': // Looking for either |, |=, or ||
        {
            character = stream.peek();
            if (character == '=' || character == '|')
            {
                character = stream.get();
                result.value += static_cast<char>(character);
            }
            break;
        }
        case '[': // Looking for either [ or [[
        {
            character = stream.peek();
            if (character == '[')
            {
                character = stream.get();
                result.value += static_cast<char>(character);
            }
            break;
        }
        case ']': // Looking for either ] or ]]
        {
            character = stream.peek();
            if (character == ']')
            {
                character = stream.get();
                result.value += static_cast<char>(character);
            }
            break;
        }
        }

        character = stream.get();
        position.line_position += static_cast<uint32_t>(result.value.length());

        return std::move(result);
    }

} // namespace ice::input
