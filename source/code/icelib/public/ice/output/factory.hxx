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


    class ASTLine;
    class ASTElement;
    class ASTContainer;

    class ASTAlias;
    class ASTEnum;
    class ASTNamespace;
    class ASTAccessSpecifier;
    class ASTUserType;
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

        virtual auto create(const Line& line_data) noexcept -> std::unique_ptr<ASTLine> = 0;
        virtual auto create(const Value& value_data) noexcept -> std::unique_ptr<ASTElement> = 0;
        virtual auto create(const Container& container_data) noexcept -> std::unique_ptr<ASTContainer> = 0;

        virtual auto create(const Pragma& pragma_data) noexcept -> std::unique_ptr<ASTElement> = 0;
        virtual auto create(const Include& include_data) noexcept -> std::unique_ptr<ASTElement> = 0;

        virtual auto create(const Alias& alias_data) noexcept -> std::unique_ptr<ASTAlias> = 0;
        virtual auto create(const Enum& enum_data) noexcept -> std::unique_ptr<ASTEnum> = 0;
        virtual auto create(const CodeBlock& codeblock_data) noexcept->std::unique_ptr<ASTContainer> = 0;
        virtual auto create(const Namespace& namespace_data) noexcept -> std::unique_ptr<ASTNamespace> = 0;
        virtual auto create(const UserType& usertype_data) noexcept -> std::unique_ptr<ASTUserType> = 0;
        virtual auto create(const AccessSpecifier& usertype_data) noexcept -> std::unique_ptr<ASTAccessSpecifier> = 0;
        virtual auto create(const Variable& variable_data) noexcept -> std::unique_ptr<ASTVariable> = 0;
        virtual auto create(const Function& function_data) noexcept -> std::unique_ptr<ASTContainer> = 0;
        virtual auto create(const Constructor& constructor_data) noexcept -> std::unique_ptr<ASTConstructor> = 0;
        virtual auto create(const Destructor& destructor_data) noexcept -> std::unique_ptr<ASTContainer> = 0;

        virtual auto create(const Invoke& invoke_data) noexcept -> std::unique_ptr<ASTInvokeable> = 0;
        virtual auto create(const Initializer& initializer_data) noexcept -> std::unique_ptr<ASTInvokeable> = 0;
        virtual auto create(const UnaryOperator& operator_data) noexcept -> std::unique_ptr<ASTUnaryOperator> = 0;
        virtual auto create(const BinaryOperator& operator_data) noexcept -> std::unique_ptr<ASTBinaryOperator> = 0;
        virtual auto create(const InvokeOperator& operator_data) noexcept -> std::unique_ptr<ASTInvokeOperator> = 0;
        virtual auto create(const Assignment& assignment_data) noexcept -> std::unique_ptr<ASTAssignment> = 0;
    };


} // namespace ice::output
