#include <ice/output/elements/alias.hxx>

namespace ice::output
{

    template<>
    auto identifier(Alias const& data) noexcept -> std::string
    {
        return { "alias:" + data.name + "{" + data.type + "}" };
    }

} // namespace ice::output
