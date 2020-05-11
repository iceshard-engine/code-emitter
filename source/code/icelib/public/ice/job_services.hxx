#pragma once
#include <ice/forwards.hxx>
#include <functional>

namespace ice
{

    //! \brief This interface allows the application to ask the Job for specified interfaces.
    class JobServices
    {
    public:
        virtual auto next_entity() noexcept -> std::shared_ptr<ice::input::Entity> = 0;

        //! \brief A registry with all registered callbacks.
        virtual auto callback_registry() noexcept -> ice::output::CallbackRegistry& = 0;

        //! \brief A Serializer object serializing 'Element' objects.
        virtual auto serializer_service() noexcept -> ice::output::Serializer& = 0;

        //! \brief Calls the given callback for each Generator service.
        virtual void visit_generators(std::function<void(ice::output::Generator&)> const& callback) noexcept = 0;
    };

    auto create_generic_services(
        ice::input::Parser* parser,
        ice::output::Serializer* serializer,
        std::vector<ice::output::Generator*> generators
    ) noexcept -> std::unique_ptr<JobServices>;

} // namespace ice
