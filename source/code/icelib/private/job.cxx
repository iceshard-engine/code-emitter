#include <ice/job.hxx>
#include <ice/job_services.hxx>
#include <ice/assert.hxx>

namespace ice
{

    Job::Job(JobAction action, std::unique_ptr<JobServices> services) noexcept
        : _action{ action }
        , _job_services{ std::move(services) }
    {
        ht_assert(_job_services != nullptr, "Job creation: Services object cannot be 'null'!");
    }

    inline auto Job::action() const noexcept
    {
        return _action;
    }

    auto Job::services() noexcept -> JobServices&
    {
        return *_job_services;
    }

} // namespace ice
