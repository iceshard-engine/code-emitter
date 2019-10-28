#pragma once
#include <ice/forwards.hxx>
#include <cstdint>

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
        virtual ~Job() noexcept = default;
    };

} // namespace ice
