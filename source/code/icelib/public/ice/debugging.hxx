#pragma once

namespace ice
{
    namespace detail
    {

        using debug_wait_signature = void(void*);
        using debug_break_signature = void(void*);
        using debug_break_attrib_signature = void(void*);

        struct DebugInfo
        {
            void* userdata{ nullptr };

            debug_wait_signature* debug_wait_handler{ nullptr };

            debug_wait_signature* debug_break_handler{ nullptr };

            debug_wait_signature* debug_break_attrib_handler{ nullptr };
        };

    } // namespace detail

    void debug_initialize(detail::DebugInfo debug_info) noexcept;

    void debug_wait() noexcept;

    void debug_break() noexcept;

    void debug_break_attrib() noexcept;

} // namespace ice
