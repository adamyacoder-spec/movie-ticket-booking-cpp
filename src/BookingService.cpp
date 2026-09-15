#ifndef BOOKINGSERVICE_CPP
#define BOOKINGSERVICE_CPP

#include <vector>
#include <iostream>
#include <algorithm>
#include "Cinema.cpp"
#include "Show.cpp"
#include "Booking.cpp"
#include "Payment.cpp"
#include "PriceCalculator.cpp"
#include "TicketPrinter.cpp"

// Core Business Orchestrator class managing system workflows
class BookingService {
private:
    Cinema cinema;
    std::vector<Movie> movies;
    std::vector<Show> shows;
    std::vector<Booking> bookings;

public:
    BookingService() : cinema("PVR Grand Mall", "City Center") {}

    void addMovie(const Movie& movie) {
        movies.push_back(movie);
    }

    void addShow(const Show& show) {
        shows.push_back(show);
    }

    void setCinema(const Cinema& c) {
        cinema = c;
    }

    const std::vector<Movie>& getMovies() const {
        return movies;
    }

    const std::vector<Show>& getShows() const {
        return shows;
    }

    // F1: Display all currently playing movies
    void displayPlayingMovies() const {
        std::cout << "\n==========================================" << std::endl;
        std::cout << "        CURRENTLY PLAYING MOVIES          " << std::endl;
        std::cout << "==========================================" << std::endl;
        if (movies.empty()) {
            std::cout << "No movies currently scheduled." << std::endl;
            return;
        }
        for (size_t i = 0; i < movies.size(); ++i) {
            std::cout << " " << (i + 1) << ". " << movies[i].getTitle()
                      << " [" << movies[i].getLanguage() << "] ("
                      << movies[i].getDurationMinutes() << " mins)" << std::endl;
        }
        std::cout << "==========================================\n" << std::endl;
    }

    // F2: Display shows for a selected movie
    std::vector<Show*> getShowsForMovie(const std::string& movieTitle) {
        std::vector<Show*> result;
        for (auto& show : shows) {
            if (show.getMovie().getTitle() == movieTitle) {
                result.push_back(&show);
            }
        }
        return result;
    }

    // Finds show by Show ID
    Show* findShowById(int showId) {
        for (auto& show : shows) {
            if (show.getShowId() == showId) {
                return &show;
            }
        }
        return nullptr;
    }

    // Finds active booking by Booking ID
    Booking* findBookingById(int bookingId) {
        for (auto& b : bookings) {
            if (b.getBookingId() == bookingId) {
                return &b;
            }
        }
        return nullptr;
    }

    // Orchestrates seat booking and payment processing (F4, F5, F6, F7)
    bool processBooking(Customer customer, Show* show, const std::vector<std::string>& seatNumbers, Payment* paymentMethod) {
        if (show == nullptr || paymentMethod == nullptr || seatNumbers.empty()) {
            std::cout << "\033[31m[ERROR] Invalid booking request or payment parameter.\033[0m" << std::endl;
            return false;
        }

        std::vector<ShowSeat*> selectedSeats;

        // Step 1: Validate seat availability (F4 & Edge Case 1)
        for (const auto& seatNum : seatNumbers) {
            ShowSeat* ss = show->findShowSeat(seatNum);
            if (ss == nullptr) {
                std::cout << "\033[31m[BOOKING ERROR] Seat '" << seatNum << "' does not exist!\033[0m" << std::endl;
                return false;
            }
            if (!ss->isAvailable()) {
                std::cout << "\033[31m[BOOKING REJECTED] Seat '" << seatNum 
                          << "' is already BOOKED! State remains unchanged.\033[0m" << std::endl;
                return false;
            }
            selectedSeats.push_back(ss);
        }

        // Step 2: Calculate Total Cost (F5)
        double totalCost = PriceCalculator::calculateTotal(selectedSeats);
        std::cout << "\n[PRICE CALCULATOR] Total price calculated for " 
                  << selectedSeats.size() << " seat(s): ₹" << totalCost << std::endl;

        // Step 3: Process Payment using Polymorphism (F6 & Edge Case 2)
        std::cout << "[PAYMENT SERVICE] Attempting payment processing..." << std::endl;
        bool paymentSuccess = paymentMethod->pay(totalCost);

        if (!paymentSuccess) {
            std::cout << "\033[31m[BOOKING FAILED] Payment processing failed! Booking NOT confirmed and seats remain AVAILABLE.\033[0m" << std::endl;
            return false; // Seats were not marked as booked
        }

        // Step 4: Reserve Seats upon successful payment
        for (auto* ss : selectedSeats) {
            ss->book();
        }

        // Step 5: Generate Booking record
        Booking newBooking(customer, *show, selectedSeats, totalCost, 
                           paymentMethod->getMethodName(), paymentMethod->getTransactionId());
        bookings.push_back(newBooking);

        std::cout << "\033[32m[BOOKING SUCCESS] Booking #" << newBooking.getBookingId() << " confirmed!\033[0m" << std::endl;

        // Step 6: Print Ticket Pass (F7)
        TicketPrinter::printTicket(newBooking);
        return true;
    }

    // F8 & Edge Case 3: Cancel Booking and release seats
    bool cancelBooking(int bookingId) {
        Booking* booking = findBookingById(bookingId);
        if (booking == nullptr) {
            std::cout << "\033[31m[CANCELLATION ERROR] Booking ID #" << bookingId << " not found!\033[0m" << std::endl;
            return false;
        }

        if (booking->getStatus() == BookingStatus::CANCELLED) {
            std::cout << "\033[31m[CANCELLATION ERROR] Booking ID #" << bookingId << " is already CANCELLED!\033[0m" << std::endl;
            return false;
        }

        bool cancelled = booking->cancelBooking();
        if (cancelled) {
            std::cout << "\033[32m[CANCELLATION SUCCESS] Booking #" << bookingId 
                      << " cancelled successfully. Seats are now AVAILABLE.\033[0m" << std::endl;
            return true;
        }
        return false;
    }
};

#endif
