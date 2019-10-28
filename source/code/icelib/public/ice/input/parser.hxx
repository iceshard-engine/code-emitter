#pragma once
#include <ice/input/entity.hxx>

#include <unordered_set>
#include <memory>

namespace ice::input
{

    //! \brief This class represents parser object returning entities.
    class Parser
    {
    public:
        virtual ~Parser() noexcept = default;

        //! \brief Checks if the parser has another entity object.
        virtual bool has_next_entity() noexcept = 0;

        //! \brief The next parsed and valid entity.
        virtual auto next_entity() noexcept -> std::shared_ptr<Entity> = 0;
    };

} // namespace ice::input
