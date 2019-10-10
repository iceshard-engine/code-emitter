#include <ice/output/elements/include.hxx>

namespace ice::output
{

    template<>
    auto ice::output::identifier(const Include& data) noexcept -> std::string
    {
        return { "include:" + data.path };
    }

} // namespace ice::output
