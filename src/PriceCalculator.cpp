#ifndef PRICECALCULATOR_CPP
#define PRICECALCULATOR_CPP

#include <vector>
#include "ShowSeat.cpp"

// Single Responsibility class to compute ticket pricing (SRP)
class PriceCalculator {
public:
    static constexpr double SILVER_PRICE = 150.0;
    static constexpr double GOLD_PRICE = 250.0;
    static constexpr double PLATINUM_PRICE = 400.0;

    static double getSeatPrice(SeatType seatType) {
        switch (seatType) {
            case SeatType::SILVER: return SILVER_PRICE;
            case SeatType::GOLD: return GOLD_PRICE;
            case SeatType::PLATINUM: return PLATINUM_PRICE;
            default: return 0.0;
        }
    }

    static double calculateTotal(const std::vector<ShowSeat*>& selectedSeats) {
        double total = 0.0;
        for (const auto* ss : selectedSeats) {
            if (ss != nullptr) {
                total += getSeatPrice(ss->getSeat().getSeatType());
            }
        }
        return total;
    }
};

#endif
