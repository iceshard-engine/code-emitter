#include <ice/output/elements/base/value.hxx>

namespace ice::output
{

    template<>
    auto identifier(const Value& data) noexcept -> std::string
    {
        static int lineid = 0;

        std::string unique_id{ data.unique.value };
        if (unique_id.empty())
        {
            unique_id = std::to_string(lineid++);
        }

        return "value:" + std::move(unique_id) + "'" + data.value + "'";
    }

} // namespace ice::output
