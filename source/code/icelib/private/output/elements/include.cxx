#include <ice/output/elements/include.hxx>

namespace ice::output
{

    template<>
    auto ice::output::identifier(Include const& data) noexcept -> std::string
    {
        return { "include:" + data.path };
    }

} // namespace ice::output
