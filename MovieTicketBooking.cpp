#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <algorithm>
#include <memory>

using namespace std;

// ============================================================
// TCS-504 ASSIGNMENT 1: MOVIE TICKET BOOKING SYSTEM
// Basic & Simple C++ Implementation (Single File)
// ============================================================

enum class SeatType { SILVER, GOLD, PLATINUM };
enum class SeatStatus { AVAILABLE, BOOKED };

// Movie Entity
class Movie {
private:
    string title;
    string language;
    int duration;

public:
    Movie(string title = "", string language = "", int duration = 0)
        : title(title), language(language), duration(duration) {}

    string getTitle() const { return title; }
    string getLanguage() const { return language; }
    int getDuration() const { return duration; }
};

// Seat Entity
class Seat {
private:
    string seatNumber;
    SeatType type;

public:
    Seat(string seatNumber = "S1", SeatType type = SeatType::SILVER)
        : seatNumber(seatNumber), type(type) {}

    string getSeatNumber() const { return seatNumber; }
    SeatType getType() const { return type; }

    double getPrice() const {
        if (type == SeatType::SILVER) return 150.0;
        if (type == SeatType::GOLD) return 250.0;
        return 400.0;
    }

    string getTypeName() const {
        if (type == SeatType::SILVER) return "SILVER";
        if (type == SeatType::GOLD) return "GOLD";
        return "PLATINUM";
    }
};

// Screen Entity (Composition: Screen owns physical seats)
class Screen {
private:
    int screenId;
    string screenName;
    vector<Seat> seats;

public:
    Screen(int screenId = 1, string screenName = "Auditorium 1")
        : screenId(screenId), screenName(screenName) {}

    void addSeat(const Seat& seat) {
        seats.push_back(seat);
    }

    int getScreenId() const { return screenId; }
    string getScreenName() const { return screenName; }
    const vector<Seat>& getSeats() const { return seats; }
};

// Cinema Entity (Composition: Cinema owns auditoriums)
class Cinema {
private:
    string name;
    string location;
    vector<Screen> screens;

public:
    Cinema(string name = "PVR Multiplex", string location = "City Center")
        : name(name), location(location) {}

    void addScreen(const Screen& screen) {
        screens.push_back(screen);
    }

    string getName() const { return name; }
    const vector<Screen>& getScreens() const { return screens; }
};

// ShowSeat Entity (Tracks AVAILABLE vs BOOKED seat status per show)
class ShowSeat {
private:
    Seat seat;
    SeatStatus status;

public:
    ShowSeat(Seat seat = Seat())
        : seat(seat), status(SeatStatus::AVAILABLE) {}

    bool isAvailable() const { return status == SeatStatus::AVAILABLE; }

    bool book() {
        if (status == SeatStatus::BOOKED) return false;
        status = SeatStatus::BOOKED;
        return true;
    }

    void release() { status = SeatStatus::AVAILABLE; }

    const Seat& getSeat() const { return seat; }
    string getStatusString() const {
        return (status == SeatStatus::AVAILABLE) ? "AVAILABLE" : "BOOKED";
    }
};

// Show Entity
class Show {
private:
    int showId;
    Movie movie;
    Screen screen;
    string startTime;
    vector<ShowSeat> showSeats;

public:
    Show(int showId = 0, Movie movie = Movie(), Screen screen = Screen(), string startTime = "12:00 PM")
        : showId(showId), movie(movie), screen(screen), startTime(startTime) {
        for (const auto& physicalSeat : screen.getSeats()) {
            showSeats.push_back(ShowSeat(physicalSeat));
        }
    }

    int getShowId() const { return showId; }
    const Movie& getMovie() const { return movie; }
    const Screen& getScreen() const { return screen; }
    string getStartTime() const { return startTime; }
    vector<ShowSeat>& getShowSeats() { return showSeats; }

    ShowSeat* findShowSeat(const string& seatNumber) {
        for (auto& ss : showSeats) {
            if (ss.getSeat().getSeatNumber() == seatNumber) return &ss;
        }
        return nullptr;
    }

    void displaySeatLayout() const {
        cout << "\n==========================================\n";
        cout << " SEAT LAYOUT FOR SHOW #" << showId << " (" << movie.getTitle() << ")\n";
        cout << " Screen: " << screen.getScreenName() << " | Time: " << startTime << "\n";
        cout << "==========================================\n";
        for (const auto& ss : showSeats) {
            cout << "Seat " << setw(3) << ss.getSeat().getSeatNumber()
                 << " [" << setw(8) << ss.getSeat().getTypeName() << "] : ["
                 << ss.getStatusString() << "]\n";
        }
        cout << "==========================================\n";
    }
};

// Customer Entity
class Customer {
private:
    string name;
    string phone;

public:
    Customer(string name = "", string phone = "") : name(name), phone(phone) {}
    string getName() const { return name; }
    string getPhone() const { return phone; }
};

enum class BookingStatus { CONFIRMED, CANCELLED };

// Booking Entity
class Booking {
private:
    static int nextBookingId;
    int bookingId;
    Customer customer;
    Show show;
    vector<ShowSeat*> bookedSeats;
    double totalAmount;
    BookingStatus status;
    string paymentMethod;
    string transactionId;

public:
    Booking(Customer customer = Customer(), Show show = Show(),
            vector<ShowSeat*> seats = {}, double amount = 0.0,
            string method = "UPI", string txnId = "TXN000")
        : customer(customer), show(show), bookedSeats(seats),
          totalAmount(amount), status(BookingStatus::CONFIRMED),
          paymentMethod(method), transactionId(txnId) {
        this->bookingId = ++nextBookingId;
    }

    int getBookingId() const { return bookingId; }
    const Customer& getCustomer() const { return customer; }
    const Show& getShow() const { return show; }
    const vector<ShowSeat*>& getBookedSeats() const { return bookedSeats; }
    double getTotalAmount() const { return totalAmount; }
    BookingStatus getStatus() const { return status; }
    string getPaymentMethod() const { return paymentMethod; }
    string getTransactionId() const { return transactionId; }

    bool cancelBooking() {
        if (status == BookingStatus::CANCELLED) return false;
        status = BookingStatus::CANCELLED;
        for (auto* ss : bookedSeats) {
            if (ss != nullptr) ss->release();
        }
        return true;
    }
};

int Booking::nextBookingId = 1000;

// Price Calculator Utility
class PriceCalculator {
public:
    static double calculateTotal(const vector<ShowSeat*>& selectedSeats) {
        double total = 0.0;
        for (const auto* ss : selectedSeats) {
            if (ss != nullptr) total += ss->getSeat().getPrice();
        }
        return total;
    }
};

// Abstract Base Class: Payment
class Payment {
protected:
    string transactionId;

public:
    virtual bool pay(double amount) = 0;
    virtual string getMethodName() const = 0;
    string getTransactionId() const { return transactionId; }
    virtual ~Payment() = default;
};

// Concrete Derived Payment Classes
class UpiPayment : public Payment {
private:
    string vpaId;
    bool simulateFailure;

public:
    UpiPayment(string vpa = "alice@okaxis", bool fail = false)
        : vpaId(vpa), simulateFailure(fail) {}

    bool pay(double amount) override {
        cout << "[UPI Payment] Processing Rs. " << amount << " via VPA: " << vpaId << "\n";
        if (simulateFailure || vpaId.find("invalid") != string::npos) {
            cout << "[UPI Payment FAILED] Invalid VPA or bank decline!\n";
            return false;
        }
        transactionId = "UPI-TXN-" + to_string(100000 + rand() % 900000);
        cout << "[UPI Payment SUCCESS] Txn ID: " << transactionId << "\n";
        return true;
    }

    string getMethodName() const override { return "UPI (" + vpaId + ")"; }
};

class CardPayment : public Payment {
private:
    string cardNumber;
    bool simulateFailure;

public:
    CardPayment(string card = "4111111111116789", bool fail = false)
        : cardNumber(card), simulateFailure(fail) {}

    bool pay(double amount) override {
        cout << "[Card Payment] Processing Card ending in "
             << (cardNumber.length() >= 4 ? cardNumber.substr(cardNumber.length() - 4) : cardNumber)
             << " for Rs. " << amount << "\n";
        if (simulateFailure) {
            cout << "[Card Payment FAILED] Transaction declined!\n";
            return false;
        }
        transactionId = "CRD-TXN-" + to_string(100000 + rand() % 900000);
        cout << "[Card Payment SUCCESS] Txn ID: " << transactionId << "\n";
        return true;
    }

    string getMethodName() const override { return "Card"; }
};

class CashPayment : public Payment {
private:
    double tenderedAmount;

public:
    CashPayment(double tendered = 500.0) : tenderedAmount(tendered) {}

    bool pay(double amount) override {
        cout << "[Cash Payment] Tendered: Rs. " << tenderedAmount << " for bill: Rs. " << amount << "\n";
        if (tenderedAmount < amount) {
            cout << "[Cash Payment FAILED] Insufficient cash!\n";
            return false;
        }
        transactionId = "CSH-TXN-" + to_string(100000 + rand() % 900000);
        cout << "[Cash Payment SUCCESS] Change: Rs. " << (tenderedAmount - amount) << "\n";
        return true;
    }

    string getMethodName() const override { return "Cash"; }
};

// Ticket Printer Utility
class TicketPrinter {
public:
    static void printTicket(const Booking& booking) {
        cout << "\n==================================================\n";
        cout << "               MOVIE TICKET PASS                  \n";
        cout << "==================================================\n";
        cout << " Booking ID  : #" << booking.getBookingId() << "\n";
        cout << " Status      : " << (booking.getStatus() == BookingStatus::CONFIRMED ? "CONFIRMED" : "CANCELLED") << "\n";
        cout << " Customer    : " << booking.getCustomer().getName() << " (" << booking.getCustomer().getPhone() << ")\n";
        cout << "--------------------------------------------------\n";
        cout << " Movie       : " << booking.getShow().getMovie().getTitle() << " (" << booking.getShow().getMovie().getLanguage() << ")\n";
        cout << " Screen      : " << booking.getShow().getScreen().getScreenName() << "\n";
        cout << " Time        : " << booking.getShow().getStartTime() << "\n";
        cout << "--------------------------------------------------\n";
        cout << " Seats       : ";
        for (size_t i = 0; i < booking.getBookedSeats().size(); ++i) {
            cout << booking.getBookedSeats()[i]->getSeat().getSeatNumber()
                 << " (" << booking.getBookedSeats()[i]->getSeat().getTypeName() << ")";
            if (i < booking.getBookedSeats().size() - 1) cout << ", ";
        }
        cout << "\n--------------------------------------------------\n";
        cout << " Payment     : " << booking.getPaymentMethod() << "\n";
        cout << " Txn ID      : " << booking.getTransactionId() << "\n";
        cout << " Total Paid  : Rs. " << fixed << setprecision(2) << booking.getTotalAmount() << "\n";
        cout << "==================================================\n\n";
    }
};

// Core Business Orchestrator Service
class BookingService {
private:
    Cinema cinema;
    vector<Movie> movies;
    vector<Show> shows;
    vector<Booking> bookings;

public:
    BookingService() {}

    void setCinema(const Cinema& c) { cinema = c; }
    void addMovie(const Movie& m) { movies.push_back(m); }
    void addShow(const Show& s) { shows.push_back(s); }

    void displayPlayingMovies() const {
        cout << "\n--- CURRENTLY PLAYING MOVIES ---\n";
        for (size_t i = 0; i < movies.size(); ++i) {
            cout << (i + 1) << ". " << movies[i].getTitle()
                 << " [" << movies[i].getLanguage() << "] ("
                 << movies[i].getDuration() << " mins)\n";
        }
    }

    vector<Show*> getShowsForMovie(const string& title) {
        vector<Show*> result;
        for (auto& show : shows) {
            if (show.getMovie().getTitle() == title) result.push_back(&show);
        }
        return result;
    }

    Show* findShowById(int id) {
        for (auto& show : shows) {
            if (show.getShowId() == id) return &show;
        }
        return nullptr;
    }

    Booking* findBookingById(int id) {
        for (auto& b : bookings) {
            if (b.getBookingId() == id) return &b;
        }
        return nullptr;
    }

    bool processBooking(Customer customer, Show* show, const vector<string>& seatNumbers, Payment* payment) {
        if (!show || !payment || seatNumbers.empty()) return false;

        vector<ShowSeat*> selectedSeats;
        for (const auto& seatNum : seatNumbers) {
            ShowSeat* ss = show->findShowSeat(seatNum);
            if (!ss) {
                cout << "[ERROR] Seat '" << seatNum << "' does not exist!\n";
                return false;
            }
            if (!ss->isAvailable()) {
                cout << "[BOOKING REJECTED] Seat '" << seatNum << "' is already BOOKED!\n";
                return false;
            }
            selectedSeats.push_back(ss);
        }

        double totalCost = PriceCalculator::calculateTotal(selectedSeats);
        cout << "[PRICE CALCULATOR] Total cost: Rs. " << totalCost << "\n";

        if (!payment->pay(totalCost)) {
            cout << "[BOOKING FAILED] Payment failed! Booking NOT confirmed.\n";
            return false;
        }

        for (auto* ss : selectedSeats) ss->book();

        Booking newBooking(customer, *show, selectedSeats, totalCost,
                           payment->getMethodName(), payment->getTransactionId());
        bookings.push_back(newBooking);

        cout << "[BOOKING SUCCESS] Booking #" << newBooking.getBookingId() << " confirmed!\n";
        TicketPrinter::printTicket(newBooking);
        return true;
    }

    bool cancelBooking(int bookingId) {
        Booking* booking = findBookingById(bookingId);
        if (!booking) {
            cout << "[ERROR] Booking ID #" << bookingId << " not found!\n";
            return false;
        }
        if (booking->cancelBooking()) {
            cout << "[SUCCESS] Booking #" << bookingId << " cancelled. Seats released.\n";
            return true;
        }
        return false;
    }
};

// Automated Edge-Case Verification Suite
void runAutomatedDemo(BookingService& service) {
    cout << "\n==================================================\n";
    cout << "   RUNNING AUTOMATED MANDATORY EDGE-CASE DEMO    \n";
    cout << "==================================================\n\n";

    Customer alice("Alice Sharma", "9876543210");
    Customer bob("Bob Verma", "9123456789");
    Show* show1 = service.findShowById(101);

    cout << "--- DEMO TEST 1: Successful Booking via UPI (F1-F7) ---\n";
    UpiPayment upiSuccess("alice@okaxis", false);
    service.processBooking(alice, show1, {"S1", "G1"}, &upiSuccess);

    cout << "\n--- DEMO TEST 2: Edge Case 1 - Booking Already Booked Seat (Rejection) ---\n";
    UpiPayment upiDup("bob@okaxis", false);
    service.processBooking(bob, show1, {"S1"}, &upiDup);

    cout << "\n--- DEMO TEST 3: Edge Case 2 - Failed Payment Handling (No Confirmation) ---\n";
    UpiPayment upiFail("bob_invalid_vpa", true);
    service.processBooking(bob, show1, {"P1"}, &upiFail);

    cout << "\n--- DEMO TEST 4: Edge Case 3 - Booking Cancellation & Seat Recovery (F8) ---\n";
    service.cancelBooking(1001);

    if (show1) show1->displaySeatLayout();

    cout << "\n--- DEMO TEST 5: Booking Seat S1 after Cancellation ---\n";
    CardPayment cardSuccess("4111111111116789", false);
    service.processBooking(bob, show1, {"S1"}, &cardSuccess);
}

// System Entry Point
int main(int argc, char* argv[]) {
    srand(static_cast<unsigned int>(time(nullptr)));

    Cinema cinema("PVR IMAX Multiplex", "Cyber City");

    Screen screen1(1, "Auditorium 1 (IMAX 3D)");
    screen1.addSeat(Seat("S1", SeatType::SILVER));
    screen1.addSeat(Seat("S2", SeatType::SILVER));
    screen1.addSeat(Seat("G1", SeatType::GOLD));
    screen1.addSeat(Seat("G2", SeatType::GOLD));
    screen1.addSeat(Seat("P1", SeatType::PLATINUM));
    screen1.addSeat(Seat("P2", SeatType::PLATINUM));

    Screen screen2(2, "Auditorium 2 (4DX)");
    screen2.addSeat(Seat("S1", SeatType::SILVER));
    screen2.addSeat(Seat("G1", SeatType::GOLD));
    screen2.addSeat(Seat("P1", SeatType::PLATINUM));

    cinema.addScreen(screen1);
    cinema.addScreen(screen2);

    Movie movie1("Inception", "English", 148);
    Movie movie2("RRR", "Telugu", 187);
    Movie movie3("Stree 2", "Hindi", 149);

    Show show1(101, movie1, screen1, "14:30 PM");
    Show show2(102, movie1, screen1, "18:00 PM");
    Show show3(103, movie2, screen2, "15:00 PM");

    BookingService service;
    service.setCinema(cinema);
    service.addMovie(movie1);
    service.addMovie(movie2);
    service.addMovie(movie3);
    service.addShow(show1);
    service.addShow(show2);
    service.addShow(show3);

    // If --demo flag passed, execute automated test suite
    if (argc > 1 && (strcmp(argv[1], "--demo") == 0 || strcmp(argv[1], "-d") == 0)) {
        runAutomatedDemo(service);
        return 0;
    }

    // Interactive CLI Menu
    int choice = -1;
    while (choice != 7) {
        cout << "\n==================================================\n";
        cout << "        PVR CINEMA MOVIE TICKET BOOKING           \n";
        cout << "==================================================\n";
        cout << " 1. Display Playing Movies (F1)\n";
        cout << " 2. Select Movie & View Shows (F2)\n";
        cout << " 3. Display Seat Layout (F3)\n";
        cout << " 4. Book Movie Tickets (F4 - F7)\n";
        cout << " 5. Cancel Booking (F8)\n";
        cout << " 6. Run Automated Verification\n";
        cout << " 7. Exit\n";
        cout << "--------------------------------------------------\n";
        cout << " Enter choice [1-7]: ";

        if (!(cin >> choice)) {
            if (cin.eof()) break;
            cout << "[ERROR] Invalid choice! Please enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1:
                service.displayPlayingMovies();
                break;
            case 2: {
                service.displayPlayingMovies();
                cout << "Enter Movie Title: ";
                string title;
                cin.ignore();
                getline(cin, title);
                vector<Show*> mShows = service.getShowsForMovie(title);
                if (mShows.empty()) {
                    cout << "No shows found for: " << title << "\n";
                } else {
                    for (const auto* s : mShows) {
                        cout << " Show ID: #" << s->getShowId()
                             << " | Screen: " << s->getScreen().getScreenName()
                             << " | Time: " << s->getStartTime() << "\n";
                    }
                }
                break;
            }
            case 3: {
                cout << "Enter Show ID: ";
                int sId;
                cin >> sId;
                Show* s = service.findShowById(sId);
                if (s) s->displaySeatLayout();
                else cout << "Show ID #" << sId << " not found!\n";
                break;
            }
            case 4: {
                cout << "Enter Customer Name: ";
                string name, phone;
                cin.ignore();
                getline(cin, name);
                cout << "Enter Phone: ";
                getline(cin, phone);
                Customer cust(name, phone);

                cout << "Enter Show ID: ";
                int sId;
                cin >> sId;
                Show* s = service.findShowById(sId);
                if (!s) {
                    cout << "Show not found!\n";
                    break;
                }
                s->displaySeatLayout();

                cout << "How many seats to book? ";
                int count;
                cin >> count;
                vector<string> seatCodes;
                for (int i = 0; i < count; ++i) {
                    cout << "Enter seat code (e.g. S1): ";
                    string code;
                    cin >> code;
                    seatCodes.push_back(code);
                }

                cout << "Payment Type (1. UPI, 2. Card, 3. Cash): ";
                int pType;
                cin >> pType;

                Payment* pay = nullptr;
                if (pType == 1) pay = new UpiPayment();
                else if (pType == 2) pay = new CardPayment();
                else pay = new CashPayment();

                service.processBooking(cust, s, seatCodes, pay);
                delete pay;
                break;
            }
            case 5: {
                cout << "Enter Booking ID to cancel: ";
                int bId;
                cin >> bId;
                service.cancelBooking(bId);
                break;
            }
            case 6:
                runAutomatedDemo(service);
                break;
            case 7:
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid menu choice.\n";
                break;
        }
    }

    return 0;
}
