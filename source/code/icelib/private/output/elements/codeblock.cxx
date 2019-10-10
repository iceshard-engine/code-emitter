#include <ice/output/elements/codeblock.hxx>

namespace ice::output
{

    template<>
    auto ice::output::identifier(const CodeBlock& data) noexcept -> std::string
    {
        return std::string{ "codeblock:" + data.name };
    }

} // namespace ice::output
