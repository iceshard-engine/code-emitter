#include <ice/logger.h>
#include <ice/debugging.hxx>

#include <fmt/printf.h>
#include <filesystem>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace ice
{

    namespace detail
    {

        static auto get_module_name() noexcept -> std::string
        {
            char buffer[255] = { 0 };
            GetModuleFileName(NULL, &buffer[0], sizeof(buffer));
            return { std::filesystem::path(buffer).filename().generic_string() };
        }

        static std::string module_name{ get_module_name() };

        static std::string_view message_format{ "{} : {} : {}\n" };

        void log_info(std::string_view message, fmt::format_args args) noexcept
        {
            auto formatted_message = fmt::vformat(message, args);
            fmt::print(stdout, detail::message_format, detail::module_name, "message", formatted_message);
        }

        void log_verbose(std::string_view message, fmt::format_args args) noexcept
        {
            auto formatted_message = fmt::vformat(message, args);
            fmt::print(stdout, detail::message_format, detail::module_name, "message", formatted_message);
        }

        void log_warning(std::string_view message, fmt::format_args args) noexcept
        {
            auto formatted_message = fmt::vformat(message, args);
            fmt::print(stderr, detail::message_format, detail::module_name, "warning", formatted_message);
        }

        void log_warning_origin(std::string_view file, int32_t file_line, std::string_view message, fmt::format_args args) noexcept
        {
            auto origin = fmt::format("{}({})", file, file_line);
            auto formatted_message = fmt::vformat(message, args);
            fmt::print(stderr, detail::message_format, origin, "warning", formatted_message);
        }

        void log_error(std::string_view message, fmt::format_args args) noexcept
        {
            auto formatted_message = fmt::vformat(message, args);
            fmt::print(stderr, detail::message_format, detail::module_name, "error", formatted_message);
        }

        void log_error_origin(std::string_view file, int32_t file_line, std::string_view message, fmt::format_args args) noexcept
        {
            auto origin = fmt::format("{}({})", file, file_line);
            auto formatted_message = fmt::vformat(message, args);
            fmt::print(stderr, detail::message_format, origin, "error", formatted_message);
        }

        void log_crash(std::string_view message, fmt::format_args args) noexcept
        {
            auto formatted_message = fmt::vformat(message, args);
            fmt::print(stderr, detail::message_format, detail::module_name, "error : crash exit ", formatted_message);
            std::exit(1);
        }

        bool log_assert(std::string_view condition, std::string_view filename, int32_t fileline, std::string_view message, fmt::format_args args) noexcept
        {
            auto origin = fmt::format("{}({})", filename, fileline);
            auto formatted_message = fmt::format("{}, {}", condition, fmt::vformat(message, args));
            fmt::print(stderr, detail::message_format, origin, " error", formatted_message);

            if (!IsDebuggerPresent())
            {
                std::exit(1);
            }
            return true;
        }

        bool log_assert(std::string_view condition, std::string_view filename, int32_t fileline, int32_t file_position, std::string_view message, fmt::format_args args) noexcept
        {
            auto origin = fmt::format("{}({},{})", filename, fileline, file_position);
            auto formatted_message = fmt::format("{}, {}", condition, fmt::vformat(message, args));
            fmt::print(stderr, detail::message_format, origin, " error", formatted_message);

            if (!IsDebuggerPresent())
            {
                std::exit(1);
            }
            return true;
        }

    } // namespace detail

} // namespace ice
