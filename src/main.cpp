#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include "MainMenu.cpp"

// Initializes cinema seed data and launches system entry point
int main(int argc, char* argv[]) {
    // Seed random generator for transaction IDs
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // 1. Create Cinema & Screens (Composition)
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

    // 2. Create Movies
    Movie movie1("Inception", "English", 148);
    Movie movie2("RRR", "Telugu", 187);
    Movie movie3("Stree 2", "Hindi", 149);

    // 3. Create Shows
    Show show1(101, movie1, screen1, "14:30 PM");
    Show show2(102, movie1, screen1, "18:00 PM");
    Show show3(103, movie2, screen2, "15:00 PM");
    Show show4(104, movie3, screen1, "21:15 PM");

    // 4. Setup Booking Service
    BookingService service;
    service.setCinema(cinema);
    service.addMovie(movie1);
    service.addMovie(movie2);
    service.addMovie(movie3);

    service.addShow(show1);
    service.addShow(show2);
    service.addShow(show3);
    service.addShow(show4);

    MainMenu menu(service);

    // Check if --demo argument was passed
    if (argc > 1 && (std::strcmp(argv[1], "--demo") == 0 || std::strcmp(argv[1], "-d") == 0)) {
        menu.runAutomatedVerification();
        return 0;
    }

    // 5. Launch UI Menu
    menu.runMenu();

    return 0;
}
