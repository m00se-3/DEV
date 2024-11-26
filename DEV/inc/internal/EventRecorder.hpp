#ifndef DEV_INTERNAL_EVENTRECORDER_HPP
#define DEV_INTERNAL_EVENTRECORDER_HPP

#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>

#include <deque>
#include <filesystem>

namespace dev {
    /**
     * @brief A class for recording and playing back SFML events. This is intended for internal testing.
     * 
     */
    class EventRecorder {
    public:
        using EventTypes = std::variant<std::monostate, sf::Event, sf::Time>;

        EventRecorder() = default;
        EventRecorder(const std::filesystem::path& eventFile);

        /**
         * @brief Place event at the back of the queue.
         * 
         * @param event 
         */
        constexpr void AddEvent(const EventTypes& event) { _events.emplace_back(event); }

        /**
         * @brief Return the next event from the queue. Events are returned in a first in first out order.
         * 
         * @return constexpr std::optional<EventTypes> 
         */
        [[nodiscard]] constexpr std::optional<EventTypes> GetNextEvent() {
            if(_events.empty()) { return std::nullopt; }
            return _events.front();
        }

        constexpr void PopEvent() { _events.pop_front(); }
        constexpr bool IsEmpty() { return _events.empty(); }

        void DumpToFile();

    private:
        std::deque<EventTypes> _events;        
    };
}

#endif