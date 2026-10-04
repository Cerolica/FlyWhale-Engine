#pragma once

#include "fwpch.h"

#include "FlyWhale/Core.h"

namespace FlyWhale 
{

    // Events in Hazel are currently blocking, meaning when an event occurs it
    // immediately gets dispatched and must be dealt with right then an there.
    // For the future, a better strategy might be to buffer events in an event
    // bus and process them during the "event" part of the update stage.

    enum class EventType  
    {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased, KeyTyped,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    enum EventCategory 
    {
        None = 0,
        EventCategoryApplication    = BIT(0),
        EventCategoryInput          = BIT(1),
        EventCategoryKeyboard       = BIT(2),
        EventCategoryMouse          = BIT(3),
        EventCategoryMouseButton    = BIT(4)
    };

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
                                virtual EventType GetEventType() const override { return  GetStaticType(); }\
                                virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

    class Event  
    {
        friend class EventDispatcher;
    public:
        virtual ~Event() = default;

        bool Handled = false;

        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;
        virtual std::string ToString() const { return GetName(); }

        inline bool IsInCategory(EventCategory category) const
        {
            return GetCategoryFlags() & category;
        }        
    };
    
    class EventDispatcher 
    {
        template<typename T>
        using EventFn = std::function<bool(T&)>;
    public:
        // Holds a reference to the generic event passed down from the layer
        EventDispatcher(Event& event) : m_Event(event) {}

        // Templated dispatch function
        // T = The specific event type it is listening for (e.g., KeyPressedEvent)
        // F = The function signature/lambda to execute if types match
        template<typename T> 
        bool Dispatch(EventFn<T> func) 
        {
            // Check if the generic event's runtime ID matches the target event class ID
            if (m_Event.GetEventType() == T::GetStaticType()) 
            {
                // Downcast the generic Event& reference to the specific target type T&
                // Execute the function 'func' and update the 'Handled' status
                m_Event.Handled |= func(static_cast<T&>(m_Event));
                return true;
            }
            return false;
        }

    private:
        Event& m_Event;
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e) 
    {
        return os << e.ToString();
    }

    inline std::string format_as(const Event& e) 
    {
        return e.ToString();
    }
}
