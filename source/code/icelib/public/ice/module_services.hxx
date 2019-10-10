#pragma once
#include <ice/forwards.hxx>

namespace ice
{


    //! \brief This class is used to access module capabilities as services.
    class ModuleServices
    {
    public:
        //! \brief A Parser object producing 'Entity' objects.
        virtual auto parser_service() noexcept -> ice::input::Parser* { return nullptr; }

        //! \brief A Generator object handling 'Entity' objects and producing output 'Elements'.
        virtual auto generator_service() noexcept -> ice::output::Generator* { return nullptr; }

        //! \brief A Serializer object serializing 'Element' objects.
        virtual auto serializer_service() noexcept -> ice::output::Serializer* { return nullptr; }
    };


} // namespace ice
