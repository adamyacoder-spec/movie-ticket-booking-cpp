#ifndef CINEMA_CPP
#define CINEMA_CPP

#include <string>
#include <vector>
#include "Screen.cpp"

// Represents the cinema building and owns its screens (Composition)
class Cinema {
private:
    std::string cinemaName;
    std::string location;
    std::vector<Screen> screens;

public:
    Cinema() {
        this->cinemaName = "PVR Multiplex";
        this->location = "City Mall";
    }

    Cinema(std::string cinemaName, std::string location) {
        this->cinemaName = cinemaName;
        this->location = location;
    }

    void addScreen(const Screen& screen) {
        screens.push_back(screen);
    }

    std::string getCinemaName() const {
        return cinemaName;
    }

    std::string getLocation() const {
        return location;
    }

    const std::vector<Screen>& getScreens() const {
        return screens;
    }
};

#endif
