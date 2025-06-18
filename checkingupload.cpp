#include <iostream>
#include <string>
using namespace std;

int main() {
    string correctUsername = "admin";
    string correctPassword = "password123";
    string username, password;

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (username == correctUsername && password == correctPassword) {
        cout << "Login successful!" << endl;
    } else {
        cout << "Invalid username or password." << endl;
    }

    return 0;
}