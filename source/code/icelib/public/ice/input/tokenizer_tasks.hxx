#pragma once
#include <ice/input/tokenizer.hxx>

namespace ice::input
{

    //! \brief Tokenizes the given input stream.
    //!
    //! \param [in] name Name of the stream object.
    auto tokenize_stream(std::istream& stream, std::optional<std::string> name = {}) noexcept -> Tokenizer;

    //! \brief Tokenizes the given string value.
    //!
    //! \param [in] name Name of the given content value.
    auto tokenize_string(std::string contents, std::optional<std::string> name = {}) noexcept -> Tokenizer;

} // namespace ice::input
