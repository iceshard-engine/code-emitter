#include <ice/job.hxx>
#include <ice/job_services.hxx>
#include <ice/assert.hxx>
#include <ice/input/parser.hxx>
#include <ice/output/serializer.hxx>
#include <ice/output/callback_registry.hxx>

namespace ice
{

    class GenericJobServices : public ice::JobServices, public ice::output::CallbackRegistry
    {
    public:
        GenericJobServices(
            ice::input::Parser* parser,
            ice::output::Serializer* serializer,
            std::vector<ice::output::Generator*> generators
        ) noexcept
            : _parser{ parser }
            , _serializer{ serializer }
            , _generators{ std::move(generators) }
        {
        }

        auto next_entity() noexcept -> std::shared_ptr<ice::input::Entity> override
        {
            if (_parser->has_next_entity())
            {
                auto entity = _parser->next_entity();
                handle_entity(*entity);
                return entity;
            }
            return nullptr;
        }

        auto callback_registry() noexcept -> ice::output::CallbackRegistry& override
        {
            return *this;
        }

        auto serializer_service() noexcept -> ice::output::Serializer& override
        {
            return *_serializer;
        }

        void visit_generators(
            std::function<void(ice::output::Generator&)> const& callback
        ) noexcept override
        {
            for (auto* generator : _generators)
            {
                callback(*generator);
            }
        }

        //!
        //! ice::output::CallbackRegistry
        //!

        void add_callback(
            ice::input::EntityType type,
            std::function<void(ice::input::Entity const&)> callback
        ) noexcept override
        {
            _callbacks[type].push_back(std::move(callback));
        }

        void handle_entity(
            ice::input::Entity const& entity
        ) const noexcept override
        {
            if (auto it = _callbacks.find(entity.type()); it != _callbacks.end())
            {
                for (auto& callback : it->second)
                {
                    callback(entity);
                }
            }
        }

    private:
        ice::input::Parser* _parser;
        ice::output::Serializer* _serializer;
        std::vector<ice::output::Generator*> _generators;

        using CallbackType = std::function<void(ice::input::Entity const&)>;
        std::unordered_map<
            ice::input::EntityType,
            std::vector<CallbackType>
        > _callbacks;
    };

    auto create_generic_services(
        ice::input::Parser* parser,
        ice::output::Serializer* serializer,
        std::vector<ice::output::Generator*> generators
    ) noexcept -> std::unique_ptr<JobServices>
    {
        return std::make_unique<GenericJobServices>(
            parser,
            serializer,
            std::move(generators)
        );
    }

} // namespace ice
