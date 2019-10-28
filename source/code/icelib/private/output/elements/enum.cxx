#include <ice/output/elements/enum.hxx>

namespace ice::output
{

    template<>
    auto identifier(Enum const& data) noexcept -> std::string
    {
        std::string result{ data.is_strong ? "enum" : "enum:class" };
        result += data.is_declaration ? "" : ":declaration";
        result += data.name;
        if (!data.base_type.empty())
        {
            result += "{" + data.base_type + "}";
        }
        return result;
    }

} // namespace ice::output