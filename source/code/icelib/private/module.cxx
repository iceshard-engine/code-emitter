#include <ice/module.hxx>
#include <ice/version.hxx>
#include <xhash>

namespace ice
{

    auto Module::module_identifier() const noexcept -> uint64_t
    {
        return std::hash<std::string_view>{}(name());
    }

    auto Module::module_api_version() const noexcept -> uint32_t
    {
        return ice::api_version_effective;
    }

} // namespace ice
