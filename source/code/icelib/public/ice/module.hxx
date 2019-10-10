#pragma once
#include <string_view>
#include <unordered_map>
#include <ice/debugging.hxx>

namespace ice
{


    //! \brief Defines all module capabilities.
    enum class ModuleCapabilities : int32_t
    {
        None = 0x00
        , Parsing = 0x01
        , Serializing = 0x02
        , Generating = 0x04
    };


    //! \brief This interface allows the application to ask the module for specified interfaces.
    class ModuleServices;


    //! \brief This class describes a dynamic loadable module which extends the loading application.
    class Module
    {
    public:
        //! \brief Unique identifier.
        auto module_identifier() const noexcept -> uint64_t;

        //! \brief ABI version on which the module was build.
        auto module_api_version() const noexcept -> uint32_t;

        //! \brief Name of the module.
        virtual auto name() const noexcept -> std::string_view = 0;

        //! \brief Description of the module.
        virtual auto description() const noexcept -> std::string_view = 0;

        //! \brief Module capabilities.
        virtual auto capabilities() const noexcept -> ModuleCapabilities { return ModuleCapabilities::None; }

        //! \brief Called with application arguments provided in a <string, string> map.
        virtual bool initialize([[maybe_unused]] const std::unordered_map<std::string, std::vector<std::string>>& arguments) noexcept { return true; }

        //! \brief Called with debug info for initializing debugger capabilities on modules.
        virtual void initialize_debuginfo(ice::detail::DebugInfo& debug_info) noexcept
        {
            ice::debug_initialize(debug_info);
        }

        //! \brief Module service provider.
        virtual auto services() noexcept -> ModuleServices& = 0;

        //! \brief Called on shutdown to finalize any operations.
        virtual void shutdown() noexcept { }
    };


#define PUBLISH_HTMODULE(class_name) \
    extern "C" { \
        __declspec(dllexport) auto ice_module_factory() -> ice::Module* {\
            return new class_name; \
        } \
        __declspec(dllexport) void ice_destroy_module(ice::Module* mod) { \
            delete mod; \
        } \
    }


} // namespace ice
