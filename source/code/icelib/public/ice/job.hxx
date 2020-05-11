#pragma once
#include <ice/forwards.hxx>
#include <memory>

namespace ice
{

    class JobServices;

    //! \brief The action the Job was created for.
    enum class JobAction : int32_t
    {
        None = 0,
        Help = 1,
        Preprocess = 2
    };

    //! \brief This class describes a single job object with it's inputs and outputs.
    class Job
    {
    public:
        Job(JobAction action, std::unique_ptr<JobServices> services) noexcept;

        virtual ~Job() noexcept = default;

        auto action() const noexcept;

        auto services() noexcept -> JobServices&;

        virtual void execute() noexcept = 0;

    private:
        JobAction const _action;
        std::unique_ptr<JobServices> _job_services;
    };

} // namespace ice
