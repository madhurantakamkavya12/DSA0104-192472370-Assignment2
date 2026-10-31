#include <iostream>
#include <string>

class SavingsAccount {
private:
    static constexpr int HISTORY_LIMIT = 10;
    int accountNumber;
    long long balance;
    std::string transactions[HISTORY_LIMIT];
    int transactionCount;

    void record(const std::string& entry)
    {
        if (transactionCount < HISTORY_LIMIT) {
            transactions[transactionCount++] = entry;
        } else {
            // Shift to discard the oldest transaction: O(k), where k is the history size.
            for (int i = 1; i < HISTORY_LIMIT; ++i) transactions[i - 1] = transactions[i];
            transactions[HISTORY_LIMIT - 1] = entry;
        }
    }

public:
    SavingsAccount(int number, long long openingBalance)
        : accountNumber(number), balance(openingBalance), transactionCount(0)
    {
        record("Opening balance: " + std::to_string(openingBalance));
    }

    void deposit(long long amount); // defined outside the class
    void withdraw(long long amount); // defined outside the class
    void miniStatement() const; // defined outside the class
    long long getBalance() const { return balance; } // defined inside the class
};

void SavingsAccount::deposit(long long amount)
{
    if (amount <= 0) return;
    balance += amount;
    record("Deposit: +" + std::to_string(amount));
}

void SavingsAccount::withdraw(long long amount)
{
    if (amount <= 0 || amount > balance) return;
    balance -= amount;
    record("Withdrawal: -" + std::to_string(amount));
}

void SavingsAccount::miniStatement() const
{
    std::cout << "Account " << accountNumber << " | Balance: " << balance << '\n';
    std::cout << "Recent transactions (oldest to newest):\n";
    for (int i = 0; i < transactionCount; ++i) std::cout << "  " << transactions[i] << '\n';
}

int main()
{
    SavingsAccount account(24017, 5000);
    account.deposit(1000);
    account.withdraw(250);
    account.deposit(300);
    account.withdraw(100);
    account.deposit(50);
    account.withdraw(25);
    account.deposit(700);
    account.withdraw(200);
    account.deposit(450);
    account.withdraw(75); // 11th transaction; oldest entry is discarded
    account.miniStatement();
}
