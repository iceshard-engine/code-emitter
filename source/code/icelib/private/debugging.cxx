#include <ice/debugging.hxx>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace ice
{
    namespace detail
    {

        // Holds the last set debug info structure
        static DebugInfo current_debug_info{ nullptr, nullptr, nullptr, nullptr };

        // Internal debug_wait call
        void debug_wait() noexcept
        {
            if (nullptr != current_debug_info.debug_wait_handler)
            {
                current_debug_info.debug_wait_handler(current_debug_info.userdata);
            }
        }

        void debug_break() noexcept
        {
            if (nullptr != current_debug_info.debug_break_handler)
            {
                current_debug_info.debug_break_handler(current_debug_info.userdata);
            }
        }

        void debug_break_attrib() noexcept
        {
            if (nullptr != current_debug_info.debug_break_attrib_handler)
            {
                current_debug_info.debug_break_attrib_handler(current_debug_info.userdata);
            }
        }

    } // namespace detail

    void debug_initialize(detail::DebugInfo debug_info) noexcept
    {
        detail::current_debug_info = debug_info;
    }

    void debug_wait() noexcept
    {
        detail::debug_wait();
    }

    void debug_break() noexcept
    {
        detail::debug_break();
    }

    void debug_break_attrib() noexcept
    {
        detail::debug_break_attrib();
    }

} // namespace ice
