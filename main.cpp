#include<iostream>
#include<map>
#include<fstream>
using namespace std;

class Account{
	string name;
	double balance;
	int AccNo;
	static int nextAccNo;
public:
	Account();
	Account(string name, double balance);
	string getName(){return name;};
	double getBalance(){return balance;};
	int getAccNo(){return AccNo;};
	void Deposit(double amount){balance += amount;};
	void Withdraw(double amount){balance -= amount;};
	static void setLastAccNo(int AccNo);
	static int getLastAccNo();
	friend ofstream & operator<<(ofstream &ofs, Account &acc);
	friend ifstream & operator>>(ifstream &ifs, Account &acc);
	friend ostream & operator<<(ostream & out, Account &acc);
};
int Account::nextAccNo = 0;

class Bank{
private:
	map<int,Account> accounts;

public:
	Bank();
	Account OpenAccount(string name, double balance);
	Account Balance(int accNo);
	Account Deposit(int accNo, double balance);
	Account Withdraw(int accNo, double balance);
	void closeAccount(int accNo);
	void viewAll();
	~Bank();

};

int main(){
	Bank b;
	Account acc;
	int accNo;
	std::string name;
	double balance;
	double amount;

	auto input = 0;
	do{
		cout << "Select one option below:" << endl;
		cout << "1 Open an Account" << endl;
		cout << "2 Balance Enquiry" << endl;
		cout << "3 Deposit" << endl;
		cout << "4 Withdraw" << endl;
		cout << "5 Close Account" << endl;
		cout << "6 Show All Accounts" << endl;
		cout << "7 Quit" << endl;
		cin >> input;

		switch(input){
		case 1:
			cout << "Open an account:" << endl;
			cout << "Enter name: ";
			cin >> name;
			cout << "Enter starting balance: ";
			cin >> balance;
			acc = b.OpenAccount(name, balance);
			cout << endl << "Account Created" << endl;
			cout << acc << endl;
			break;

		case 2:
			cout << "Balance Enquiry:" << endl;
			cout << "Enter account number: ";
			cin >> accNo;
			acc = b.Balance(accNo);
			cout << acc << endl;
			break;

		case 3:
			cout << "Deposit" << endl;
			cout << "Enter Account Number: ";
			cin >> accNo;
			cout << "Enter amount to deposit: ";
			cin >> amount;
			acc = b.Deposit(accNo, amount);
			cout << "Deposited!" << endl;
			cout << acc << endl;
			break;

		case 4:
			cout << "Withdraw" << endl;
			cout << "Enter Account Number: ";
			cin >> accNo;
			cout << "Enter amount to withdraw: ";
			cin >> amount;
			acc = b.Deposit(accNo, amount);
			cout << "Withdrawn!" << endl;
			cout << acc << endl;
			break;

		case 5:
			cout << "Close Account: " << endl;
			cout << "Enter Account Number: ";
			cin >> accNo;
			b.closeAccount(accNo);
			cout << endl;
			break;


		case 6:
			cout << "All Accounts: " << endl;
			b.viewAll();
			cout << endl;
			break;
		}

	} while(input != 7);

	return 0;
}


//Account
Account::Account(){
}
Account::Account(string name, double balance){
	this->name = name;
	this->balance = balance;
	this->AccNo = ++nextAccNo;
}

void Account::setLastAccNo(int AccNo){
	nextAccNo = AccNo;
}

int Account::getLastAccNo(){
	return nextAccNo;
}

ofstream & operator<<(ofstream &ofs, Account &acc){
	ofs << acc.AccNo << endl;
	ofs << acc.name << endl;
	ofs << acc.balance << endl;
	return ofs;
}

ifstream & operator>>(ifstream &ifs, Account &acc){
	ifs >> acc.AccNo;
	ifs >> acc.name;
	ifs >> acc.balance;
	return ifs;
}

ostream & operator<<(ostream & out, Account &acc){
	out << "Name: " << acc.name << endl;
	out << "Balance: " << acc.balance << endl;
	return out;
}

//Bank
Bank::Bank(){
	Account account;
	ifstream infile("accounts.txt");
	if(!(infile.peek() == ifstream::traits_type::eof())){
		while(!infile.eof()){
		infile >> account;
		accounts.insert(pair<int,Account>(account.getAccNo(),account));
		}
		Account::setLastAccNo(account.getAccNo());
	}
	infile.close();
}

Account Bank::Balance(int accNo){
	map<int,Account>::iterator itr = accounts.find(accNo);
	return itr->second;
}

Account Bank::OpenAccount(string name, double balance){
	Account account(name, balance);
	accounts.insert(pair<int,Account>(account.getAccNo(), account));

	ofstream ofs("accounts.txt", ios::trunc);
	map<int,Account>::iterator itr;
	for(itr = accounts.begin(); itr != accounts.end(); itr++){
		ofs << itr->second;
	}
	ofs.close();
	return account;
}

Account Bank::Deposit(int accNo, double balance){
	map<int,Account>::iterator itr = accounts.find(accNo);
	itr->second.Deposit(balance);
	return itr->second;
}

Account Bank::Withdraw(int accNo, double amount){
	map<int, Account>::iterator itr = accounts.find(accNo);
	itr->second.Withdraw(amount);
	return itr->second;
}

void Bank::closeAccount(int accNo){
	map<int, Account>::iterator itr = accounts.find(accNo);
	accounts.erase(itr);
	cout << "Account successfully closed" << endl;
}

void Bank::viewAll(){
	map<int, Account>::iterator itr;
	for(itr = accounts.begin(); itr != accounts.end(); itr++){
		cout << "Account No. " << itr->first << endl;
		cout << itr->second << endl;
	}
}

Bank::~Bank(){
	ofstream ofs("accounts.txt", ios::trunc);
	map<int,Account>::iterator itr;
	for(itr = accounts.begin(); itr != accounts.end(); itr++){
		ofs << itr->second;
	}
	ofs.close();
}
