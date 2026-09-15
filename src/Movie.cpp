#ifndef MOVIE_CPP
#define MOVIE_CPP

#include <string>
#include <iostream>

// Represents a movie screening in the cinema
class Movie {
private:
    std::string title;
    std::string language;
    int durationMinutes;

public:
    // Default constructor (Compile-Time Polymorphism)
    Movie() {
        this->title = "Unknown";
        this->language = "English";
        this->durationMinutes = 120;
    }

    // Parameterized constructor using 'this' keyword
    Movie(std::string title, std::string language, int durationMinutes) {
        this->title = title;
        this->language = language;
        this->durationMinutes = durationMinutes;
    }

    // Getters demonstrating Encapsulation
    std::string getTitle() const {
        return title;
    }

    std::string getLanguage() const {
        return language;
    }

    int getDurationMinutes() const {
        return durationMinutes;
    }

    void displayInfo() const {
        std::cout << "Movie: " << title << " | Language: " << language 
                  << " | Duration: " << durationMinutes << " mins" << std::endl;
    }
};

#endif
