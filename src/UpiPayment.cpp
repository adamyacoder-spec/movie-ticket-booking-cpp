#ifndef UPIPAYMENT_CPP
#define UPIPAYMENT_CPP

#include <string>
#include <iostream>
#include "Payment.cpp"

// Implements UPI payment method (Inheritance & Polymorphism)
class UpiPayment : public Payment {
private:
    std::string vpaId;
    bool simulateFailure;

public:
    UpiPayment(std::string vpaId, bool simulateFailure = false) 
        : vpaId(vpaId), simulateFailure(simulateFailure) {}

    bool pay(double amount) override {
        std::cout << "[UPI Payment] Initiating transaction for amount: ₹" << amount 
                  << " via VPA: " << vpaId << "..." << std::endl;
        
        if (simulateFailure || vpaId.find('@') == std::string::npos) {
            std::cout << "\033[31m[UPI Payment FAILED] Invalid VPA or transaction declined by bank.\033[0m" << std::endl;
            return false;
        }

        transactionId = "UPI-TXN-" + std::to_string(rand() % 900000 + 100000);
        std::cout << "\033[32m[UPI Payment SUCCESS] Txn ID: " << transactionId << "\033[0m" << std::endl;
        return true;
    }

    std::string getMethodName() const override {
        return "UPI (" + vpaId + ")";
    }
};

#endif
