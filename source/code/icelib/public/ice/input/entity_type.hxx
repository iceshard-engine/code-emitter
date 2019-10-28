#pragma once
#include <cinttypes>

namespace ice::input
{

    //! \brief Defines all known entity types.
    enum class EntityType : uint32_t
    {
        Invalid = 0x0000'0000,

        // Common entities
        Alias = 0x0000'0001,
        Enumeration = 0x0000'0002,
        Member = 0x0000'0004,
        Namespace = 0x0000'0010,
        Usertype = 0x0000'0020,

        // Additional C++ entities
        Preprocessor = 0x0000'10000,

        // Special entities
        ScopeEnd = 0x0001'0000,
        FileBegin = 0x0002'0000,
        FileEnd = 0x0004'0000,
        Token = 0x0008'0000,

        Unknown = 0x000f'ffff,

        // Custom
        Custom = 0x0010'0000
    };

} // namespace ice::input
