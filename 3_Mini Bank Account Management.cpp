#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

class BankAccount
{
public:
    string name;
    int accountNumber;
    float balance;

    BankAccount(string name, int accountNumber, float balance)
    {
        this->name = name;
        this->accountNumber = accountNumber;
        this->balance = balance;
    }

    void display() const
    {
        cout << "------------------------------\n";
        cout << "Name           : " << name << "\n";
        cout << "Account Number : " << accountNumber << "\n";
        cout << "Balance        : Rs. " << balance << "\n";
        cout << "------------------------------\n";
    }

    string toFileString() const
    {
        return name + "," + to_string(accountNumber) + "," + to_string(balance);
    }
};

class BankSystem
{
private:
    vector<BankAccount> accounts;
    string filename = "accounts.txt";

public:
    BankSystem()
    {
        loadAccountsFromFile();
    }

    void createAccount(string name, int accountNumber, float balance)
    {
        BankAccount acc(name, accountNumber, balance);
        accounts.push_back(acc);
        saveAccountToFile(acc);
        cout << "\n[+] Account created successfully!\n";
    }

    void viewAllAccounts() const
    {
        if (accounts.empty())
        {
            cout << "\n[!] No accounts found.\n";
            return;
        }

        cout << "\n========= All Bank Accounts =========\n";
        for (const auto& acc : accounts)
        {
            acc.display();
        }
        cout << "Total accounts: " << accounts.size() << "\n";
    }

    void searchAccount(int number) const
    {
        bool found = false;
        for (const auto& acc : accounts)
        {
            if (acc.accountNumber == number)
            {
                cout << "\n[✓] Account Found:\n";
                acc.display();
                found = true;
                break;
            }
        }
        if (!found)
        {
            cout << "\n[!] Account not found.\n";
        }
    }

private:
    void saveAccountToFile(const BankAccount& acc) const
    {
        ofstream outFile(filename, ios::app);
        if (outFile.is_open())
        {
            outFile << acc.toFileString() << "\n";
            outFile.close();
        }
        else
        {
            cout << "[x] Error: Unable to save account to file.\n";
        }
    }

    void loadAccountsFromFile()
    {
        ifstream inFile(filename);
        string line;

        if (inFile.is_open())
        {
            while (getline(inFile, line))
            {
                size_t pos1 = line.find(',');
                size_t pos2 = line.rfind(',');

                if (pos1 == string::npos || pos2 == string::npos || pos1 == pos2)
                {
                    cerr << "[WARNING] Skipping malformed line: " << line << endl;
                    continue;
                }

                string name = line.substr(0, pos1);
                int accountNumber = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
                float balance = stof(line.substr(pos2 + 1));

                accounts.emplace_back(name, accountNumber, balance);
            }
            inFile.close();
        }
    }
};

int main()
{
    BankSystem bank;
    int choice;

    do
    {
        cout << "\n=========== Bank Management Menu ===========\n";
        cout << "1. Create Account\n";
        cout << "2. View All Accounts\n";
        cout << "3. Search Account by Number\n";
        cout << "4. Exit\n";
        cout << "============================================\n";
        cout << "Enter your choice (1-4): ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "[x] Invalid input. Please enter a number.\n";
            continue;
        }
        cin.ignore();

        string name;
        int accNum;
        float balance;

        switch (choice)
        {
            case 1:
                cout << "\nEnter Name: ";
                getline(cin, name);

                cout << "Enter Account Number: ";
                if (!(cin >> accNum))
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "[x] Invalid account number.\n";
                    break;
                }

                cout << "Enter Initial Balance: ";
                if (!(cin >> balance))
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "[x] Invalid balance amount.\n";
                    break;
                }
                cin.ignore();

                bank.createAccount(name, accNum, balance);
                break;

            case 2:
                bank.viewAllAccounts();
                break;

            case 3:
                cout << "\nEnter Account Number to search: ";
                if (!(cin >> accNum))
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "[x] Invalid account number.\n";
                    break;
                }
                bank.searchAccount(accNum);
                break;

            case 4:
                cout << "\nExiting... Thank you for using the system.\n";
                break;

            default:
                cout << "[x] Invalid choice. Please select from 1 to 4.\n";
        }
    } while (choice != 4);

    return 0;
}
