#pragma once
#include "generic_job.hxx"
#include <ice/module.hxx>
#include <ice/module_services.hxx>
#include <ice/job_services.hxx>
#include <ice/output/generator.hxx>

namespace ice
{

    GenericJob::GenericJob(std::unique_ptr<ice::JobServices> services) noexcept
        : ice::Job{ ice::JobAction::Preprocess, std::move(services) }
    {
        initialize();
    }

    GenericJob::~GenericJob() noexcept
    {
        cleanup();
    }

    void GenericJob::execute() noexcept
    {
        parse();
        serialize();
    }

    void GenericJob::initialize() noexcept
    {
        services().visit_generators(
            [this](ice::output::Generator& generator) noexcept
            {
                generator.register_callbacks(
                    services().callback_registry()
                );
            }
        );
    }

    void GenericJob::parse() noexcept
    {
        services().visit_generators(
            [this](ice::output::Generator& generator) noexcept
            {
                generator.on_start_parsing(
                    *this
                );
            }
        );

        auto entity = services().next_entity();
        while (entity != nullptr)
        {
            entity = services().next_entity();
        }
    }

    void GenericJob::serialize() noexcept
    {
        services().visit_generators(
            [this](ice::output::Generator& generator) noexcept
            {
                generator.on_start_serializing(
                    services().serializer_service()
                );
            }
        );
    }

    void GenericJob::cleanup() noexcept
    {
        // TODO
    }

    auto create_generic_job(
        ice::ModuleLoader& modules,
        std::unordered_map<std::string, std::vector<std::string>> arguments
    ) noexcept -> std::unique_ptr<ice::Job>
    {
        ice::input::Parser* parser = nullptr;
        ice::output::Serializer* serializer = nullptr;
        std::vector<ice::output::Generator*> generators{ };

        modules.each_module(
            [&](ice::Module& mod) noexcept
            {
                mod.initialize(arguments);

                if (mod.has_capability(ice::ModuleCapabilities::Parsing))
                {
                    parser = mod.services().parser_service();
                }
                if (mod.has_capability(ice::ModuleCapabilities::Serializing))
                {
                    serializer = mod.services().serializer_service();
                }
                if (mod.has_capability(ice::ModuleCapabilities::Generating))
                {
                    generators.push_back(mod.services().generator_service());
                }
            }
        );

        return std::make_unique<ice::GenericJob>(
            ice::create_generic_services(
                parser,
                serializer,
                std::move(generators)
            )
        );
    }

} // namespace ice
