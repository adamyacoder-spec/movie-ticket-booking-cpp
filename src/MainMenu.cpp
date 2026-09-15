#ifndef MAINMENU_CPP
#define MAINMENU_CPP

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "BookingService.cpp"
#include "UpiPayment.cpp"
#include "CardPayment.cpp"
#include "CashPayment.cpp"

// User Interface controller for console interaction
class MainMenu {
private:
    BookingService service;

public:
    MainMenu(const BookingService& bookingService) : service(bookingService) {}

    void displayHeader() const {
        std::cout << "\n==================================================" << std::endl;
        std::cout << "        PVR CINEMA MOVIE TICKET BOOKING           " << std::endl;
        std::cout << "==================================================" << std::endl;
    }

    void runMenu() {
        int choice = -1;
        while (choice != 7) {
            displayHeader();
            std::cout << " 1. Display Playing Movies (F1)" << std::endl;
            std::cout << " 2. Select Movie & View Shows (F2)" << std::endl;
            std::cout << " 3. Display Seat Layout (F3)" << std::endl;
            std::cout << " 4. Book Movie Tickets (F4 - F7)" << std::endl;
            std::cout << " 5. Cancel Booking (F8)" << std::endl;
            std::cout << " 6. Run Automated Requirement & Edge-Case Verification" << std::endl;
            std::cout << " 7. Exit" << std::endl;
            std::cout << "--------------------------------------------------" << std::endl;
            std::cout << " Enter choice [1-7]: ";

            if (std::cin.eof()) {
                break;
            }
            if (!(std::cin >> choice)) {
                if (std::cin.eof()) break;
                std::cout << "\033[31m[ERROR] Invalid menu choice! Please enter a number.\033[0m" << std::endl;
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                continue;
            }

            switch (choice) {
                case 1:
                    service.displayPlayingMovies();
                    break;
                case 2:
                    handleViewShows();
                    break;
                case 3:
                    handleViewSeatLayout();
                    break;
                case 4:
                    handleBookTickets();
                    break;
                case 5:
                    handleCancelBooking();
                    break;
                case 6:
                    runAutomatedVerification();
                    break;
                case 7:
                    std::cout << "\nThank you for using Movie Ticket Booking System! Goodbye.\n" << std::endl;
                    break;
                default:
                    std::cout << "\033[31m[ERROR] Choice out of range [1-7]. Try again.\033[0m" << std::endl;
                    break;
            }
        }
    }

private:
    void handleViewShows() {
        service.displayPlayingMovies();
        std::cout << "Enter Movie Title exactly as listed: ";
        std::string title;
        std::cin.ignore();
        std::getline(std::cin, title);

        std::vector<Show*> movieShows = service.getShowsForMovie(title);
        if (movieShows.empty()) {
            std::cout << "\033[31mNo shows found for movie: " << title << "\033[0m" << std::endl;
            return;
        }

        std::cout << "\n--- AVAILABLE SHOWS FOR '" << title << "' ---" << std::endl;
        for (const auto* s : movieShows) {
            std::cout << " Show ID: #" << s->getShowId() 
                      << " | Screen: " << s->getScreen().getScreenName()
                      << " | Start Time: " << s->getStartTime() << std::endl;
        }
    }

    void handleViewSeatLayout() {
        std::cout << "Enter Show ID: ";
        int showId;
        if (!(std::cin >> showId)) {
            std::cout << "\033[31m[ERROR] Invalid Show ID input!\033[0m" << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            return;
        }

        Show* show = service.findShowById(showId);
        if (show == nullptr) {
            std::cout << "\033[31m[ERROR] Show ID #" << showId << " not found!\033[0m" << std::endl;
            return;
        }

        show->displaySeatLayout();
    }

    void handleBookTickets() {
        std::cout << "Enter Customer Name: ";
        std::string name;
        std::cin.ignore();
        std::getline(std::cin, name);

        std::cout << "Enter Customer Phone: ";
        std::string phone;
        std::getline(std::cin, phone);

        Customer customer(name, phone);

        std::cout << "Enter Show ID: ";
        int showId;
        if (!(std::cin >> showId)) {
            std::cout << "\033[31m[ERROR] Invalid Show ID!\033[0m" << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            return;
        }

        Show* show = service.findShowById(showId);
        if (show == nullptr) {
            std::cout << "\033[31m[ERROR] Show ID #" << showId << " not found!\033[0m" << std::endl;
            return;
        }

        show->displaySeatLayout();

        std::cout << "Enter number of seats to book: ";
        int numSeats;
        if (!(std::cin >> numSeats) || numSeats <= 0) {
            std::cout << "\033[31m[ERROR] Invalid seat quantity!\033[0m" << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            return;
        }

        std::vector<std::string> seatNumbers;
        for (int i = 0; i < numSeats; ++i) {
            std::cout << "Enter seat number " << (i + 1) << " (e.g., S1, G1, P1): ";
            std::string seatNum;
            std::cin >> seatNum;
            seatNumbers.push_back(seatNum);
        }

        std::cout << "\nSelect Payment Method:\n 1. UPI\n 2. Card\n 3. Cash\nChoice [1-3]: ";
        int payChoice;
        std::cin >> payChoice;

        Payment* payment = nullptr;
        if (payChoice == 1) {
            std::cout << "Enter UPI ID (e.g. user@upi): ";
            std::string vpa;
            std::cin >> vpa;
            payment = new UpiPayment(vpa);
        } else if (payChoice == 2) {
            std::cout << "Enter 16-digit Card Number: ";
            std::string card;
            std::cin >> card;
            payment = new CardPayment(card);
        } else if (payChoice == 3) {
            std::cout << "Enter Cash Amount Tendered: ₹";
            double cash;
            std::cin >> cash;
            payment = new CashPayment(cash);
        } else {
            std::cout << "\033[31m[ERROR] Invalid payment method selected!\033[0m" << std::endl;
            return;
        }

        service.processBooking(customer, show, seatNumbers, payment);
        delete payment;
    }

    void handleCancelBooking() {
        std::cout << "Enter Booking ID to cancel: ";
        int bId;
        if (!(std::cin >> bId)) {
            std::cout << "\033[31m[ERROR] Invalid Booking ID!\033[0m" << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            return;
        }

        service.cancelBooking(bId);
    }

public:
    void runAutomatedVerification() {
        std::cout << "\n==================================================" << std::endl;
        std::cout << "   RUNNING AUTOMATED MANDATORY EDGE-CASE DEMO    " << std::endl;
        std::cout << "==================================================\n" << std::endl;

        Show* show = service.findShowById(101);
        if (!show) return;

        Customer alice("Alice Sharma", "9876543210");
        Customer bob("Bob Verma", "9123456789");

        std::cout << "\n--- DEMO TEST 1: Successful Booking via UPI (F1-F7) ---" << std::endl;
        UpiPayment validUpi("alice@okaxis");
        service.processBooking(alice, show, {"S1", "G1"}, &validUpi);

        std::cout << "\n--- DEMO TEST 2: Edge Case 1 - Booking Already Booked Seat (Rejection) ---" << std::endl;
        CardPayment bobCard("4532890123456789");
        service.processBooking(bob, show, {"S1"}, &bobCard); // S1 is already booked by Alice!

        std::cout << "\n--- DEMO TEST 3: Edge Case 2 - Failed Payment Handling (No Confirmation) ---" << std::endl;
        UpiPayment failedUpi("bob_invalid_vpa", true); // simulate failure
        service.processBooking(bob, show, {"P1"}, &failedUpi); // P1 will NOT be booked

        std::cout << "\n--- DEMO TEST 4: Edge Case 3 - Booking Cancellation & Seat Recovery (F8) ---" << std::endl;
        service.cancelBooking(1001); // Cancel Alice's booking
        show->displaySeatLayout(); // Verify S1 and G1 are back to AVAILABLE!

        std::cout << "\n--- DEMO TEST 5: Booking Seat S1 after Cancellation ---" << std::endl;
        service.processBooking(bob, show, {"S1"}, &bobCard); // Should succeed now!
    }
};

#endif
