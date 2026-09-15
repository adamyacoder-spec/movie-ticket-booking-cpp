#ifndef BOOKING_CPP
#define BOOKING_CPP

#include <string>
#include <vector>
#include "Customer.cpp"
#include "Show.cpp"
#include "ShowSeat.cpp"

enum class BookingStatus {
    CONFIRMED,
    CANCELLED
};

// Represents a confirmed movie booking entity
class Booking {
private:
    static int nextBookingId; // Static Member requirement
    int bookingId;
    Customer customer;        // Aggregation
    Show show;                // Aggregation
    std::vector<ShowSeat*> bookedSeats;
    double totalAmount;
    BookingStatus status;
    std::string paymentMethod;
    std::string transactionId;

public:
    Booking() : bookingId(0), customer(), show(), totalAmount(0.0), status(BookingStatus::CANCELLED) {}

    Booking(Customer customer, Show show, std::vector<ShowSeat*> seats, double totalAmount, std::string payMethod, std::string txnId)
        : customer(customer), show(show), bookedSeats(seats), totalAmount(totalAmount), 
          status(BookingStatus::CONFIRMED), paymentMethod(payMethod), transactionId(txnId) {
        this->bookingId = ++nextBookingId;
    }

    int getBookingId() const {
        return bookingId;
    }

    const Customer& getCustomer() const {
        return customer;
    }

    const Show& getShow() const {
        return show;
    }

    const std::vector<ShowSeat*>& getBookedSeats() const {
        return bookedSeats;
    }

    double getTotalAmount() const {
        return totalAmount;
    }

    BookingStatus getStatus() const {
        return status;
    }

    std::string getStatusString() const {
        return (status == BookingStatus::CONFIRMED) ? "CONFIRMED" : "CANCELLED";
    }

    std::string getPaymentMethod() const {
        return paymentMethod;
    }

    std::string getTransactionId() const {
        return transactionId;
    }

    // Cancels booking and releases held seats (F8 / Edge Case 3)
    bool cancelBooking() {
        if (status == BookingStatus::CANCELLED) {
            return false;
        }
        status = BookingStatus::CANCELLED;
        for (auto* ss : bookedSeats) {
            if (ss != nullptr) {
                ss->release(); // Restore seat status to AVAILABLE
            }
        }
        return true;
    }
};

// Initialize static member
int Booking::nextBookingId = 1000;

#endif
