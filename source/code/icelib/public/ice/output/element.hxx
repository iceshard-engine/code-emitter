#pragma once
#include <ice/forwards.hxx>
#include <ice/output/factory.hxx>
#include <type_traits>
#include <memory>
#include <string>


namespace ice::output
{


    class Factory;


    template<typename T>
    auto identifier(const T&) noexcept -> std::string;


    template<typename Container, typename T>
    auto transform(T&& object) noexcept -> T&&
    {
        return std::move(object);
    }


    //! \brief Describes a single AST element.
    class ASTElement
    {
    public:
        ASTElement(std::string element_uuid) noexcept;
        virtual ~ASTElement() noexcept = default;

        //! \brief Element unique identifier.
        auto identifier() const noexcept -> std::string_view;

        //! \brief The Factory used to create this element.
        virtual auto factory() noexcept -> Factory& = 0;

        //! \brief Called to serialize the element.
        virtual void serialize(ice::output::Writer& strm) const noexcept = 0;

    protected:
        const std::string _identifier;
    };


    //! \brief Describes a AST element capable of holding child elements.
    class ASTContainerElement : public ASTElement
    {
    public:
        ASTContainerElement(std::string element_uuid) noexcept;
        virtual ~ASTContainerElement() noexcept override = default;

        template<typename T>
        bool contains(const T& element_data) const noexcept;

        template<typename T, typename... Args>
        auto add(const T& data, Args&&... args) noexcept -> auto&;

    protected:
        virtual auto get(const std::string& id) const noexcept -> ASTElement* = 0;
        virtual auto set(std::unique_ptr<ASTElement> element) noexcept -> ASTElement* = 0;
    };


    template<typename T>
    bool ASTContainerElement::contains(const T& element_data) const noexcept
    {
        return get(ice::output::identifier(element_data)) != nullptr;
    }

    template<typename T, typename... Args>
    auto ASTContainerElement::add(const T& element_data, Args&&... args) noexcept -> auto&
    {
        using return_type_raw = decltype(factory().create(element_data));
        using return_type = typename std::decay_t<return_type_raw>::element_type;

        auto* element = get(ice::output::identifier(element_data));
        if (element == nullptr)
        {
            element = set(factory().create(element_data));
        }
        return *static_cast<return_type*>(element);
    }


} // namespace ice::output
