#pragma once
#include <ice/input/token.hxx>

#include <experimental/coroutine>
#include <optional>
#include <memory>

namespace ice::input
{

    //! \brief A coroutine generator uset to tokenize input streams.
    class Tokenizer
    {
    public:
        //! \brief Coroutine promise type.
        class promise_type
        {
        public:
            //! \brief Returns the Tokenizer object from the coroutine frame.
            auto get_return_object() noexcept -> Tokenizer;

            //! \brief A tokenizer is suspended on creation.
            auto initial_suspend() noexcept -> std::experimental::suspend_always;

            //! \brief A tokenizer is not suspended uppon reaching the return statement.
            auto return_void() noexcept -> std::experimental::suspend_never;

            //! \brief A tokenizer is suspended on destruction.
            auto final_suspend() noexcept -> std::experimental::suspend_always;

            //! \brief A tokenizer is able to yield Token objects.
            auto yield_value(token value) noexcept -> std::experimental::suspend_always;

            //! \brief Exit with error on exeption.
            void unhandled_exception() noexcept { std::exit(-1); }

        private:
            //! \brief Holds the token value before returning. #todo is this required?
            token _value{ TokenType::Invalid };

            friend class Tokenizer;
        };

        //! \brief Coroutine handle type.
        using handle_type = std::experimental::coroutine_handle<promise_type>;

    private:
        explicit Tokenizer(handle_type handle) noexcept;

    public:
        //! \brief The default constructor disabled.
        Tokenizer() noexcept = delete;
        ~Tokenizer() noexcept;

        //! \brief A tokenizer object can be move around.
        Tokenizer(Tokenizer&& other) noexcept;

        //! \brief A tokenizer object cannot be copied.
        Tokenizer(const Tokenizer&) noexcept = delete;

        //! \brief A tokenizer object can be move around.
        auto operator=(Tokenizer&& other) noexcept -> Tokenizer&;

        //! \brief A tokenizer object cannot be copied.
        auto operator=(const Tokenizer&) noexcept -> Tokenizer& = delete;

        //! \brief Checks if another token is available.
        bool has_next_token() const noexcept;

        //! \brief Parses the next available token.
        auto next_token() noexcept -> token;

    private:
        handle_type _coroutine;
    };

} // namespace ice::input
