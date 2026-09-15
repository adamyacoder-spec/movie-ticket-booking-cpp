#ifndef SCREEN_CPP
#define SCREEN_CPP

#include <string>
#include <vector>
#include "Seat.cpp"

// Represents one auditorium and owns its physical seats (Composition)
class Screen {
private:
    int screenId;
    std::string screenName;
    std::vector<Seat> seats;

public:
    Screen() {
        this->screenId = 1;
        this->screenName = "Screen 1";
    }

    Screen(int screenId, std::string screenName) {
        this->screenId = screenId;
        this->screenName = screenName;
    }

    // Adds physical seat to screen (Composition ownership)
    void addSeat(const Seat& seat) {
        seats.push_back(seat);
    }

    int getScreenId() const {
        return screenId;
    }

    std::string getScreenName() const {
        return screenName;
    }

    const std::vector<Seat>& getSeats() const {
        return seats;
    }
};

#endif
