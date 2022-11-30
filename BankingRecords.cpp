#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
using namespace std;

class Account
{
private:
    long int account_id = 1226450000;
    char firstName[10];
    char lastName[10];
    long phone_number;
    float total_Balance;

public:
    void readData()
    {
        cout << "\nEnter First Name: ";
        cin >> firstName;
        cout << "Enter Last Name: ";
        cin >> lastName;
        cout << "Enter Phone Number: ";
        cin >> phone_number;
        cout << "Enter Balance: ";
        cin >> total_Balance;
        cout << endl;
    }
    void showData()
    {
        cout << "Account ID: " << account_id << endl;
        cout << "First Name: " << firstName << endl;
        cout << "Last Name: " << lastName << endl;
        cout << "Phone Number: " << phone_number << endl;
        cout << "Current Balance: Rs.  " << total_Balance << endl;
        cout << "---------------------------------------------------------------" << endl;
    }
    void writeRecord()
    {
        ofstream outfile;
        ifstream infile;
        infile.open("rec.bank", ios::binary);
        infile.seekg(0, ios::end);
        int count = infile.tellg() / sizeof(*this);
        outfile.open("rec.bank", ios::binary | ios::app); // ios - input output stream | app - append
        // ios::app is set, all output operations are performed at the end of the file.
        readData();

        if (count == -1)
            count++;
        cout << count;
        account_id = 1226450000 + count + 1;
        outfile.write(reinterpret_cast<char *>(this), sizeof(*this));
        infile.close();
        outfile.close();
    }
    void readRecord()
    {
        ifstream infile;
        infile.open("rec.bank", ios::binary);
        if (!infile)
        {
            cout << "Error in Opening! File Not Found!!" << endl;
            return;
        }
        cout << "\n\t****Data from file****" << endl;
        cout << "---------------------------------------------------------------" << endl;
        while (!infile.eof())
        {
            if (infile.read(reinterpret_cast<char *>(this), sizeof(*this)))
            {
                showData();
            }
        }
        infile.close();
    }
    void searchRecord()
    {
        int n;
        ifstream infile;
        infile.open("rec.bank", ios::binary);
        if (!infile)
        {
            cout << "\nError in opening! File Not Found!!" << endl;
            return;
        }
        cout << "\nEnter Account ID to Search: ";
        cin >> n;
        if (n > 1226450000)
        {
            n = n - 1226450000;
            cout << endl;
            infile.seekg((n - 1) * sizeof(*this));
            infile.read(reinterpret_cast<char *>(this), sizeof(*this));
            showData();
        }
        else
            cout << "Account ID does not exist" << endl;
    }
    void editRecord()
    {
        int n, input;
        fstream iofile;
        iofile.open("rec.bank", ios::in | ios::binary);
        if (!iofile)
        {
            cout << "\nError in opening! File Not Found!!" << endl;
            return;
        }
        cout << "\nEnter Account ID to Search: ";
        cin >> input;
        if (input > 1226450000)
        {
            n = input - 1226450000;
            iofile.seekg((n - 1) * sizeof(*this));
            iofile.read(reinterpret_cast<char *>(this), sizeof(*this));
            cout << "Account " << input << " has following data" << endl;
            showData();
            iofile.close();
            iofile.open("rec.bank", ios::out | ios::in | ios::binary);
            iofile.seekp((n - 1) * sizeof(*this));
            cout << "\nEnter data to Modify " << endl;
            readData();
            account_id = input;
            iofile.write(reinterpret_cast<char *>(this), sizeof(*this));
        }
        else
            cout << "Account ID does not exist" << endl;
    }
    void deleteRecord()
    {
        int n, input;
        fstream iofile;
        iofile.open("rec.bank", ios::in | ios::binary);
        if (!iofile)
        {
            cout << "\nError in opening! File Not Found!!" << endl;
            return;
        }
        cout << "\nEnter Account ID to Search: ";
        cin >> input;
        if (input > 1226450000)
        {
            n = input - 1226450000;
            iofile.seekg((n - 1) * sizeof(*this));
            iofile.read(reinterpret_cast<char *>(this), sizeof(*this));
            cout << "Record " << n << " has following data" << endl;
            showData();
            iofile.close();
            iofile.open("rec.bank", ios::out | ios::in | ios::binary);
            iofile.seekp((n - 1) * sizeof(*this));
            account_id = input;
            strcpy(firstName,"DELETED");
            strcpy(lastName,"DELETED");
            phone_number = 0;
            total_Balance = 0;
            iofile.write(reinterpret_cast<char *>(this), sizeof(*this));
        }
        else
            cout << "Account ID does not exist" << endl;
    }
};
int main()
{
    Account A;
    int choice;
    cout << "\t*** BANK RECORDS MANAGMENT SYSTEM ***" << endl;
    cout << "---------------------------------------------------------------" << endl;
    cout << "\tWelcome USER ";
    while (true)
    {
        cout << "\n\t1 --> Add record to file";
        cout << "\n\t\t2 --> Display record from file";
        cout << "\n\t\t\t3 --> Search Record from file";
        cout << "\n\t\t\t4 --> Update Record";
        cout << "\n\t\t5 --> Delete Record";
        cout << "\n\t6 --> Quit";
        cout << "\nEnter your choice: ";
        cin >> choice;
        cout << "---------------------------------------------------------------" << endl;
        switch (choice)
        {
        case 1:
            A.writeRecord();
            break;
        case 2:
            A.readRecord();
            break;
        case 3:
            A.searchRecord();
            break;
        case 4:
            A.editRecord();
            break;
        case 5:
            A.deleteRecord();
            break;
        case 6:
            exit(0);
            break;
        default:
            cout << "\nEnter correct choice";
            break;
        }
    }
    return 0;
}