#pragma once
#include <ostream>
#include <string>
#include <stack>

namespace ice::output
{

    //! \brief 'EndOfLine' tag type.
    struct endl_token
    {
    };

    //! \brief 'Indent' tag type.
    struct indent_token
    {
    };

    //! \brief 'PushIndent' tag type.
    struct push_token
    {
    };

    //! \brief 'PopIndent' tag type.
    struct pop_token
    {
    };

    //! \brief Contexts used during serialization.
    enum class OutputContext
    {
        //! \brief Serialization takes place in a container, and the element should be indented on each new line.
        Container,
        //! \brief Serialization takes place inside another serialization element, and no identation should take place.
        Embedded,
    };

    //! \brief This class is used to serialize the final produced AST.
    //!
    //! \todo Change this class into an interface.
    class Writer
    {
    public:
        //! \brier Creates a writer with the given outsream and default output context.
        Writer(std::ostream& out, OutputContext default_context) noexcept;

        //! \brief Append the given string value.
        auto append(std::string value) noexcept -> Writer&;

        //! \brief Indent and append the given string value.
        auto append_indented(std::string value) noexcept -> Writer&;

        //! \brief Indent, append the given string value and emit a new-line character.
        auto writeln(std::string value) noexcept -> Writer&;

        //! \brief Indent, append the given string value, emit a new-line character and advance the indentation level.
        auto push(std::string value) noexcept -> Writer&;

        //! \brief Indent, append the given string value, emit a new-line character and lower the indentation level.
        auto pop(std::string value) noexcept -> Writer&;

        //! \brief Push the given context type onto the stack.
        auto push_context(OutputContext context) noexcept -> Writer&;

        //! \brief Pops the last context type from the stack.
        auto pop_context() noexcept -> Writer&;

        //! \brief The currnet output context type.
        auto output_context() const noexcept -> OutputContext;

    public:
        friend auto operator<<(Writer& writer, std::string str) noexcept -> Writer&;
        friend auto operator<<(Writer& writer, char character) noexcept -> Writer&;

        friend auto operator<<(Writer& writer, endl_token) noexcept -> Writer&;
        friend auto operator<<(Writer& writer, indent_token) noexcept -> Writer&;
        friend auto operator<<(Writer& writer, push_token) noexcept -> Writer&;
        friend auto operator<<(Writer& writer, pop_token) noexcept -> Writer&;

    protected:
        //! \brief The current identation string representation.
        auto indentation() const noexcept -> std::string;

    private:
        //! \brief The destination for the serialization.
        std::ostream& _stream;

        //! \brief The output context stack.
        std::stack<OutputContext> _context_stack{};

        //! \brief The indentation level.
        int32_t _level{ 0 };
    };

    auto operator<<(Writer& writer, std::string str) noexcept -> Writer&;
    auto operator<<(Writer& writer, endl_token) noexcept -> Writer&;
    auto operator<<(Writer& writer, indent_token) noexcept -> Writer&;
    auto operator<<(Writer& writer, push_token) noexcept -> Writer&;
    auto operator<<(Writer& writer, pop_token) noexcept -> Writer&;

    static endl_token endl;
    static indent_token indent;
    static push_token push;
    static pop_token pop;

} // namespace ice::output
