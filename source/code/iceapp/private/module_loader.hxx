#pragma once

#include <unordered_map>
#include <filesystem>
#include <string>
#include <memory>

namespace ice
{
    class ModuleLoader final
    {
    public:
        ModuleLoader() = default;
        ~ModuleLoader() noexcept;

        //! \brief Tries to load the module at the given location.
        bool load_module(std::filesystem::path module_location) noexcept;

    private:
        struct ModuleHandleImpl;

        struct ModuleHandle
        {
            virtual ~ModuleHandle() noexcept = default;

            friend struct ModuleHandleImpl;
        };

        // List of all loaded modules.
        std::unordered_map<std::string, std::unique_ptr<ModuleHandle>> _modules{};
    };

} // namespace ice
