#pragma once
#include <cstdint>

namespace ice
{

    //! \brief Major versions may change APIs and ABIs.
    static constexpr const uint16_t api_version_major = 1;

    //! \brief Minor versions may change ABIs and deprecate APIs.
    static constexpr const uint16_t api_version_minor = 0;

    //! \brief Patch versions may change implementations and introduce new APIs.
    static constexpr const uint32_t api_version_patch = 0;

    //! \brief API version type.
    enum struct Version : uint32_t;

    //! \brief Current API version value.
    static constexpr const Version api_version = Version{ (uint32_t{ api_version_major } << 16) | uint32_t{ api_version_minor } };

} // namespace ice
