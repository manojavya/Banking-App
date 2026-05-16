/*
v1.9.0 Stable Release | Private Release | No Commercial |
Developed by Manojavya P.M
Made proudly on Arch Linux in India
*/
#include <ctime>
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>

using namespace std;

string uname;

void program(string cu){
    cout << "\nWelcome " << cu << endl;
    cout << "What would you like to perfrom today?" << endl;
    ifstream is;
    ofstream os;
    is.open("functions.txt");
    string func;
    while(getline(is, func)){
        cout << func << endl;
    }
    is.close();
    int op;
    cin >> op;
    cin.ignore();
    string i;

    //Set the balance of the user:
    is.open(uname+"/account/balance.txt");
    double balance = 0.0;
    while(getline(is, i)){
        balance = stod(i);
    }
    is.close();
    string dbstr;

    //Set the creditcard debt
    double debt = 0.0;
    is.open(uname + "/account/creditdebt.txt");
    while(getline(is, dbstr)){
        debt = stod(dbstr);
    }
    is.close();

    //Set credit card limit to 20 lakhs
    double crdtlimit = 2000000;
    
    double ws = 0.0;
    double wc = 0.0;

    // wc: Withdrwaw Credit
    //ws: Withdraw Savings

    //1. Test
    if(op == 1){
        cout << "All is good!" << endl;
        cout << "Balance: " << balance << endl;
        cout << "Credit debt: " << debt << endl;
    }
    //2. Check Balance of savings account
    else if(op == 2){
        cout << "Your balance is: "; //Total balance should be saved to users balance file, which will be read by the app
        is.open(uname + "/account/balance.txt");
        string strbal;
        while(getline(is, strbal)){
            cout << strbal << endl;
        }
    }
    //Deposit money to savings
    else if(op == 3){
        cout << "Deposit money to svaings: " << endl;
        os.open(uname + "/account/balance.txt");
        double in;
        cin >> in;
        cin.ignore();
        os << in;
        os.flush();
        os.close();
        cout << "Added " << in << "rs to savings account" << endl;;
    }
    //Desposits Debt to credit account
    else if(op == 4){
        double da;
        string db;
        //da: depostied amount
        cout << "You have a debt of " << debt << "rs." << endl;
        cout << "Pay only one at a time please!" << endl;
        cout << "Enter the amount you would like to deposit: " << endl;
        cin >> da;
        cin.ignore();
        if(da > balance){
            cout << "You do not have enough money in your savings account to fill the debt!" << endl;
            return;
        }
        else if(da < 0){
            cout << "You cannot pay in negatives!" << endl; 
            return;
        }
        else if(debt < 0){
            cout << "You have no debt!!" << endl;
            return;
        }
        else if(da > debt){
            cout << "You are trying to deposit more than your debt!!!" << endl;
            return;
        }
        is.open(uname + "/account/creditdebt.txt");
        if(getline(is, db)){
            //da = stod(db);
            debt = debt - da;
            is.close();
            os.open(uname + "/account/creditdebt.txt");
            os << debt;
            os.flush();
            os.close();
            balance -= da;
            os.open(uname + "/account/balance.txt");
            os << balance;
            os.flush();
            os.close();
        }
    }
    //withdraws money from savings account
    else if(op == 5){
        double wa;
        string bastr;
        //bastr: balance stored in the form of a string whihc will be converted to double again using stod
        //wa: withdrawn amount
        cout << "How much would you like to withdraw? " << endl;
        cin >> wa;
        if(wa > balance){
            cout << "You dont have enough in your savings!" << endl;
        }
        cin.ignore();
        is.open(uname + "/account/balance.txt");
        if(getline(is, bastr)){
            balance = stod(bastr) - wa;
            is.close();
            os.open(uname + "/account/balance.txt");
            os << balance;
            os.flush();
            os.close();
        }
        cout << "Now your balance is: " << balance << endl;
    }
    //Withdraws money from credit card
    else if(op == 6){
        double wa;
        //wa: withdrawn amount
        cout << "You have a debt of: " << debt << "rs." << endl;
        cout << "Please ensure your debt is below 20Lakh rs." << endl;
        cout << "You have a total credit limit of: " << crdtlimit << "rs. how much would you like to withdraw. (No interest)" << endl;
        cin >> wa;
        cin.ignore();
        if(wa > crdtlimit){
            cout << "Sorry, you are exceeding the credit account limit of rs20,00,000" << endl;
            return;
        }
        else if(debt + wa > crdtlimit){
            cout << "Please be a responsible banker by paying your debt first!" << endl;
            return;
        }
        debt += wa;
        balance += wa;
        os.open(uname + "/account/creditdebt.txt");
        os << debt;
        os.flush();
        os.close();
        os.open(uname + "/account/balance.txt");
        os << balance;
        os.flush();
        os.close();
        cout << "Now your debt is: " << debt << endl;
        cout << "Now your balance is: " << balance << endl;
    }
    else{
        try{
            throw 100;
        }
        catch(int excep){
            cout << "Program Unexpectedly exited with code: " << excep << endl;
        }
    }
}

int main(){
    bool auth_uname = false;
    bool auth_passwd = false;
    ofstream os;
    ifstream is;
    time_t ts;
    time(&ts);
    cout << "Program was initialized at " << ctime(&ts);
    //string uname;
    string passwd;
    char ls;
    cout << "Please login or signup (L/S)" << endl;
    cin >> ls;
    cin.ignore();
    if (ls == 'L'){
        is.open("username.txt");
        cout << "User name: " << endl;
        cin >> uname;
        cin.ignore();
        string loggedname;
        while(getline(is, loggedname)){
            if (uname == loggedname){
                cout << "Found user name: " << endl;
                auth_uname = true;
                is.close();
                break;
            }
        }
        if(auth_uname == true){
            cout << "password: " << endl;
            cin >> passwd;
            cin.ignore();
            is.open("passwd.txt");
            string file_passwd;
            while(getline(is, file_passwd)){
                if(file_passwd == passwd){
                    cout << "Password correct" << endl;
                    auth_passwd = true;
                    is.close();
                    break;
                }
            }
        }
        if(auth_passwd == false){
            try{
                throw 101;
            }
            catch(int excep){
                cout << "Program Unexpectedly exited with code: " << excep << endl;
                cout << "Username or Password was incorrect" << endl;
            }
        }
    }
    else if (ls == 'S'){
        os.open("username.txt", ios::app);
        cout << "Please enter user name (this will also be your login name)" << endl;
        cin >> uname;
        cin.ignore();
        os << uname << "\n";
        os.flush();
        os.close();
        os.open("passwd.txt", ios::app);
        cout << "Please enter your password" << endl;
        cin >> passwd;
        cin.ignore();
        //DEBUG LINE TO CHECK WEATHER PASSWORD WAS TAKEN IN BY C++: cout << passwd << endl;
        os << passwd << "\n";
        os.flush();
        os.close();
        cout << "Continue with login!" << endl;
        return 0;
    }
    if(auth_passwd == true && auth_uname == true){
        cout << "Login successful" << endl;
        filesystem::create_directories(uname + "/account/");
        program(uname);
    }
    else{
        try{
            throw 102;
        }
        catch(int excep){
            cout << "Program Unexpectedly exited with code: " << excep << endl;
        }
    }
}