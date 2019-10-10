#pragma once
#include <ice/output/elements/base/container.hxx>

namespace ice::output
{


    class ASTRoot : public ice::output::ASTContainer
    {
    public:
        ASTRoot() noexcept;

        //! \copydoc ASTContainer::serialize
        void serialize(Writer& writer) const noexcept override;

        //! \brief Checks if the given Root element is enabled from serialization.
        virtual bool enabled() const noexcept = 0;

        //! \brief Sets the serialization flag of this Root element.
        virtual void set_enabled(bool value) noexcept = 0;

        //! \brief The Root element location.
        //! \note Can be anything, from a path to a URL.
        virtual auto location() const noexcept -> std::string = 0;

        //! \brief Serializes the whole Root element and all its children to the final representation.
        virtual void serialize() const noexcept = 0;
    };


} // namespace ice::output
