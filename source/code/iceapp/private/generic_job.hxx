#pragma once
#include <ice/job.hxx>
#include "module_loader.hxx"

namespace ice
{

    //! \brief Defines a generic job for a single Parser, Serializer and any number of Generators.
    class GenericJob : public ice::Job
    {
    public:
        GenericJob(std::unique_ptr<ice::JobServices> services) noexcept;
        ~GenericJob() noexcept;

        void execute() noexcept override;

    protected:
        void initialize() noexcept;
        void parse() noexcept;
        void serialize() noexcept;
        void cleanup() noexcept;
    };

    auto create_generic_job(
        ice::ModuleLoader& modules,
        std::unordered_map<std::string, std::vector<std::string>> arguments
    ) noexcept -> std::unique_ptr<ice::Job>;

}
