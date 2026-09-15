# Movie Ticket Booking System 🎬🎟️
**Course**: B.Tech. CSE (Semester V) | **Subject**: System Design (TCS-504)  
**Language**: C++17 | **Architecture**: Object-Oriented Design & Clean Code (Zero Header Files)

---

## 📌 Project Overview

A robust, menu-driven **C++ Console Movie Ticket Booking System** for a single cinema multiplex (e.g., PVR/INOX). Built to satisfy the academic requirements of **TCS-504 System Design**, this project models real-world movie ticket booking workflows including date/show selection, tier pricing, live seat status matrix management, multi-channel payment integration, itemized ticket generation, and booking cancellation.

---

## ✨ Key Features (F1 – F8)

- **F1: Movie Listing**: Display all currently playing movies with title, language, and duration.
- **F2: Showtimes per Movie**: View shows for a selected movie with auditorium screen name and start time.
- **F3: Live Seat Layout Grid**: Display seat status (`AVAILABLE` vs `BOOKED`) with tier badges (Silver, Gold, Platinum).
- **F4: Multi-Seat Booking Validation**: Select one or more seats; automatically rejects already-booked seats without mutating state.
- **F5: Tiered Pricing Engine**:
  - 🥈 **SILVER**: ₹150
  - 🥇 **GOLD**: ₹250
  - 💎 **PLATINUM**: ₹400
- **F6: Multi-Channel Payment Hierarchy**: Supports **UPI**, **Credit/Debit Card**, and **Cash**. Failed payments release held seats immediately.
- **F7: Itemized Pass/Ticket Printer**: Prints formatted pass with Booking ID, Customer details, Movie, Screen, Time, Seats, Txn ID, and Total Paid.
- **F8: Cancellation & Seat Recovery**: Cancel confirmed bookings using Booking ID, returning seats to `AVAILABLE` status.

---

## 🏗️ Architecture & Design Highlights

### 1. Object-Oriented Principles (OOP)
- **Encapsulation**: Private state attributes accessed exclusively via getters/setters.
- **Abstraction**: Base class `Payment` with pure virtual method `virtual bool pay(double amount) = 0`.
- **Inheritance**: `UpiPayment`, `CardPayment`, and `CashPayment` inherit from `Payment`.
- **Runtime Polymorphism**: `Payment*` dynamic method dispatch during transaction processing.
- **Compile-Time Polymorphism**: Constructor overloading across domain entities.
- **Static Members**: Global auto-incrementing ID generator (`nextBookingId`).
- **`this` Keyword**: Explicit disambiguation in constructor initializations.
- **Composition**: `Cinema ➔ Screen`, `Screen ➔ Seat`, `Show ➔ ShowSeat`.
- **Aggregation**: `Show ➔ Movie`, `Booking ➔ Customer`.
- **Association**: `BookingService ➔ Payment`, `BookingService ➔ TicketPrinter`.

### 2. SOLID Design Principles
- **SRP (Single Responsibility)**: `PriceCalculator` prices seats, `TicketPrinter` formats passes, `BookingService` orchestrates workflows.
- **OCP (Open-Closed)**: Adding new payment methods (e.g., `NetBankingPayment`) requires zero edits to existing service code.
- **LSP (Liskov Substitution)**: Any derived payment class works seamlessly via `Payment*`.
- **ISP (Interface Segregation)**: Minimal payment interface contract avoiding bloated methods like forced refunds.
- **DIP (Dependency Inversion)**: `BookingService` depends on high-level `Payment` abstraction rather than concrete implementations.

---

## 📂 File Structure

```text
movie_ticket_booking/
├── MovieTicketBooking.cpp              # Single-file complete C++ implementation
├── README.md                           # GitHub README documentation
├── TCS504_Assignment1_MovieTicketBooking.md # Full Academic Report (UML, Tables, SOLID)
├── src/                                # Modular single-class C++ files (No headers)
│   ├── Movie.cpp
│   ├── Seat.cpp
│   ├── Screen.cpp
│   ├── Cinema.cpp
│   ├── ShowSeat.cpp
│   ├── Show.cpp
│   ├── Customer.cpp
│   ├── Booking.cpp
│   ├── Payment.cpp
│   ├── UpiPayment.cpp
│   ├── CardPayment.cpp
│   ├── CashPayment.cpp
│   ├── PriceCalculator.cpp
│   ├── TicketPrinter.cpp
│   ├── BookingService.cpp
│   ├── MainMenu.cpp
│   └── main.cpp
└── .gitignore
```

---

## 🛠️ Build & Execution Instructions

### Prerequisites
- GCC / MinGW-w64 with C++17 support installed.

### Compilation
```bash
# Option 1: Compile single-file executable
g++ -std=c++17 -O2 -static MovieTicketBooking.cpp -o main.exe

# Option 2: Compile modular C++ codebase (No header files)
g++ -std=c++17 -O2 -static -I. src/main.cpp -o main.exe
```

### Execution
```bash
# Run interactive console menu
./main.exe

# Run automated edge-case verification test suite
./main.exe --demo
```

---

## 📜 Academic Documentation

For complete UML Class Diagrams, UML Sequence Diagrams, Class Responsibility Analysis (*Knows / Does / Must NOT Do*), Noun-Verb Analysis, and Relationship Lifetime Test justifications, refer to [TCS504_Assignment1_MovieTicketBooking.md](./TCS504_Assignment1_MovieTicketBooking.md).

---

## 👤 Author
Developed as part of **TCS-504 System Design (B.Tech. CSE Semester V)**.
