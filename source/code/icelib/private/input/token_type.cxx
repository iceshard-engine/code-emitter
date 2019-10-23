#include <ice/input/token_type.hxx>

namespace ice::input
{

    auto to_string(TokenType token_type) noexcept -> std::string
    {
        switch (token_type)
        {
        case ice::input::TokenType::Invalid:
            return "Invalid";
        case ice::input::TokenType::Symbol:
            return "Symbol";
        case ice::input::TokenType::Number:
            return "Number";
        case ice::input::TokenType::Literal:
            return "Literal";
        case ice::input::TokenType::ConstLiteral:
            return "ConstLiteral";
        case ice::input::TokenType::Punctuation:
            return "Punctuation";
        case ice::input::TokenType::Whitespace:
            return "Whitespace";
        case ice::input::TokenType::EndOfLine:
            return "EndOfLine";
        case ice::input::TokenType::EndOfFile:
            return "EndOfFile";
        default:
            break;
        }
        // Custom token
        return "Custom";
    }

} // namespace ice::input
