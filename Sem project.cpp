#include <iostream>
#include <fstream>
#include <string>
using namespace std;
// A FUNCTION TO VIEW PERSONAL DETAILS OF STUDENT
void viewPersonalDetails(const string& username) {
    ifstream in("studentDB.txt");
    string fileUsername, filePassword, borrowRequest, returnRequest;
    double balance;
    bool found = false;

    while (in >> fileUsername >> filePassword >> balance >> borrowRequest >> returnRequest) {
        if (fileUsername == username) {
            cout << "\n--- Personal Details ---\n";
            cout << "Username: " << fileUsername << endl;
            cout << "Account Balance: " << balance << endl;
            cout << "Borrow Request: " << borrowRequest << endl;
            cout << "Return Request: " << returnRequest << endl;
            found = true;
            break;
        }
    }
    in.close();

    if (!found) {
        cout << "No details found for user: " << username << endl;
    }
}
// A FUNCTION TO REGISTER A NEW STUDENT


void registerStudent() {
    ofstream file("studentDB.txt", ios::app);
    string username, password;
    double balance = 1000;
    string borrowRequest = "none";
    string returnRequest = "none";

    cout << "Enter new student's username: ";
    cin >> username;
    cout << "Enter new student's password: ";
    cin >> password;

    file << username << " " << password << " " << balance << " " << borrowRequest << " " << returnRequest << endl;
    file.close();
    cout << "Student added successfully.\n";
}
// A FUNCTION TO CHANGE ADMIN PASSWORD
void changeAdminPassword(){
    string username, password, oldPass, newPass;
    ifstream in("admin.txt");
    in >> username >> password;
    in.close();

    cout << "Enter your current password: ";
    cin >> oldPass;
    if (oldPass == password) {
        cout << "Enter your new password: ";
        cin >> newPass;

        ofstream out("admin.txt");
        out << username << " " << newPass;
        out.close();

        cout << "Password changed successfully!\n";
    } else {
        cout << "Current password is incorrect.\n";
    }
}
// A FUNCTION TO CHANGE STUDENT PASSWORD

void changePassword(const string& username) {
    string oldPass, newPass;
    string fileUsername, filePassword, borrowRequest, returnRequest;
    double balance;
    bool changed = false;

    ifstream in("studentDB.txt");
    ofstream out("StudentDBupdated.txt");

    while (in >> fileUsername >> filePassword >> balance >> borrowRequest >> returnRequest) {
        if (fileUsername == username) {
            cout << "Enter your current password: ";
            cin >> oldPass;
            if (oldPass == filePassword) {
                cout << "Enter your new password: ";
                cin >> newPass;
                filePassword = newPass;
                changed = true;
            } else {
                cout << "Current password is incorrect.\n";
            }
        }
        out << fileUsername << " " << filePassword << " " << balance << " " << borrowRequest << " " << returnRequest << endl;
    }
    in.close();
    out.close();

    remove("studentDB.txt");
    rename("StudentDBupdated.txt", "studentDB.txt");

    if (changed) {
        cout << "Password changed successfully!\n";
    }
}
// A FUNCTION TO VALIDATE STUDENT LOGIN INFO
void student() {
    ifstream inData("studentDB.txt");
    string storedUsername, storedPassword, borrowRequest, returnRequest;
    string inputUsername, inputPassword;
    int balance, option;
    bool loginSuccess = false;

    cout << "Enter your username: ";
    cin >> inputUsername;
    cout << "Enter your password: ";
    cin >> inputPassword;

    while (inData >> storedUsername >> storedPassword >> balance >> borrowRequest >> returnRequest) {
        if (inputUsername == storedUsername && inputPassword == storedPassword) {
            loginSuccess = true;
            break;
        }
    }

    inData.close();

    if (loginSuccess) {
        cout << "Successfully logged in!..\n\n";
        do {
            cout << "Select one option below\n";
            cout << "1. View Personal Details\n";
            cout << "2. Request to borrow/rent a book\n";
            cout << "3. Return borrowed/rented book\n";
            cout << "4. Change password\n";
            cout << "5. Exit\n\n";
            cout << "Enter option to proceed: ";
            cin >> option;

            switch (option) {
                case 1:
                     viewPersonalDetails(inputUsername);
                    break;
                case 2:
                    // RequestBorrowBook();
                    break;
                case 3:
                    // RequestCheckoutBook();
                    break;
                case 4:
                    changePassword(inputUsername);
                    break;
                case 5:
                    cout << "Logging out...";
                    break;
                default:
                    cout << "Invalid option. Try again\n";
            }
        } while (option != 5);
    } else {
        cout << "Invalid username or password";
    }
}
// A FUNCTION TO HANDLE LIBRARIAN LOGIN AND OPTIONS
void librarian(){
    ifstream inData;
    string storedUsername, storedPassword;
    string username, password;
    int option;
    inData.open("admin.txt");
    inData>>storedUsername>>storedPassword;
    inData.close();
    cout<<"Enter librarian username: ";
    cin>>username;
    cout<<"\nEnter librarian password: ";
    cin>>password;
    if(username==storedUsername && password==storedPassword)
    {
        cout<<"Successfully logged in!..\n\n";
        do{
        cout<<"Select one option below\n\t";
        cout<<"1.Register new student\n\t";
        cout<<"2.Approve student\'s request to borrow book\n\t";
        cout<<"3.Accept returned book and update system\n\t";
        cout<<"4.Change password\n\t";
        cout<<"5.Exit\n\n";
        cout<<"Enter option to proceed: ";
        cin>>option;
        switch(option)
        {
            case 1:
                registerStudent();
                break;
            case 2:
                //approveBorrowRequest();
                break;
            case 3:
                //acceptReturn();
                break;
            case 4:
                changeAdminPassword();
                break;
            case 5:
                cout<<"Logging out...";
                break;
            default:
                cout<<"invalid option. Try again\n";

        }
        }while(option!=5);
    }else{
        cout<<"Invalid username or password";
    }

}

// MAIN FUNCTION TO SELECT ROLE AND PROCEED
int main()
{
    int role;
    cout<<"******Welcome to the Library ******\n\n";
    cout<<"Select your role to proceed:";
    cout<<"\n\t1.Normal Student Login\n";
    cout<<"\t2.Librarian Login\n\n";
    cout<<"Enter your role to proceed: ";
    cin>>role;
    if(role==1)
    {
        student();
    }else if(role==2)
    {
        librarian();
    }else{
        cout<<"Invalid Choice.";
    }
    return 0;
}
