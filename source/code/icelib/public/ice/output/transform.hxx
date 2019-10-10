#pragma once
#include <algorithm>

namespace ice::output::data
{


    template<class C, class T>
    struct DataTransform
    {
        constexpr DataTransform(T(C::*member_pointer)) noexcept;

        constexpr DataTransform(T(C::*member_pointer), T requested_value) noexcept;

        [[nodiscard]]
        constexpr auto operator()(T value) const noexcept->DataTransform;

        template<class C, class T>
        friend auto operator|(C data, const DataTransform<C, T>& transform) noexcept->C;

    private:
        T(C::*field);

        T value;
    };

    template<class C, class T>
    DataTransform(T(C::*), T)->DataTransform<C, T>;

    template<class C, class T>
    DataTransform(T(C::*))->DataTransform<C, T>;


    template<class C, class T>
    [[nodiscard]]
    auto operator|(C data, const DataTransform<C, T>& transform) noexcept -> C
    {
        (data.*transform.field) = transform.value;
        return std::move(data);
    }


    template<class C, class T>
    constexpr DataTransform<C, T>::DataTransform(T(C::*member_pointer)) noexcept
        : field{ member_pointer }
        , value{ }
    { }

    template<class C, class T>
    constexpr DataTransform<C, T>::DataTransform(T(C::*member_pointer), T requested_value) noexcept
        : field{ member_pointer }
        , value{ std::move(requested_value) }
    { }

    template<class C, class T>
    constexpr auto ice::output::data::DataTransform<C, T>::operator()(T new_value) const noexcept -> DataTransform
    {
        return DataTransform<C, T>{ field, std::move(new_value) };
    }


} // namespace ice::output::data
