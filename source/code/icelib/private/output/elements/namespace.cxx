#include <ice/output/elements/namespace.hxx>

namespace ice::output
{

    template<>
    auto ice::output::identifier(Namespace const& data) noexcept -> std::string
    {
        return "namespace:" + data.name;
    }

} // namespace ice::output
