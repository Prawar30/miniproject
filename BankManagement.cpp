#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <ctime>

using namespace std;

// Function to generate a random account number
int generateAccountNumber() {
    return rand() % 9000 + 1000;
}

// Class to show a bank account
class BankAccount {
private:
    string accountHolder;
    double balance;
    int accountNumber;

public:
    // Constructor to create a bank account
    BankAccount(const string& holder, double initialBalance)
        : accountHolder(holder), balance(initialBalance) {
        accountNumber = generateAccountNumber();
    }

    
    void displayAccount() const {
        cout << "\nAccount Details\n";       
        cout << "Account Holder: " << accountHolder << "\n";
        cout << "Balance: " << fixed << setprecision(2) << balance << "\n";
    }

    int getAccountNumber() const {
        return accountNumber;
    }
};


void addAccount() {
    string name;
    double initialBalance;

    cout << "Enter account holder's name: ";

    while (true) {
        getline(cin, name);

        if (!name.empty() && name.find_first_of("1234567890") == string::npos) {
            break; 
        } else {
            cout << "Invalid input. Please try again:";
        }
    }

    cout << "Enter initial balance: ";
    cin >> initialBalance;

    cin.ignore();

    BankAccount newAccount(name, initialBalance);

    ofstream outFile("account_details.txt", ios::app);

    if (outFile.is_open()) {
        outFile << newAccount.getAccountNumber() << " " << name << " " << initialBalance << "\n";
        outFile.close();
        cout << "Account added successfully!\n";
        cout << "Account Number: " << newAccount.getAccountNumber() << "\n";
    } else {
        cout << "Error opening file for writing.\n";
    }
}

void displayAccountDetails() {
    int accountNumber;
    cout << "Enter account number to display details: ";
    cin >> accountNumber;

    ifstream inFile("account_details.txt");

    if (inFile.is_open()) {
        int fileAccountNumber;
        string name;
        double balance;

        bool found = false;

        while (inFile >> fileAccountNumber >> name >> balance) {
            if (fileAccountNumber == accountNumber) {
                found = true;

                BankAccount account(name, balance);
                account.displayAccount();
                break;
            }
        }

        if (!found) {
            cout << "Account not found!\n";
        }

        inFile.close();
    } else {
        cout << "Error opening file for reading.\n";
    }
}

void deleteAccount() {
    int accountNumber;
    cout << "Enter account number to delete: ";
    cin >> accountNumber;

    ifstream inFile("account_details.txt");
    ofstream outFile("temp.txt");

    if (inFile.is_open() && outFile.is_open()) {
        int fileAccountNumber;
        string name;
        double balance;

        bool found = false;


        while (inFile >> fileAccountNumber >> name >> balance) {
            if (fileAccountNumber != accountNumber) {
                outFile << fileAccountNumber << " " << name << " " << balance << "\n";
            } else {
                found = true;
            }
        }

        inFile.close();
        outFile.close();

        
        remove("account_details.txt");
        rename("temp.txt", "account_details.txt");

        if (found) {
            cout << "Account deleted successfully!\n";
        } else {
            cout << "Account not found!\n";
        }
    } else {
        cout << "Error opening files for reading or writing.\n";
    }
}

int main() {
    srand(time(0));

    int choice;

    do {
        cout << "\nBank Management System\n";
        cout << "1. Add Account\n";
        cout << "2. Display Account\n";
        cout << "3. Delete Account\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                addAccount();
                break;
            case 2:
                displayAccountDetails();
                break;
            case 3:
                deleteAccount();
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
        }

    } while (choice != 4);

    return 0;
}

