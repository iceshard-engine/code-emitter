#include <ice/output/elements/base/line.hxx>

namespace ice::output
{

    template<>
    auto ice::output::identifier(Line const& data) noexcept -> std::string
    {
        static int lineid = 0;

        auto unique_value{ data.unique.value };
        if (unique_value.empty())
        {
            unique_value = std::to_string(lineid++) + "'" + data.value + "'";
        }

        return "line:" + unique_value;
    }

} // namespace ice::output
