#ifndef SEAT_CPP
#define SEAT_CPP

#include <string>

// Enum representing physical seat tiers
enum class SeatType {
    SILVER,
    GOLD,
    PLATINUM
};

// Represents one physical seat in an auditorium
class Seat {
private:
    std::string seatNumber;
    SeatType seatType;

public:
    Seat() {
        this->seatNumber = "A1";
        this->seatType = SeatType::SILVER;
    }

    Seat(std::string seatNumber, SeatType seatType) {
        this->seatNumber = seatNumber;
        this->seatType = seatType;
    }

    std::string getSeatNumber() const {
        return seatNumber;
    }

    SeatType getSeatType() const {
        return seatType;
    }

    std::string getSeatTypeString() const {
        switch (seatType) {
            case SeatType::SILVER: return "SILVER";
            case SeatType::GOLD: return "GOLD";
            case SeatType::PLATINUM: return "PLATINUM";
            default: return "UNKNOWN";
        }
    }
};

#endif
