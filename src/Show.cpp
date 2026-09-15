#ifndef SHOW_CPP
#define SHOW_CPP

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include "Movie.cpp"
#include "Screen.cpp"
#include "ShowSeat.cpp"

// Represents a movie screening on a particular screen at a specific time
class Show {
private:
    int showId;
    Movie movie;             // Aggregation (Movie exists independently)
    Screen screen;           // Aggregation (Screen exists independently)
    std::string startTime;
    std::vector<ShowSeat> showSeats; // Composition (ShowSeats exist for this show)

public:
    Show() : showId(0), movie(), screen(), startTime("00:00") {}

    Show(int showId, Movie movie, Screen screen, std::string startTime)
        : showId(showId), movie(movie), screen(screen), startTime(startTime) {
        // Initialize show seats from physical screen seats
        for (const auto& physicalSeat : screen.getSeats()) {
            showSeats.push_back(ShowSeat(physicalSeat));
        }
    }

    int getShowId() const {
        return showId;
    }

    const Movie& getMovie() const {
        return movie;
    }

    const Screen& getScreen() const {
        return screen;
    }

    std::string getStartTime() const {
        return startTime;
    }

    std::vector<ShowSeat>& getShowSeats() {
        return showSeats;
    }

    // Finds pointer to ShowSeat by seat number
    ShowSeat* findShowSeat(const std::string& seatNumber) {
        for (auto& ss : showSeats) {
            if (ss.getSeat().getSeatNumber() == seatNumber) {
                return &ss;
            }
        }
        return nullptr;
    }

    // Displays grid of seat layout showing tier, seat number, and status (F3)
    void displaySeatLayout() const {
        std::cout << "\n==========================================" << std::endl;
        std::cout << " SEAT LAYOUT FOR SHOW #" << showId << " (" << movie.getTitle() << ")" << std::endl;
        std::cout << " Screen: " << screen.getScreenName() << " | Time: " << startTime << std::endl;
        std::cout << "==========================================" << std::endl;
        std::cout << " [SCREEN THIS WAY]" << std::endl;
        std::cout << "------------------------------------------" << std::endl;

        for (const auto& ss : showSeats) {
            std::cout << "Seat " << std::setw(3) << ss.getSeat().getSeatNumber()
                      << " [" << std::setw(8) << ss.getSeat().getSeatTypeString() << "] : "
                      << (ss.isAvailable() ? "\033[32m[AVAILABLE]\033[0m" : "\033[31m[ BOOKED  ]\033[0m")
                      << std::endl;
        }
        std::cout << "==========================================\n" << std::endl;
    }
};

#endif
