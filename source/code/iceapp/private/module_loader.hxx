#pragma once
#include <unordered_map>
#include <filesystem>
#include <functional>
#include <string>
#include <memory>

namespace ice
{
    class Module;

    class ModuleLoader final
    {
    public:
        ModuleLoader() = default;
        ~ModuleLoader() noexcept;

        //! \brief Traverses the given location for compatible modules.
        //!     If a module is found it tries to load it.
        void load_all(std::filesystem::path location, bool recursive = false) noexcept;

        //! \brief Tries to load the module at the given location.
        bool load_module(std::filesystem::path module_location) noexcept;

        //! \brief Calls the given callback function for each loaded module.
        void each_module(std::function<void(Module&)> callback) noexcept;

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
