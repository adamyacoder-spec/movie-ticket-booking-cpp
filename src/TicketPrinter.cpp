#ifndef TICKETPRINTER_CPP
#define TICKETPRINTER_CPP

#include <iostream>
#include <iomanip>
#include "Booking.cpp"

// Single Responsibility Class for formatting and printing tickets (F7 & SRP)
class TicketPrinter {
public:
    static void printTicket(const Booking& booking) {
        std::cout << "\n==================================================" << std::endl;
        std::cout << "               MOVIE TICKET PASS                  " << std::endl;
        std::cout << "==================================================" << std::endl;
        std::cout << " Booking ID  : #" << booking.getBookingId() << std::endl;
        std::cout << " Status      : " << booking.getStatusString() << std::endl;
        std::cout << " Customer    : " << booking.getCustomer().getName() 
                  << " (" << booking.getCustomer().getPhone() << ")" << std::endl;
        std::cout << "--------------------------------------------------" << std::endl;
        std::cout << " Movie       : " << booking.getShow().getMovie().getTitle() 
                  << " (" << booking.getShow().getMovie().getLanguage() << ")" << std::endl;
        std::cout << " Screen      : " << booking.getShow().getScreen().getScreenName() << std::endl;
        std::cout << " Time        : " << booking.getShow().getStartTime() << std::endl;
        std::cout << "--------------------------------------------------" << std::endl;
        std::cout << " Seats       : ";
        for (size_t i = 0; i < booking.getBookedSeats().size(); ++i) {
            std::cout << booking.getBookedSeats()[i]->getSeat().getSeatNumber()
                      << " (" << booking.getBookedSeats()[i]->getSeat().getSeatTypeString() << ")";
            if (i < booking.getBookedSeats().size() - 1) std::cout << ", ";
        }
        std::cout << std::endl;
        std::cout << "--------------------------------------------------" << std::endl;
        std::cout << " Payment     : " << booking.getPaymentMethod() << std::endl;
        std::cout << " Txn ID      : " << booking.getTransactionId() << std::endl;
        std::cout << " Total Paid  : ₹" << std::fixed << std::setprecision(2) << booking.getTotalAmount() << std::endl;
        std::cout << "==================================================" << std::endl;
        std::cout << "   Thank you! Enjoy your movie at PVR Multiplex!  " << std::endl;
        std::cout << "==================================================\n" << std::endl;
    }
};

#endif
