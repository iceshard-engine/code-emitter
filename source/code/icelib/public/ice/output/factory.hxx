#pragma once
#include <memory>

namespace ice::output
{

    struct Line;
    struct Value;
    struct Container;

    struct Pragma;
    struct Include;

    struct Alias;
    struct Enum;
    struct CodeBlock;
    struct Namespace;
    struct AccessSpecifier;
    struct UserType;
    struct Variable;
    struct Function;
    struct Constructor;
    struct Destructor;

    struct Invoke;
    struct Initializer;
    struct UnaryOperator;
    struct BinaryOperator;
    struct InvokeOperator;
    struct Assignment;

    class ASTElement;
    class ASTContainer;

    class ASTVariable;
    class ASTConstructor;

    class ASTInvokeable;
    class ASTUnaryOperator;
    class ASTBinaryOperator;
    class ASTInvokeOperator;
    class ASTAssignment;

    //! \brief Describes a class which is able to create elements from given types.
    class Factory
    {
    public:
        virtual ~Factory() noexcept = default;

        // Heavy WIP
        virtual auto create_element(
            uint64_t type_hash,
            void const* data,
            size_t size
        ) noexcept -> std::unique_ptr<ASTElement> = 0;

        // Heavy WIP
        template<typename T>
        auto create(T const& data) noexcept -> std::unique_ptr<ASTElement>
        {
            return create_element(typeid(T).hash_code(), &data, sizeof(T));
        }
    };

    using ASTFactory = Factory;

} // namespace ice::output
