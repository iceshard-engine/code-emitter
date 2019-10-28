#include <ice/output/elements/pragma.hxx>
#include <numeric>

namespace ice::output
{

    template<>
    auto identifier(Pragma const& data) noexcept -> std::string
    {
        return "pragma:" + data.command + std::accumulate(data.arguments.begin(), data.arguments.end(), std::string{ "(" }, [](std::string left, const auto& arg) {
            return std::move(left) + "," + arg;
        }) + ")";
    }

} // namespace ice::output
