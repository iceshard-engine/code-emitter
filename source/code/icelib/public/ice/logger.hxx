#pragma once
#include <fmt/format.h>

namespace ice
{


    namespace detail
    {

        void log_info(std::string_view message, fmt::format_args args) noexcept;

        void log_verbose(std::string_view message, fmt::format_args args) noexcept;

        void log_warning(std::string_view message, fmt::format_args args) noexcept;

        void log_warning_origin(std::string_view file, int32_t file_line, std::string_view message, fmt::format_args args) noexcept;

        void log_error(std::string_view message, fmt::format_args args) noexcept;

        void log_error_origin(std::string_view file, int32_t file_line, std::string_view message, fmt::format_args args) noexcept;

        void log_crash(std::string_view message, fmt::format_args args) noexcept;

        bool log_assert(std::string_view condition, std::string_view filename, int32_t fileline, std::string_view message, fmt::format_args args) noexcept;

        bool log_assert(std::string_view condition, std::string_view filename, int32_t fileline, int32_t file_position, std::string_view message, fmt::format_args args) noexcept;

    } // namespace detail


    template<class... Args>
    void log_info(std::string_view message, const Args&... args) noexcept
    {
        detail::log_info(std::move(message), fmt::make_format_args(args...));
    }

    template<class... Args>
    void log_verbose(std::string_view message, const Args&... args) noexcept
    {
        detail::log_verbose(std::move(message), fmt::make_format_args(args...));
    }

    template<class... Args>
    void log_warning(std::string_view message, const Args&... args) noexcept
    {
        detail::log_warning(std::move(message), fmt::make_format_args(args...));
    }

    template<class... Args>
    void log_warning_origin(std::string_view file, int32_t file_line, std::string_view message, const Args&... args) noexcept
    {
        detail::log_warning_origin(std::move(file), file_line, std::move(message), fmt::make_format_args(args...));
    }

    template<class... Args>
    void log_error(std::string_view message, const Args&... args) noexcept
    {
        detail::log_error(std::move(message), fmt::make_format_args(args...));
    }

    template<class... Args>
    void log_error_origin(std::string_view file, int32_t file_line, std::string_view message, const Args&... args) noexcept
    {
        detail::log_error_origin(std::move(file), file_line, std::move(message), fmt::make_format_args(args...));
    }

    template<class... Args>
    void log_crash(std::string_view message, const Args&... args) noexcept
    {
        detail::log_crash(std::move(message), fmt::make_format_args(args...));
    }


} // namespace ice
