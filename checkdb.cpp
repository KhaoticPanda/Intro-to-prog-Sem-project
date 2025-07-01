#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Function to display student menu
void studentMenu(const string& username) {
    int choice;
    do {
        cout << "\n--- Student Menu ---\n";
        cout << "1. Borrow a book\n";
        cout << "2. Check account balance\n";
        cout << "3. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Borrow book feature coming soon.\n";
                break;
            case 2:
                cout << "Check balance feature coming soon.\n";
                break;
            case 3:
                cout << "Logging out...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);
}

// Function to check student credentials
bool checkStudentCredentials(string& username) {
    string fileUsername, filePassword;
    double balance; // Add this for the third column
    string password;

    ifstream credFile("studentDB.txt");
    if (!credFile) {
        cout << "Could not open student database file." << endl;
        return false;
    }

    cout << "Enter student username: ";
    cin >> username;
    cout << "Enter student password: ";
    cin >> password;

    bool found = false;
    // Read username, password, and balance from each line
    while (credFile >> fileUsername >> filePassword >> balance) {
        if (username == fileUsername && password == filePassword) {
            found = true;
            cout << "Student login successful!" << endl;
            cout << "Your current balance is: " << balance << endl;
            break;
        }
    }
    credFile.close();

    if (!found) {
        cout << "Invalid student credentials." << endl;
    }
    return found;
}

int main() {
    cout << "*****************************************" << endl;
    cout << "******  WELCOME TO GREAT MINDS LIBRARY  ******" << endl;
    cout << "How do you want to login?" << endl;
    cout << "1. As a student" << endl;
    cout << "2. As a librarian" << endl;
    cout << "3. As a guest" << endl;

    cout << "Please enter your  choice (1-3): ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        string username;
        if (checkStudentCredentials(username)) {
            studentMenu(username); // Show student menu after successful login
        }
    }
    // ...librarian and guest code...
    return 0;
}

