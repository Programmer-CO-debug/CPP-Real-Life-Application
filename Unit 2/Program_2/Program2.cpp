#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

class PaymentMethod {
protected:
    string transactionId;
    double amount;

public:
    PaymentMethod(string id, double amt) {
        transactionId = id;
        amount = amt;
    }

    virtual bool processPayment() const = 0;

    virtual ~PaymentMethod() {}
};


class CreditCardPayment : public PaymentMethod {
private:
    string cardNumber;

public:
    CreditCardPayment(string id, double amt, string card)
        : PaymentMethod(id, amt) {
        cardNumber = card;
    }

    bool processPayment() const {
        cout << "Credit Card Payment: "
             << transactionId
             << " | Rs. " << amount
             << " | Card: " << cardNumber
             << " | Successful" << endl;

        return true;
    }
};


class UPIPayment : public PaymentMethod {
private:
    string upiId;

public:
    UPIPayment(string id, double amt, string upi)
        : PaymentMethod(id, amt) {
        upiId = upi;
    }

    bool processPayment() const {
        cout << "UPI Payment: "
             << transactionId
             << " | Rs. " << amount
             << " | UPI: " << upiId
             << " | Successful" << endl;

        return true;
    }
};


class NetBankingPayment : public PaymentMethod {
private:
    string bankName;

public:
    NetBankingPayment(string id, double amt, string bank)
        : PaymentMethod(id, amt) {
        bankName = bank;
    }

    bool processPayment() const {
        cout << "Net Banking Payment: "
             << transactionId
             << " | Rs. " << amount
             << " | Bank: " << bankName
             << " | Successful" << endl;

        return true;
    }
};


int main() {

    vector<unique_ptr<PaymentMethod>> payments;

    payments.push_back(
        make_unique<CreditCardPayment>(
            "TXN001", 2500, "XXXX-XXXX-1234"
        )
    );

    payments.push_back(
        make_unique<UPIPayment>(
            "TXN002", 1200, "student@upi"
        )
    );

    payments.push_back(
        make_unique<NetBankingPayment>(
            "TXN003", 5000, "Example Bank"
        )
    );

    cout << "=== Payment Gateway ===" << endl;

    for (const auto& payment : payments) {
        payment->processPayment();
    }

    return 0;
}
