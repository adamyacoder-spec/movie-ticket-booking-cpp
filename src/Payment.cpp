#ifndef PAYMENT_CPP
#define PAYMENT_CPP

#include <string>
#include <iostream>

// Abstract Base Class defining payment contract (Abstraction & Interface Segregation)
class Payment {
protected:
    std::string transactionId;

public:
    Payment() : transactionId("TXN-000") {}

    virtual ~Payment() {}

    // Pure virtual method for Runtime Polymorphism
    virtual bool pay(double amount) = 0;

    virtual std::string getMethodName() const = 0;

    std::string getTransactionId() const {
        return transactionId;
    }
};

#endif
