#include <ice/output/elements/function.hxx>
#include <numeric>

namespace ice::output
{
    namespace detail
    {

        // Concatenates all function arguments into a single string usable as a identifier.
        auto function_identifier_arguments(Function const& data) noexcept -> std::string
        {
            std::string result{};
            if (!data.arguments.empty())
            {
                result = std::accumulate(std::next(data.arguments.begin()), data.arguments.end(), data.arguments.front().type.identifier(),
                    [&](std::string left, Function::Argument const& argument) {
                        return std::move(left) + ", " + argument.type.identifier();
                    });
            }
            return result;
        }

    } // namespace detail

    template<>
    auto ice::output::identifier(Function const& data) noexcept -> std::string
    {
        std::string result{ "function:" };
        result += data.is_declaration ? "declaration:" : "";
        result += data.return_type.identifier() + " ";
        result += data.parent_namespace + "::";
        result += data.name;
        result += detail::function_identifier_arguments(data);
        result += data.is_const ? " const" : "";
        result += data.is_noexcept ? " noexcept" : "";
        return result;
    }

} // namespace ice::output
