#ifndef SHOWSEAT_CPP
#define SHOWSEAT_CPP

#include <string>
#include "Seat.cpp"

enum class SeatStatus {
    AVAILABLE,
    BOOKED
};

// Represents the booking status of a seat for a specific show
class ShowSeat {
private:
    Seat seat;
    SeatStatus status;

public:
    ShowSeat() : seat(), status(SeatStatus::AVAILABLE) {}

    ShowSeat(Seat seat) : seat(seat), status(SeatStatus::AVAILABLE) {}

    bool isAvailable() const {
        return status == SeatStatus::AVAILABLE;
    }

    // Mark seat as booked (returns false if already booked - Edge Case F4)
    bool book() {
        if (status == SeatStatus::BOOKED) {
            return false;
        }
        status = SeatStatus::BOOKED;
        return true;
    }

    // Release seat back to AVAILABLE status (Edge Case F8)
    void release() {
        status = SeatStatus::AVAILABLE;
    }

    const Seat& getSeat() const {
        return seat;
    }

    SeatStatus getStatus() const {
        return status;
    }

    std::string getStatusString() const {
        return (status == SeatStatus::AVAILABLE) ? "AVAILABLE" : "BOOKED";
    }
};

#endif
