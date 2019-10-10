#pragma once
#include <ice/output/element.hxx>
#include <ice/output/elements/types.hxx>
#include <ice/output/elements/invoke.hxx>

namespace ice::output
{


    struct UnaryOperator
    {
        std::string identifier;

        Type result_type{ ice::output::t_void };

        bool wrap_expression{ false };

        bool postfix_operator{ false };
    };

    struct BinaryOperator
    {
        std::string identifier;

        Type result_type{ ice::output::t_void };

        bool wrap_expression{ false };
    };

    struct InvokeOperator
    {
        std::vector<std::string> arguments{ };

        std::pair<char, char> brackets{ '(', ')' };

        Type result_type{ ice::output::t_void };

        bool is_unlimited{ false };

        struct Unique
        {
            std::string value{ };
        };

        Unique unique{ "" };
    };


    template<>
    auto identifier(const UnaryOperator&) noexcept->std::string;

    template<>
    auto identifier(const BinaryOperator&) noexcept->std::string;

    template<>
    auto identifier(const InvokeOperator&) noexcept->std::string;


    class ASTUnaryOperator : public ASTElement
    {
    public:
        explicit ASTUnaryOperator(const UnaryOperator& data) noexcept;

        template<class T>
        auto set_element(const T& element_data) noexcept -> auto&;

        template<class T>
        auto chain_element(const T& element_data) noexcept -> auto&;

        template<class T>
        auto append_element(const T& element_data) noexcept -> auto&;

    protected:
        virtual auto get_element(const std::string& dataid) const noexcept -> ASTElement* = 0;
        virtual auto set_element(std::unique_ptr<ASTElement> element, bool chained) noexcept -> ASTElement* = 0;

        virtual auto get_target_element(const std::string& dataid) const noexcept -> ASTElement* = 0;
        virtual auto set_target_element(std::unique_ptr<ASTElement> element) noexcept -> ASTElement* = 0;
    };


    template<class T>
    auto ASTUnaryOperator::set_element(const T& element_data) noexcept -> auto&
    {
        using return_type_raw = decltype(factory().create(element_data));
        using return_type = typename std::decay_t<return_type_raw>::element_type;

        auto* element = static_cast<return_type*>(get_target_element(ice::output::identifier(element_data)));
        if (element == nullptr)
        {
            element = static_cast<return_type*>(set_target_element(
                factory().create(element_data)
            ));
        }
        return *element;
    }

    template<class T>
    auto ASTUnaryOperator::chain_element(const T& element_data) noexcept -> auto&
    {
        using return_type_raw = decltype(factory().create(element_data));
        using return_type = typename std::decay_t<return_type_raw>::element_type;

        auto result = get_element(ice::output::identifier(element_data));
        if (nullptr == result)
        {
            result = set_element(factory().create(element_data), true);
        }
        return *static_cast<return_type*>(result);
    }

    template<class T>
    auto ASTUnaryOperator::append_element(const T& element_data) noexcept -> auto&
    {
        using return_type_raw = decltype(factory().create(element_data));
        using return_type = typename std::decay_t<return_type_raw>::element_type;

        auto result = get_element(ice::output::identifier(element_data));
        if (nullptr == result)
        {
            result = set_element(factory().create(element_data), false);
        }
        return *static_cast<return_type*>(result);
    }


    class ASTBinaryOperator : public ASTElement
    {
    public:
        explicit ASTBinaryOperator(const BinaryOperator& data) noexcept;

        template<class T>
        auto set_left_element(const T& element_data) noexcept -> auto&;

        template<class T>
        auto set_right_element(const T& element_data) noexcept -> auto&;

        template<class T>
        auto chain_element(const T& element_data) noexcept -> auto&;

        template<class T>
        auto append_element(const T& element_data) noexcept -> auto&;

    protected:
        virtual auto get_element(const std::string& dataid) const noexcept -> ASTElement* = 0;
        virtual auto set_element(std::unique_ptr<ASTElement> element, bool chained) noexcept -> ASTElement* = 0;

        virtual auto get_target_element(const std::string& dataid, bool right_element) const noexcept -> ASTElement* = 0;
        virtual auto set_target_element(std::unique_ptr<ASTElement> element, bool right_element) noexcept -> ASTElement* = 0;
    };

    template<class T>
    auto ASTBinaryOperator::set_left_element(const T& element_data) noexcept -> auto&
    {
        using return_type_raw = decltype(factory().create(element_data));
        using return_type = typename std::decay_t<return_type_raw>::element_type;

        auto* element = static_cast<return_type*>(get_target_element(ice::output::identifier(element_data), false));
        if (element == nullptr)
        {
            element = static_cast<return_type*>(set_target_element(
                factory().create(element_data)
                , false
            ));
        }
        return *element;
    }

    template<class T>
    auto ASTBinaryOperator::set_right_element(const T& element_data) noexcept -> auto&
    {
        using return_type_raw = decltype(factory().create(element_data));
        using return_type = typename std::decay_t<return_type_raw>::element_type;

        auto* element = static_cast<return_type*>(get_target_element(ice::output::identifier(element_data), true));
        if (element == nullptr)
        {
            element = static_cast<return_type*>(set_target_element(
                factory().create(element_data)
                , true
            ));
        }
        return *element;
    }

    template<class T>
    auto ASTBinaryOperator::chain_element(const T& element_data) noexcept -> auto&
    {
        using return_type_raw = decltype(factory().create(element_data));
        using return_type = typename std::decay_t<return_type_raw>::element_type;

        auto result = get_element(ice::output::identifier(element_data));
        if (nullptr == result)
        {
            result = set_element(factory().create(element_data), true);
        }
        return *static_cast<return_type*>(result);
    }

    template<class T>
    auto ASTBinaryOperator::append_element(const T& element_data) noexcept -> auto&
    {
        using return_type_raw = decltype(factory().create(element_data));
        using return_type = typename std::decay_t<return_type_raw>::element_type;

        auto result = get_element(ice::output::identifier(element_data));
        if (nullptr == result)
        {
            result = set_element(factory().create(element_data), false);
        }
        return *static_cast<return_type*>(result);
    }


    class ASTInvokeOperator: public ASTElement
    {
    public:
        explicit ASTInvokeOperator(const InvokeOperator& data) noexcept;

        template<class T>
        auto set_argument(std::string name, const T& element_data, bool new_line = false) noexcept -> auto&;

        template<class T>
        auto chain_element(const T& invoke_data) noexcept -> auto&;

        template<class T>
        auto append_element(const T& invoke_data) noexcept -> auto&;

    private:
        virtual auto get_element(
            const std::string& dataid
        ) const noexcept -> ASTElement* = 0;

        virtual auto set_element(
            std::unique_ptr<ASTElement> element
            , bool chained
        ) noexcept -> ASTElement* = 0;

        virtual auto get_argument_value(
            std::string argname
            , std::string argid
        ) const noexcept -> ASTElement* = 0;

        virtual auto set_argument_value(
            std::string argname
            , std::unique_ptr<ASTElement> element
            , bool newline
        ) noexcept -> ASTElement* = 0;
    };

    template<class T>
    auto ASTInvokeOperator::set_argument(std::string name, const T& element_data, bool new_line /*= false*/) noexcept -> auto&
    {
        using return_type_raw = decltype(factory().create(element_data));
        using return_type = typename std::decay_t<return_type_raw>::element_type;

        auto* element = static_cast<return_type*>(get_argument_value(name, ice::output::identifier(element_data)));
        if (element == nullptr)
        {
            element = static_cast<return_type*>(set_argument_value(
                std::move(name),
                factory().create(element_data),
                new_line
            ));
        }
        return *element;
    }

    template<class T>
    auto ASTInvokeOperator::chain_element(const T& element_data) noexcept -> auto&
    {
        using return_type_raw = decltype(factory().create(element_data));
        using return_type = typename std::decay_t<return_type_raw>::element_type;

        auto result = get_element(ice::output::identifier(element_data));
        if (nullptr == result)
        {
            result = set_element(factory().create(element_data), false);
        }
        return *static_cast<return_type*>(result);
    }

    template<class T>
    auto ASTInvokeOperator::append_element(const T& element_data) noexcept -> auto&
    {
        using return_type_raw = decltype(factory().create(element_data));
        using return_type = typename std::decay_t<return_type_raw>::element_type;

        auto result = get_element(ice::output::identifier(element_data));
        if (nullptr == result)
        {
            result = set_element(factory().create(element_data), false);
        }
        return *static_cast<return_type*>(result);
    }


} // namespace ice::output
