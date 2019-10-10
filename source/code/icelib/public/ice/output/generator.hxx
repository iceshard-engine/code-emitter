#pragma once
#include <ice/input/entity.h>
#include <memory>
#include <functional>
#include <vector>

namespace ice::output
{


    //! \brief Describes a single callback.
    class CallbackRegistry
    {
    public:
        virtual ~CallbackRegistry() noexcept = default;

        //! \brief Adds a callback function for the given entity type.
        virtual void add_callback(ice::input::Entity::Type type, std::function<void(const std::shared_ptr<ice::input::Entity>&)> callback) noexcept = 0;

        //! \brief Calls all callbacks for the given entity.
        virtual void handle_entity(const std::shared_ptr<ice::input::Entity>& entity) const noexcept = 0;
    };


    //! \brief Describes a generator service which is capable of building ICE AST trees.
    class Generator
    {
    public:
        virtual ~Generator() noexcept = default;

        //! \brief Called during callback registration.
        virtual void register_callbacks(CallbackRegistry& registry) noexcept = 0;

        //! \brief Called before the parsing step.
        virtual void on_start_parsing(
            [[maybe_unused]] ice::input::Parser& parser,
            [[maybe_unused]] ice::output::Serializer& serializer
        ) noexcept { }

        //! \brief Called before the serialization step.
        virtual void on_start_serializing(
            [[maybe_unused]] ice::output::Serializer& serializer
        ) noexcept { }
    };


} // namespace ice::output
