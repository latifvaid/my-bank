//
// Author: Latif Vaid, UIC, Spring 2021
// Assignment: Project 02, part 1, part 2
//
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;



//
// Deposit:+ account amount
// Withdrawal:-account amount
// Check balance:? account
// Find the account with the largest balance: ^
// List accounts and balances in range:* low high
// List of accounts with a negative balance: <
//Total of all positive balances in the bank: $
// Add a new account: add
//Delete an existing account: del acct
// Exit: x
//






void checkArrays(int accounts[], double balance[],int N){
    cout << fixed;
    cout << setprecision(2);
    cout << "** Checking arrays..." << endl;
    cout << "1. " << accounts[0] << ", $" << balance[0] << endl;
    cout << N << ". " << accounts[N-1] << ", $" << balance[N-1] << endl;
}


// the account that matches "acct". If found, the index of that
// account is returned; if not found -1 is returned.
//
int search(int accounts[], int N,int acct){
    
    for(int i = 0; i < N; i++){
        if(acct == accounts[i]){
            return i;
//             cout << accounts[i] << i << endl;
        }
    }
    return -1;
}

//
// maxBalance
//
// Given an array of N balances, searches for the highest balances
// and returns the index of this balance. If there's a tie, the
// first (smaller) index is returned. Assumes N > 0.
//
int maxBalance(double balance[], int N){
    double max = balance[0];
    int largest = 0;

    for(int i = 1; i < N; i++){
        if(max < balance[i]){
            max = balance[i];
            largest = i;
        }   
    }
    return largest;
}

void lowtoHigh(int accounts[], double balance[], int N, int low, int high){
    for(int i = 0; i < N; i++){
        if(accounts[i] >= low && accounts[i] <= high){
            cout << "Account " << accounts[i] << ": "<< "balance $" << balance[i] << endl;
        }
    }
}

int main(){
    

    
    string filename;
    cout << "** Welcome to UIC Bank v2.0 **" << endl;
    cout << "Enter bank filename> " << endl;
    cin >> filename;
    cout << "** Inputting account data..." << endl;
    fstream infile(filename);
    cout << fixed;
    cout << setprecision(2);
    if(!infile.good()){ 
        cout << "**Error: unable to open input file " << "'" << filename << "'" << endl;
        return 0;
    }
    
    string line;   
    string line2;
    int N;
    infile >> N; //gets the size of the array by looking the first line in file and calling it N
    
    int* accounts;
    accounts = new int[N];  
    
    double* balance;
    balance = new double[N];
    
    int i = 0;
    
    //getting all the data into 2 arrays balance and accounts so we can use that array for adding things
    while(i < N){
        infile >> line;                     //gets the first number till space and stores in line
//         cout << line << " " << endl;
        accounts[i] = stoi(line);           //string to int and saving the data as int(accounts)
        infile >> line2; 
        balance[i]= stod(line2);               // string to double and saving data as double(balance)
        i++;
    }
    checkArrays(accounts, balance, N);
    cout << "** Processing user commands..." << endl;
    string cmd;
    int acct;
    double addBal;
    int index = 0;
    while(cmd != "x"){ //loops until cmd is x
        cout << "Enter command (+, -, ?, ^, *, <, $, add, del, x): " << endl;
        cin >> cmd;
        if(cmd == "+"){
            cin >> acct;
            cin >> addBal;
            index = search(accounts, N, acct); //calling search function to find the account so we can get the index of it
            if(index == -1){         //if -1 is returned then did not find that account
                cout << "** Invalid account, transaction ignored" << endl;
            } else {
                balance[index] = balance[index] + addBal;
                cout << "Account " << accounts[index] << ": "<< "balance $" << balance[index] << endl;  
            }
        }
        else if(cmd == "-"){
            cin >> acct;
            cin >> addBal;
            index = search(accounts, N, acct); //calling search function to find the account so we can get the index of it
            if(index == -1){                  //if -1 is returned then did not find that account
                cout << "** Invalid account, transaction ignored" << endl;
            } else {
                balance[index] = balance[index] - addBal;
                cout << "Account " << accounts[index] << ": "<< "balance $" << balance[index] << endl;
            }
        }
        else if(cmd == "?"){
            cin >> acct;
            index = search(accounts, N, acct); //calling search function to find the account so we can get the index of it
            if(index == -1){ //if -1 is returned then did not find that account
                cout << "** Invalid account, transaction ignored" << endl;
            } else {
            cout << "Account " << accounts[index] << ": "<< "balance $" << balance[index] << endl;
            }
        }
        else if(cmd == "^"){
            index = maxBalance(balance, N); //calling maxBalance function so we can get the index of max balance
                cout <<"Account " << accounts[index] << ": balance $" << balance[index] << endl;
        }
        else if(cmd == "*"){
            int low, high;
            cin >> low;
            cin >> high;
            
           lowtoHigh(accounts, balance, N, low, high); //calls lowtoHigh function to get index from low to high
        }
        
        else if(cmd == "<"){         
            for(int i = 0; i < N; i++){
                if(balance[i] < 0){
                    cout <<"Account " << accounts[i] << ": balance $" << balance[i] << endl;
                }
            }
        }
        else if(cmd == "$"){ 
            double total = 0;
            for(int i = 0; i < N; i++){
                if(balance[i] > 0){
                    total = total + balance[i];
                }
            }
            cout << "Total deposits: $" << total << endl;
        }
        else if(cmd == "add"){
            int newacct = accounts[N-1];
            newacct += 1;
            int* newAccounts;
            newAccounts = new int[N+1];  
            double* newBalance;
            newBalance = new double[N+1];
            
            
            for(int i = 0; i < N+1; i++){
                if(i < N){
                    newAccounts[i] = accounts[i];
                    newBalance[i] = balance[i];
                }
                else{
                    newAccounts[i] = newacct;
                    newBalance[i] = 0;
                    cout <<"Added account " << newAccounts[i] << ": balance $" << newBalance[i] << endl;
                }
            }

            delete[] accounts;
            delete[] balance;
            accounts = newAccounts;
            balance = newBalance;
            N += 1;

            
        }
        else if(cmd == "del"){
            cin >> acct;
            
            int counter = 0;
                  
            for(int i = 0; i <= N; i++){
                
               if(accounts[i] == acct){
                   index = i;
                   N = N - 1;
                   for(int j = index; j < N; j++){
                       accounts[j] = accounts[j+1];
                       balance[j] = balance[j+1];
                   }
                   cout << "Deleted account " << acct << endl;
               }
               else{
                   counter++;
               }
            }

            if(counter == N+1){
                cout << "** Invalid account, transaction ignored" << endl;
            }
        }
        else if(cmd == "x"){
            break;
        }
        else{
            cout << "** Invalid command, try again..." << endl;
        }
    }
    infile.close(); //closing file after we are done using the data
    
    //opening the same file to input the the data that we changed
    ofstream outfile;
    outfile.open(filename);
    outfile << fixed;
    outfile << setprecision(2); //saving as double
    outfile << N << endl;
        
         
//     for(int i = 0; i < N; i++){
//         cout << accounts[i] << " " << balance[i] << endl;
//     }
    int j = 0;
    while(j < N){
        outfile << accounts[j] << " " << balance[j] << endl; //adding the data edited by the user in the file
        j++;
    }
    outfile.close(); 
    cout << "** Saving account data..." << endl;
    cout << "** Done **" << endl;
    delete[] accounts;
    delete[] balance;
    return 0;
}