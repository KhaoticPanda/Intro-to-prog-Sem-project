#include <iostream>
using namespace std;
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
    cout<<"\nEnter librarian passwprd: ";
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
                //registerStudent();
                break;
            case 2:
                //approveBorrowRequest();
                break;
            case 3:
                //acceptReturn();
                break;
            case 4:
                //changePassword();
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
        //student();
    }else if(role==2)
    {
        librarian();
    }else{
        cout<<"Invalid Choice.";
    }
    return 0;
}
