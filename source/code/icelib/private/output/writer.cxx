#include <ice/output/writer.hxx>

namespace ice::output
{

    Writer::Writer(std::ostream& out, OutputContext default_context) noexcept
        : _stream{ out }
    {
        push_context(default_context);
    }

    auto Writer::append(std::string value) noexcept -> Writer&
    {
        _stream << value;
        return *this;
    }

    auto Writer::append_indented(std::string value) noexcept -> Writer&
    {
        if (_context_stack.top() != OutputContext::Embedded)
        {
            _stream << indentation();
        }
        _stream << value;
        return *this;
    }

    auto Writer::writeln(std::string value) noexcept -> Writer&
    {
        _stream << indentation() << value << "\n";
        return *this;
    }

    auto Writer::push(std::string value) noexcept -> Writer&
    {
        if (!value.empty())
            writeln(value);
        _level += 1;
        return *this;
    }

    auto Writer::pop(std::string value) noexcept -> Writer&
    {
        _level -= 1;
        if (!value.empty())
            writeln(value);
        return *this;
    }

    auto Writer::indentation() const noexcept -> std::string
    {
        return std::string(size_t{ 4 } * _level, ' ');
    }

    auto Writer::push_context(OutputContext context) noexcept -> Writer&
    {
        _context_stack.push(context);
        return *this;
    }

    auto Writer::pop_context() noexcept -> Writer&
    {
        _context_stack.pop();
        return *this;
    }

    auto Writer::output_context() const noexcept -> OutputContext
    {
        return _context_stack.top();
    }

    auto operator<<(Writer& writer, std::string str) noexcept -> Writer&
    {
        return writer.append(str);
    }

    auto operator<<(Writer& writer, char character) noexcept -> Writer&
    {
        writer._stream << character;
        return writer;
    }

    auto operator<<(Writer& writer, endl_token) noexcept -> Writer&
    {
        writer._stream << "\n";
        return writer;
    }

    auto operator<<(Writer& writer, indent_token) noexcept -> Writer&
    {
        return writer.append_indented("");
    }

    auto operator<<(Writer& writer, push_token) noexcept -> Writer&
    {
        writer._level += 1;
        return writer;
    }

    auto operator<<(Writer& writer, pop_token) noexcept -> Writer&
    {
        writer._level -= 1;
        return writer;
    }

} // namespace ice::output
