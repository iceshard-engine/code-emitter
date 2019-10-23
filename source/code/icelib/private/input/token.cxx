#include <ice/input/token.hxx>
#include <ice/assert.hxx>
#include <fmt/format.h>

namespace ice::input
{

    auto debug_string(const token& token) noexcept -> std::string
    {
        return fmt::format("{}:({},{}) <{}:{}>",
            token.position.origin,
            token.position.line,
            token.position.line_position,
            token.type,
            token.value
        );
    }

} // namespace ice::input
