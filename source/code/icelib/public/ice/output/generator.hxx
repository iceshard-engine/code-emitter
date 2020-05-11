#pragma once
#include <ice/forwards.hxx>

namespace ice::output
{

    //! \brief Describes a generator service which is capable of building ICE AST trees.
    class Generator
    {
    public:
        virtual ~Generator() noexcept = default;

        //! \brief Called during callback registration.
        virtual void register_callbacks(
            ice::output::CallbackRegistry& registry
        ) noexcept = 0;

        //! \brief Called before the parsing step.
        virtual void on_start_parsing(
            [[maybe_unused]] ice::Job& job
        ) noexcept {}

        //! \brief Called before the serialization step.
        virtual void on_start_serializing(
            [[maybe_unused]] ice::output::Serializer& serializer
        ) noexcept {}
    };

} // namespace ice::output
