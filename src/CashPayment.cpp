#ifndef CASHPAYMENT_CPP
#define CASHPAYMENT_CPP

#include <string>
#include <iostream>
#include "Payment.cpp"

// Implements Cash payment method (Inheritance & Polymorphism)
class CashPayment : public Payment {
private:
    double tenderedAmount;

public:
    CashPayment(double tenderedAmount) : tenderedAmount(tenderedAmount) {}

    bool pay(double amount) override {
        std::cout << "[Cash Payment] Cash tendered: ₹" << tenderedAmount 
                  << " for total amount: ₹" << amount << "..." << std::endl;
        
        if (tenderedAmount < amount) {
            std::cout << "\033[31m[Cash Payment FAILED] Insufficient cash tendered. Short by ₹" 
                      << (amount - tenderedAmount) << "\033[0m" << std::endl;
            return false;
        }

        double change = tenderedAmount - amount;
        transactionId = "CSH-TXN-" + std::to_string(rand() % 900000 + 100000);
        std::cout << "\033[32m[Cash Payment SUCCESS] Change returned: ₹" << change 
                  << " | Txn ID: " << transactionId << "\033[0m" << std::endl;
        return true;
    }

    std::string getMethodName() const override {
        return "CASH";
    }
};

#endif
