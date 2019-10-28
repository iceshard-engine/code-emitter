#include <ice/input/entity.hxx>

namespace ice::input
{

    Entity::Entity(EntityType type) noexcept
        : _type{ type }
    {
    }

} // namespace ice::input
