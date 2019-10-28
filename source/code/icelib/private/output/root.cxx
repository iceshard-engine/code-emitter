#include <ice/output/root.hxx>
#include <algorithm>
#include <sstream>

namespace ice::output
{

    ASTRoot::ASTRoot() noexcept
        : ASTContainer{ Container{ "" } }
    {
    }

    void ASTRoot::serialize(Writer& writer) const noexcept
    {
        ASTContainer::serialize(writer);
    }

} // namespace ice::output
