#include <iostream>
#include <fstream>
#include <string>
using namespace std;
void requestBorrowBook(const string& username) {
    string bookName;
    cout << "Enter the name of the book you want to borrow: ";
    cin >> bookName;

    ifstream in("studentDB.txt");
    ofstream out("StudentDBupdated.txt");

    string fileUsername, filePassword, borrowRequest, returnRequest;
    double balance;
    bool found = false;

    while (in >> fileUsername >> filePassword >> balance >> borrowRequest >> returnRequest) {
        if (fileUsername == username) {
            found = true;
            if (borrowRequest == "none") {
                borrowRequest = bookName;
            } else {
                borrowRequest += "," + bookName;
            }
            cout << "Borrow request submitted successfully.\n";
        }

        out << fileUsername << " " << filePassword << " " << balance << " "
            << borrowRequest << " " << returnRequest << endl;
    }

    in.close();
    out.close();

    remove("studentDB.txt");
    rename("StudentDBupdated.txt", "studentDB.txt");

    if (!found) {
        cout << "Username not found in the database.\n";
    }
}
void acceptReturn() {
    string fileUsername, filePassword, borrowRequest, returnRequest;
    double balance;
    bool anyReturnFound = false;

    // First, scan and show students with return requests
    ifstream preview("studentDB.txt");
    cout << "\n--- Students with Pending Return Requests ---\n";
    while (preview >> fileUsername >> filePassword >> balance >> borrowRequest >> returnRequest) {
        if (returnRequest != "none") {
            cout << " - " << fileUsername << " wants to return: " << returnRequest << endl;
            anyReturnFound = true;
        }
    }
    preview.close();

    if (!anyReturnFound) {
        cout << "No return requests found.\n";
        return;  // Exit early since there's nothing to do
    }

    // Ask admin which student to process
    string username;
    cout << "\nEnter student username to process return: ";
    cin >> username;

    // Load book inventory
    const int MAX_BOOKS = 100;
    string bookNames[MAX_BOOKS];
    int bookCopies[MAX_BOOKS];
    int bookCount = 0;

    ifstream bookIn("booksDB.txt");
    string bookName;
    int copiesAvailable;

    while (bookIn >> bookName >> copiesAvailable) {
        bookNames[bookCount] = bookName;
        bookCopies[bookCount] = copiesAvailable;
        bookCount++;
    }
    bookIn.close();

    // Process the selected student's return
    ifstream in("studentDB.txt");
    ofstream out("StudentDBupdated.txt");
    bool studentFound = false;

    while (in >> fileUsername >> filePassword >> balance >> borrowRequest >> returnRequest) {
        if (fileUsername == username) {
            studentFound = true;
            if (returnRequest == "none") {
                cout << "This user has no return request.\n";
            } else {
                cout << "Processing return of book: " << returnRequest << endl;
                for (int i = 0; i < bookCount; i++) {
                    if (bookNames[i] == returnRequest) {
                        bookCopies[i]++;
                        break;
                    }
                }
                returnRequest = "none";
                cout << "Book return accepted for user: " << username << endl;
            }
        }

        out << fileUsername << " " << filePassword << " " << balance << " "
            << borrowRequest << " " << returnRequest << endl;
    }

    in.close();
    out.close();

    // Update student database
    remove("studentDB.txt");
    rename("StudentDBupdated.txt", "studentDB.txt");

    // Update book database
    ofstream bookOut("booksDB.txt");
    for (int i = 0; i < bookCount; i++) {
        bookOut << bookNames[i] << " " << bookCopies[i] << endl;
    }
    bookOut.close();

    if (!studentFound) {
        cout << "No student found with username: " << username << endl;
    }
}
void approveBorrowRequest() {
    string username, password, borrowRequest, returnRequest;
    int balance;

    ifstream bookFile("booksDB.txt");
    string bookName;
    int copiesAvailable;

    const int MAX_BOOKS = 100;
    string bookNames[MAX_BOOKS];
    int bookCopies[MAX_BOOKS];
    int bookCount = 0;

    while (bookFile >> bookName >> copiesAvailable) {
        bookNames[bookCount] = bookName;
        bookCopies[bookCount] = copiesAvailable;
        bookCount++;
    }
    bookFile.close();

    ifstream studentFile("studentDB.txt");
    ofstream updatedFile("updatedDB.txt");

    bool anyRequestFound = false;

    while (studentFile >> username >> password >> balance >> borrowRequest >> returnRequest) {
        if (borrowRequest != "none") {
            for (int i = 0; i < bookCount; i++) {
                if (bookNames[i] == borrowRequest) {
                    if (bookCopies[i] > 0) {
                        borrowRequest = "none";
                        bookCopies[i] -= 1;
                        anyRequestFound = true;
                    } else {
                        cout << "Book not available for " << username << endl;
                    }
                    break;
                }
            }
        }
        updatedFile << username << " " << password << " " << balance << " " << borrowRequest << " " << returnRequest << endl;
    }

    studentFile.close();
    updatedFile.close();

    if (!anyRequestFound) {
        cout << "No borrow requests found.\n\n";
    }

    ofstream bookOut("booksDB.txt");
    for (int i = 0; i < bookCount; i++) {
        bookOut << bookNames[i] << " " << bookCopies[i] << endl;
    }
    bookOut.close();

    remove("studentDB.txt");
    rename("updatedDB.txt", "studentDB.txt");
}
void requestReturnBook(const string& username) {
    string bookName;
    cout << "Enter the name of the book you want to return: ";
    cin >> bookName;

    ifstream in("studentDB.txt");
    ofstream out("StudentDBupdated.txt");

    string fileUsername, filePassword, borrowRequest, returnRequest;
    double balance;
    bool found = false;

    while (in >> fileUsername >> filePassword >> balance >> borrowRequest >> returnRequest) {
        if (fileUsername == username) {
            found = true;
            if (returnRequest != "none") {
                cout << "You already have a pending return request.\n";
            } else {
                returnRequest = bookName;
                cout << "Return request submitted successfully.\n";
            }
        }
        out << fileUsername << " " << filePassword << " " << balance << " "
            << borrowRequest << " " << returnRequest << endl;
    }

    in.close();
    out.close();

    remove("studentDB.txt");
    rename("StudentDBupdated.txt", "studentDB.txt");

    if (!found) {
        cout << "Username not found in the database.\n";
    }
}

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
            cout<<"--------------------------\n\n";
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
            cout << "2. Request to borrow a book\n";
            cout << "3. Return borrowed book\n";
            cout << "4. Change password\n";
            cout << "5. Exit\n\n";
            cout << "Enter option to proceed: ";
            cin >> option;

            switch (option) {
                case 1:
                     viewPersonalDetails(inputUsername);
                    break;
                case 2:
                    requestBorrowBook(inputUsername);
                    break;
                case 3:
                    requestReturnBook(inputUsername);
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
        cout<<"3.Accept returned book\n\t";
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
                approveBorrowRequest();
                break;
            case 3:
                acceptReturn();
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
