#include <ice/input/tokenizer.hxx>

namespace ice::input
{

    auto Tokenizer::promise_type::get_return_object() noexcept -> Tokenizer
    {
        return Tokenizer{ handle_type::from_promise(*this) };
    }

    auto Tokenizer::promise_type::initial_suspend() noexcept -> std::experimental::suspend_always
    {
        return {};
    }

    auto Tokenizer::promise_type::return_void() noexcept -> std::experimental::suspend_never
    {
        return {};
    }

    auto Tokenizer::promise_type::final_suspend() noexcept -> std::experimental::suspend_always
    {
        return {};
    }

    auto Tokenizer::promise_type::yield_value(token token) noexcept -> std::experimental::suspend_always
    {
        _value = std::move(token);
        return {};
    }

    Tokenizer::~Tokenizer() noexcept
    {
        if (_coroutine)
        {
            _coroutine.destroy();
        }
    }

    Tokenizer::Tokenizer(handle_type handle) noexcept
        : _coroutine{ std::move(handle) }
    {
    }

    Tokenizer::Tokenizer(Tokenizer&& other) noexcept
        : _coroutine{ std::move(other._coroutine) }
    {
        other._coroutine = nullptr;
    }

    auto Tokenizer::operator=(Tokenizer&& other) noexcept -> Tokenizer&
    {
        if (this == &other)
        {
            return *this;
        }

        if (_coroutine)
        {
            _coroutine.destroy();
        }

        _coroutine = other._coroutine;
        other._coroutine = nullptr;
        return *this;
    }

    bool Tokenizer::has_next_token() const noexcept
    {
        return !_coroutine.done();
    }

    auto Tokenizer::next_token() noexcept -> token
    {
        if (_coroutine.done())
        {
            return { TokenType::EndOfFile };
        }
        else
        {
            _coroutine.resume();
            return std::move(_coroutine.promise()._value);
        }
    }

} // namespace ice::input
