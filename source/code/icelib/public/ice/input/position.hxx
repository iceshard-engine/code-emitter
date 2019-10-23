#pragma once
#include <cinttypes>
#include <string>

namespace ice::input
{

    //! \brief Holds position information from any input/parser object.
    struct Position final
    {
        //! \brief The input origin name.
        //!
        //! \details This value can be a file path or a specific name.
        std::string origin;

        //! \brief The input line.
        uint32_t line{ 1 };

        //! \brief The input line position.
        uint32_t line_position{ 1 };
    };

} // namespace ice::input
