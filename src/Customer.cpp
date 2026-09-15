#ifndef CUSTOMER_CPP
#define CUSTOMER_CPP

#include <string>

// Represents a cinema customer
class Customer {
private:
    std::string name;
    std::string phone;

public:
    Customer() {
        this->name = "Guest";
        this->phone = "0000000000";
    }

    Customer(std::string name, std::string phone) {
        this->name = name;
        this->phone = phone;
    }

    std::string getName() const {
        return name;
    }

    std::string getPhone() const {
        return phone;
    }
};

#endif
