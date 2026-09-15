#ifndef CARDPAYMENT_CPP
#define CARDPAYMENT_CPP

#include <string>
#include <iostream>
#include "Payment.cpp"

// Implements Card payment method (Inheritance & Polymorphism)
class CardPayment : public Payment {
private:
    std::string cardNumber;
    bool simulateFailure;

public:
    CardPayment(std::string cardNumber, bool simulateFailure = false) 
        : cardNumber(cardNumber), simulateFailure(simulateFailure) {}

    bool pay(double amount) override {
        std::cout << "[Card Payment] Processing Card ending in " 
                  << (cardNumber.length() >= 4 ? cardNumber.substr(cardNumber.length() - 4) : "XXXX")
                  << " for amount: ₹" << amount << "..." << std::endl;
        
        if (simulateFailure || cardNumber.length() < 12) {
            std::cout << "\033[31m[Card Payment FAILED] Invalid card details or insufficient funds.\033[0m" << std::endl;
            return false;
        }

        transactionId = "CRD-TXN-" + std::to_string(rand() % 900000 + 100000);
        std::cout << "\033[32m[Card Payment SUCCESS] Txn ID: " << transactionId << "\033[0m" << std::endl;
        return true;
    }

    std::string getMethodName() const override {
        return "CARD (ending " + (cardNumber.length() >= 4 ? cardNumber.substr(cardNumber.length() - 4) : "XXXX") + ")";
    }
};

#endif
