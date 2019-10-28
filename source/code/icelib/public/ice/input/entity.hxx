#pragma once
#include <ice/input/position.hxx>
#include <ice/input/attributes.hxx>
#include <ice/input/entity_type.hxx>

#include <memory>

namespace ice::input
{

    //! \brief This class represents a single parsed entity.
    class Entity
    {
    public:
        virtual ~Entity() noexcept = default;

        //! \brief Creating an entity requires its type to be known.
        explicit Entity(EntityType type) noexcept;

        //! \brief Type of the entity.
        auto type() const noexcept -> EntityType { return _type; }

        //! \brief Name of the entity.
        virtual auto name() const noexcept -> std::string = 0;

        //! \brief Canonical name of the entity.
        virtual auto canonical_name() const noexcept -> std::string { return name(); }

        //! \brief List of attributes this entity is associated with.
        virtual auto attribute_list() const noexcept -> AttributeList const& = 0;

        //! \brief Parent contaning entity.
        virtual auto parent_entity() const noexcept -> std::shared_ptr<Entity> const& = 0;

        //! \brief This entity may contain other entities and introduces a new scope.
        virtual bool introduces_scope() const noexcept { return false; }

        //! \brief Location of this entity in the input data.
        virtual auto location() const noexcept -> Position const& = 0;

    protected:
        const EntityType _type;
    };

} // namespace ice::input
