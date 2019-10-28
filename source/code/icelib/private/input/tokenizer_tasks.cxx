#include <ice/input/tokenizer_tasks.hxx>
#include <ice/input/tokens.hxx>
#include <ice/assert.hxx>

#include <sstream>
#include <istream>

//!
//! \brief The general tokenizer implementation was based on a article found here:
//!     https://www.dreamincode.net/forums/topic/153718-fundamentals-of-parsing/
//!

namespace ice::input
{
    namespace detail
    {

        constexpr int c_lf = '\n';
        constexpr int c_cr = '\r';
        constexpr int c_endoffile = -1;

        auto tokenize_stream_iternal(std::istream& stream, Position position) noexcept -> Tokenizer
        {
            ht_assert(stream.good(), "Invalid input stream object!");

            token parsed_token{
                .type = TokenType::Invalid,
                .position = position,
                .value = ""
            };

            // Run until we hit end-of-file on the stream.
            for (auto input_char = stream.get(); stream.eof() == false; /* empty */)
            {
                // Remove any comment from the source
                if (input_char == '/')
                {
                    int peek_character = stream.peek();

                    // Remove line comment
                    if (peek_character == '/')
                    {
                        while (!(peek_character == detail::c_lf || peek_character == detail::c_cr) && !stream.eof())
                        {
                            peek_character = stream.get();
                        }

                        input_char = peek_character;
                        parsed_token = parse_end_of_line_token(stream, position, input_char);
                        //token = std::make_unique<EndOfLineToken>(file, line, last_position, get_line_position(strm, last_position));
                    }

                    // Remove block comment
                    if (peek_character == '*')
                    {
                        while (parsed_token.type == TokenType::Invalid)
                        {
                            peek_character = stream.get();

                            ht_assert(peek_character != detail::c_endoffile, "Unexpected character! [ got: {:c} ]", peek_character);
                            if (peek_character == detail::c_lf || peek_character == detail::c_cr)
                            {
                                co_yield parse_end_of_line_token(stream, position, input_char);
                            }
                            else if (peek_character == '*')
                            {
                                peek_character = stream.peek();
                                ht_assert(peek_character != detail::c_endoffile, "Unexpected character! [ got: {:c} ]", peek_character);

                                if (peek_character == '/')
                                {
                                    input_char = stream.get();
                                    input_char = ' ';
                                    parsed_token = parse_whitespace_token(stream, position, input_char);
                                }
                            }
                        }
                    }

                    if (parsed_token.type == TokenType::Invalid)
                    {
                        parsed_token = parse_punctuation_token(stream, position, input_char);
                    }
                }
                else if (input_char == '_' || std::isalpha(input_char))
                {
                    parsed_token = parse_symbol_token(stream, position, input_char);
                }
                else if (input_char == detail::c_lf || input_char == detail::c_cr)
                {
                    parsed_token = parse_end_of_line_token(stream, position, input_char);
                }
                else if (std::isspace(input_char))
                {
                    parsed_token = parse_whitespace_token(stream, position, input_char);
                }
                else if (std::isdigit(input_char))
                {
                    parsed_token = parse_number_token(stream, position, input_char);
                }
                else if (input_char == '\"')
                {
                    parsed_token = parse_literal_token(stream, position, input_char);
                }
                else if (input_char == '\'')
                {
                    parsed_token = parse_const_literal_token(stream, position, input_char);
                }
                else if (std::ispunct(input_char))
                {
                    parsed_token = parse_punctuation_token(stream, position, input_char);
                }

                if (parsed_token.type == TokenType::Invalid)
                {
                    parsed_token = parse_invalid_token(stream, position, input_char);
                }

                //input_char = token->parse_token({}, strm, input_char);
                co_yield std::move(parsed_token);

                // reset the token type
                parsed_token.type = TokenType::Invalid;
            }

            // Add the EOF token to the end of the list
            co_yield ice::input::token{
                .type = TokenType::EndOfFile,
                .position = position,
                .value = ""
            };
        }

    } // namespace detail

    // The token parsing function
    auto tokenize_stream(std::istream& strm, std::optional<std::string> name) noexcept -> Tokenizer
    {
        // Initial position value
        Position position{
            .origin = name.value_or("<unknown>"),
            .line = 1,
            .line_position = 1
        };

        // Create the internal tokenizer
        auto internal_tokenizer = detail::tokenize_stream_iternal(strm, std::move(position));

        // Move yield all tokens
        for (auto token = internal_tokenizer.next_token(); internal_tokenizer.has_next_token(); token = internal_tokenizer.next_token())
        {
            co_yield std::move(token);
        }

        co_return;
    }

    auto tokenize_string(std::string contents, std::optional<std::string> name) noexcept -> Tokenizer
    {
        // Initial position value
        Position position{
            .origin = name.value_or("<unknown>"),
            .line = 1,
            .line_position = 1
        };

        // Initialize the string stream object
        std::stringstream string_stream;
        string_stream << std::move(contents);

        // Create the internal tokenizer
        auto internal_tokenizer = detail::tokenize_stream_iternal(string_stream, std::move(position));

        // Move yield all tokens
        for (auto token = internal_tokenizer.next_token(); internal_tokenizer.has_next_token(); token = internal_tokenizer.next_token())
        {
            co_yield std::move(token);
        }

        co_return;
    }

} // namespace ice::input
