#pragma once
#include <ice/forwards.hxx>
#include <ice/input/entity_type.hxx>

#include <functional>
#include <memory>

namespace ice::output
{

    //! \brief Describes a single callback.
    class CallbackRegistry
    {
    public:
        virtual ~CallbackRegistry() noexcept = default;

        //! \brief Adds a callback function for the given entity type.
        virtual void add_callback(ice::input::EntityType type, std::function<void(ice::input::Entity const&)> callback) noexcept = 0;

        //! \brief Calls all callbacks for the given entity.
        virtual void handle_entity(ice::input::Entity const& entity) const noexcept = 0;
    };

} // namespace ice::output
