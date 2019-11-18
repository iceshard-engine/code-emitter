#include <ice/module.hxx>
#include <ice/version.hxx>
#include <xhash>

namespace ice
{

    auto Module::module_identifier() const noexcept -> ModuleIdentifier
    {
        return static_cast<ModuleIdentifier>(std::hash<std::string_view>{}(name()));
    }

    auto Module::module_api_version() const noexcept -> Version
    {
        return ice::api_version;
    }

} // namespace ice
