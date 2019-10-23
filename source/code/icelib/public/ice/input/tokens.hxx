#pragma once
#include <ice/input/tokenizer.hxx>
#include <string>

namespace ice::input
{

    //! \todo describe this method.
    auto parse_symbol_token(std::istream& stream, Position& position, int& character) noexcept -> token;

    //! \todo describe this method.
    auto parse_number_token(std::istream& stream, Position& position, int& character) noexcept -> token;

    //! \todo describe this method.
    auto parse_literal_token(std::istream& stream, Position& position, int& character) noexcept -> token;

    //! \todo describe this method.
    auto parse_const_literal_token(std::istream& stream, Position& position, int& character) noexcept -> token;

    //! \todo describe this method.
    auto parse_punctuation_token(std::istream& stream, Position& position, int& character) noexcept -> token;

    //! \todo describe this method.
    auto parse_whitespace_token(std::istream& stream, Position& position, int& character) noexcept -> token;

    //! \todo describe this method.
    auto parse_end_of_line_token(std::istream& stream, Position& position, int& character) noexcept -> token;

    //! \todo describe this method.
    auto parse_invalid_token(std::istream& stream, Position& position, int& character) noexcept -> token;

} // namespace ice::input
