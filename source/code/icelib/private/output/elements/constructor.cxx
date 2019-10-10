#include <ice/output/elements/constructor.hxx>
#include <numeric>

namespace ice::output
{
    namespace detail
    {

        // Concatenates all constructor arguments into a single string usable as a identifier.
        auto constructor_identifier_arguments(const Constructor& data) noexcept -> std::string
        {
            std::string result{ };
            if (!data.arguments.empty())
            {
                result = std::accumulate(std::next(data.arguments.begin()), data.arguments.end(), data.arguments.front().type.identifier(),
                    [&](std::string left, const Constructor::Argument& argument)
                    {
                        return std::move(left) + ", " + argument.type.identifier();
                    }
                );
            }
            return result;
        }

    } // namespace detail

    template<>
    auto identifier(const Constructor & data) noexcept -> std::string
    {
        std::string result{ "constructor:" };
        result += data.is_declaration ? "declaration:" : "";
        result += data.parent_namespace + "::";
        result += data.name;
        result += "(" + detail::constructor_identifier_arguments(data) + ")";
        result += data.is_noexcept ? " noexcept" : "";
        return result;
    }

    template<>
    auto identifier(const Destructor & data) noexcept -> std::string
    {
        std::string result{ "destructor:" };
        result += data.is_declaration ? "declaration:" : "";
        result += data.parent_namespace + "::";
        result += data.name + "()";
        result += data.is_noexcept ? " noexcept" : "";
        return result;
    }

    ASTConstructor::ASTConstructor(const Constructor& data) noexcept
        : ASTContainer{ ice::output::identifier(data), true }
    { }

} // namespace ice::output
