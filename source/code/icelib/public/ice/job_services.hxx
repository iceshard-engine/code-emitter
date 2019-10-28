#pragma once
#include <ice/forwards.hxx>
#include <functional>

namespace ice
{

    //! \brief This interface allows the application to ask the Job for specified interfaces.
    class JobServices
    {
    public:
        //! \brief A Parser object producing 'Entity' objects.
        virtual auto parser_service() noexcept -> ice::input::Parser& = 0;

        //! \brief A registry with all registered callbacks.
        virtual auto callback_registry() const noexcept -> ice::output::CallbackRegistry const& = 0;

        //! \brief A Serializer object serializing 'Element' objects.
        virtual auto serializer_service() noexcept -> ice::output::Serializer& = 0;

        //! \brief Calls the given callback for each Generator service.
        virtual void visit_generators(std::function<void(ice::output::Generator&)> const& callback) noexcept = 0;
    };

} // namespace ice
