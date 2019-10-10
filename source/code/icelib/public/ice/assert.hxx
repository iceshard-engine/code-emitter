#pragma once
#include <fmt/format.h>
#undef assert

#ifdef _DEBUG
namespace ice::build
{
    static constexpr bool is_release = false;
    static constexpr bool is_debug = true;
    static constexpr bool enable_assert = true;
}
#else
namespace ice::build
{
    static constexpr bool is_release = true;
    static constexpr bool is_debug = false;
    static constexpr bool enable_assert = true;
}
#endif

namespace ice::detail
{

    extern bool log_assert(std::string_view condition, std::string_view filename, int32_t fileline, std::string_view message, fmt::format_args args) noexcept;

    extern bool log_assert(std::string_view condition, std::string_view filename, int32_t fileline, int32_t file_position, std::string_view message, fmt::format_args args) noexcept;

} // namespace ice::detail

#undef ht_assert
#define ht_assert(cond, message, ...) \
    if constexpr(ice::build::enable_assert) { \
        if ((cond) == false) { \
            if (ice::detail::log_assert(#cond, __FILE__, __LINE__, message, fmt::make_format_args(__VA_ARGS__)) == true) { \
                __debugbreak(); \
            } \
        } \
    }

#define ht_assert_token(token, cond, message, ...) \
    if constexpr(ice::build::enable_assert) { \
        if ((cond) == false) { \
            if (ice::detail::log_assert(#cond, (token)->file(), (token)->line(), (token)->line_position(), message, fmt::make_format_args(__VA_ARGS__)) == true) { \
                __debugbreak(); \
            } \
        } \
    }

#define ht_assert_entity(entity, cond, message, ...) \
    if constexpr(ice::build::enable_assert) { \
        if ((cond) == false) { \
            const auto& location = (entity)->location(); \
            if (ice::detail::log_assert(#cond, location.file, location.line, location.line_position, message, fmt::make_format_args(__VA_ARGS__)) == true) { \
                __debugbreak(); \
            } \
        } \
    }
