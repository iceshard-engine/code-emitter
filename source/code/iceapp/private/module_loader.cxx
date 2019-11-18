#include "module_loader.hxx"

#include <ice/module.hxx>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

namespace ice
{

    using ModuleObjectFactory = auto() -> ice::Module*;

    using ModuleObjectDestructor = void(ice::Module*);

    struct ModuleLoader::ModuleHandleImpl : ModuleLoader::ModuleHandle
    {
        HMODULE raw_handle = nullptr;

        std::unique_ptr<ice::Module, ModuleObjectDestructor*> module_object{ nullptr, nullptr };

        ~ModuleHandleImpl() noexcept final;
    };

    ModuleLoader::ModuleHandleImpl::~ModuleHandleImpl() noexcept
    {
        if (raw_handle != nullptr)
        {
            FreeLibrary(raw_handle);
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ModuleLoader::~ModuleLoader() noexcept
    {
        _modules.clear();
    }

    bool ModuleLoader::load_module(std::filesystem::path module_location) noexcept
    {
        if (std::filesystem::is_regular_file(module_location) == false)
        {
            return false;
        }

        module_location = std::filesystem::canonical(module_location);

        auto module_handle = std::make_unique<ModuleHandleImpl>();

        // Try load module.
        module_handle->raw_handle = LoadLibrary(module_location.generic_string().c_str());
        if (module_handle->raw_handle == nullptr)
        {
            return false;
        }

        // Try get public procedures.
        void* const factory_func = GetProcAddress(module_handle->raw_handle, "ice_module_factory");
        void* const destroy_func = GetProcAddress(module_handle->raw_handle, "ice_destroy_module");
        if (factory_func == nullptr || destroy_func == nullptr)
        {
            return false;
        }

        // Try create the module object
        auto* const module_object = reinterpret_cast<ModuleObjectFactory*>(factory_func)();
        if (module_object == nullptr)
        {
            return false;
        }

        module_handle->module_object = std::unique_ptr<ice::Module, ModuleObjectDestructor*>{
            module_object,
            reinterpret_cast<ModuleObjectDestructor*>(destroy_func)
        };

        std::string module_name = std::string{ module_object->name() };
        if (_modules.contains(module_name))
        {
            return false;
        }

        _modules.emplace(std::move(module_name), std::move(module_handle));
        return true;
    }

} // namespace ice