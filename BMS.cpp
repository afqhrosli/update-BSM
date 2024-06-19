#include<iostream>
#include<mysql.h>
#include<sstream>
#include<string>
#include<conio.h>
#include<iomanip>
#include <cstdlib>
#include<windows.h>
#include <algorithm>
#include <vector>

using namespace std;

int qstate;
MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;
string items[20000000];
string CustID, StaffID, BookID, Date, name, userID; //primary key

class db_response
{
public:
	static void ConnectionFunction()
	{
		conn = mysql_init(0);
		if (conn)
		{
			cout << "Database Connected" << endl;
			system("cls");
		}
		else
			cout << "Failed to Connect" << mysql_errno(conn) << endl;
		conn = mysql_real_connect(conn, "localhost", "root", "", "bsm_db", 3306, NULL, 0);
		if (conn)
		{
			cout << "Database connected to MYSQL" << conn << endl;
			system("pause");
		}
		else
			cout << "Failed to connect" << mysql_errno(conn) << endl;
	}
};

void Login();
void Loginmember();
void AdminMenu();
void Regcashier();
void memberMenu(string userID);
void ListcashierAdmin();
void Addbook();
void DelBook();
void UpdateBook();
void ViewBook();
bool SearchBook();
void DisplayReport();

void Regmember();
void Addpurchase(string userID);
void Viewpurchase(string userID);
void Updatepurchase(string userID);
void Delpurchase(string userID);
void payment(string userID);


void clearConsole() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif 

}

int main()
{

	system("title Bookshop ");
	db_response::ConnectionFunction();
	system("cls");

	int menu;
	while (true) {
		cout << setw(200) << " " << endl;
		cout << setw(99) << "******************************************************************************" << endl;
		cout << setw(99) << "*                                                                            *" << endl;
		cout << setw(99) << "*                     WELCOME TO BOOKSHOP MANAGEMENT SYSTEM                  *" << endl;
		cout << setw(99) << "*                                                                            *" << endl;
		cout << setw(99) << "******************************************************************************" << endl << endl << endl;
		cout << setw(60) << "1. Login Admin/Cashier\n\n";
		cout << setw(53) << "2. Login Member\n\n";
		cout << setw(56) << "3. Register Member\n\n"; // betulkan
		cout << setw(46) << "4. Exit\n\n\n";
		cout << setw(50) << "Please Enter Your Choice : ";
		cin >> menu;

		switch (menu)
		{
		case 1:
			Login();
			break;
		case 2:
			Loginmember();
			break;
		case 3:
			Regmember();
			break;
		case 4:
			exit(0); //kne tgk balik
		default:
			system("cls");
			system("pause");
			cout << "Please Enter a Valid Input!\n\n";
			
		}
	}


	return 0;
}

string getPhoneNumber() {
	string phone;
	while (true) {
		cout << " " << setw(45) << "Enter phone number: ";
		cin >> phone;
		if (phone.length() >= 10 && phone.length() <= 11 && all_of(phone.begin(), phone.end(), ::isdigit)) break;
		cout << " " << setw(45) << "Invalid input. Please enter a 10-digit number." << endl;
		cin.clear();
		cin.ignore();
	}
	return phone;
}

void Login()
{
	system("cls");

	string username;
	string password;
	string role;
	cout << setw(200) << " " << endl;
	cout << setw(90) << "***********************************************" << endl;
	cout << setw(90) << "*           LOGIN ADMIN/CASHIER PANEL         *" << endl;
	cout << setw(90) << "***********************************************" << endl << endl << endl;
	cout << setw(70) << "Please Enter Your Login Credentials...";
	cout << "\n\n\n" << setw(45) << "Username : ";
	cin >> username;
	// Validate username input
	if (username.empty())
	{
		cout << "Invalid username! Please try again." << endl;
		Login(); // Repeat the function to allow re-entering the username
		return;
	}

	cout << "\n\n" << setw(45) << "Password : ";
	char ch;
	while ((ch = _getch()) != 13)
	{
		password += ch;
		cout << '*';
	}

	// Validate password input
	if (password.empty())
	{
		cout << endl << "Invalid password! Please try again." << endl;
		Login(); // Repeat the function to allow re-entering the password
		return;
	}

	string checkUser_query = "SELECT role,name FROM user WHERE username = '" + username + "' AND password = '" + password + "'";
	const char* cu = checkUser_query.c_str();
	qstate = mysql_query(conn, cu);

	if (!qstate) {
		res = mysql_store_result(conn);
		if (res) {
			if (mysql_num_rows(res) == 1) {
				row = mysql_fetch_row(res);
				role = row[0]; // Assuming Level is stored as a string in the database
				name = row[1];
				cout << "\n\n\t\tLogged in successfully." << endl;
				if (role == "1") {
					cout << "\n\n\t\tRole 1: Admin" << endl;
					AdminMenu();
					// Provide functionalities for an admin user.
				}
				else if (role == "2") {
					cout << "\n\n\t\tRole 2: Member" << endl;
					memberMenu(username);
					// Provide functionalities for an admin user.

			    }
				else if (role == "3") {
					cout << "\n\n\t\tRole 3: cashier" << endl;
					//memberMenu();
					// Provide functionalities for a cashier user.
				}
			}
			else {
				cout << endl << "\n\n\t\tInvalid username or password. Want to try again? (y/n): ";
				char c;
				cin >> c;
				if (c == 'y' || c == 'Y')
					Login();
				else
					cout << "\n\n\t\tLogin failed!" << endl;
			}
		}
	}
	else {
		cout << "\n\n\t\tQuery Execution Problem: " << mysql_error(conn) << endl;
	}
}

void Loginmember()
{
	system("cls");

	string username;
	string password;
	string role;
	cout << setw(200) << " " << endl;
	cout << setw(90) << "***********************************************" << endl;
	cout << setw(90) << "*                 LOGIN MEMBER PANEL          *" << endl;
	cout << setw(90) << "***********************************************" << endl << endl << endl;
	cout << setw(70) << "Please Enter Your Login Credentials...";
	cout << "\n\n\n" << setw(45) << "Username : ";
	cin >> username;
	// Validate username input
	if (username.empty())
	{
		cout << "Invalid username! Please try again." << endl;
		Login(); // Repeat the function to allow re-entering the username
		return;
	}

	cout << "\n\n" << setw(45) << "Password : ";
	char ch;
	while ((ch = _getch()) != 13)
	{
		password += ch;
		cout << '*';
	}

	// Validate password input
	if (password.empty())
	{
		cout << endl << "Invalid password! Please try again." << endl;
		Login(); // Repeat the function to allow re-entering the password
		return;
	}

	string checkUser_query = "SELECT role,name,userID FROM user WHERE username = '" + username + "' AND password = '" + password + "'";
	const char* cu = checkUser_query.c_str();
	qstate = mysql_query(conn, cu);

	if (!qstate) {
		res = mysql_store_result(conn);
		if (res) {
			if (mysql_num_rows(res) == 1) {
				row = mysql_fetch_row(res);
				role = row[0];// Assuming Level is stored as a string in the database
				name = row[1];
				userID = row[2];

				cout << "\n\n\t\tLogged in successfully." << endl;
				if (role == "1") {
					cout << "\n\n\t\tRole 1: Admin" << endl;
					AdminMenu();
					// Provide functionalities for an admin user.
				}
				else if (role == "2") {
					cout << "\n\n\t\tRole 2: member" << endl;
					memberMenu(userID);
					// Provide functionalities for a member user.
				}
				else if (role == "3") {
					cout << "\n\n\t\tRole 3: cashier" << endl;
					//CashierMenu();
					// Provide functionalities for a cashier user.
				}
			}
			else {
				cout << endl << "\n\n\t\tInvalid username or password. Want to try again? (y/n): ";
				char c;
				cin >> c;
				if (c == 'y' || c == 'Y')
					Login();
				else
					cout << "\n\n\t\tLogin failed!" << endl;
			}
		}
	}
	else {
		cout << "\n\n\t\tQuery Execution Problem: " << mysql_error(conn) << endl;
	}
}


void AdminMenu()
{

	system("cls");


	int menu;
	cout << setw(200) << " " << endl;
	cout << setw(99) << "******************************************************************************" << endl;
	cout << setw(99) << "*                                                                            *" << endl;
	cout << setw(99) << "*                              MAIN MENU - ADMIN                             *" << endl;
	cout << setw(99) << "*                                                                            *" << endl;
	cout << setw(99) << "******************************************************************************" << endl;
	cout << "\n\n\t\tLogged in as : " << name << endl << endl;
	cout << setw(55) << "1. Manage Cashier\n\n";
	cout << setw(53) << "2. Manage Books\n\n";
	cout << setw(60) << "3. Manage Report Sales\n\n";
	cout << setw(48) << "4. Logout\n\n\n";
	cout << setw(50) << "Please Enter Your Choice : ";
	cin >> menu;

	switch (menu)
	{
	case 1:

		int choose;
		system("cls");

		cout << setw(300) << " " << endl;
		cout << setw(99) << "******************************************************************************" << endl;
		cout << setw(99) << "*                                                                            *" << endl;
		cout << setw(99) << "*                              MENU - CASHIER                                *" << endl;
		cout << setw(99) << "*                                                                            *" << endl;
		cout << setw(99) << "******************************************************************************" << "\n\n" << endl;
		cout << setw(60) << "***** INFORMATION *****\n\n" << endl;
		cout << setw(60) << "** ROLE FOR CASHIER IS 3 **\n\n" << endl;
		cout << setw(57) << "1. Register Cashier\n\n";
		cout << setw(50) << "2. View User\n\n";
		cout << setw(46) << "3. Back\n\n\n";
		cout << setw(50) << "Please Enter Your Choice : ";
	
		cin >> choose;

		if (choose == 1)
		{
			Regcashier();
		}
		else if (choose == 2)
		{
			ListcashierAdmin();

		}
		else if (choose == 3)
		{
			AdminMenu();
		}

		break;

	case 2:
		system("cls");

		cout << setw(200) << " " << endl;
		cout << setw(99) << "******************************************************************************" << endl;
		cout << setw(99) << "*                                                                            *" << endl;
		cout << setw(99) << "*                              MENU - MANAGE BOOK                            *" << endl;
		cout << setw(99) << "*                                                                            *" << endl;
		cout << setw(99) << "******************************************************************************" << "\n\n" << endl;
		cout << setw(57) << "1. Search book\n\n";
		cout << setw(54) << "2. Add book\n\n";
		cout << setw(57) << "3. Update book\n\n";
		cout << setw(57) << "4. Delete book\n\n";
		cout << setw(58) << "5. Display book\n\n";
		cout << setw(51) << "6. Back\n\n\n";
		cout << setw(50) << "Please Enter Your Choice : ";
		cin >> choose;

		if (choose == 1)
		{
			SearchBook();
		}
		if (choose == 2)
		{
			Addbook();
		}
		if (choose == 3)
		{
			UpdateBook();
		}
		if (choose == 4)
		{
			DelBook();
		}
		if (choose == 5)
		{
			ViewBook();
		}
		else if (choose == 6)
		{
			AdminMenu();
		}

		break;

	case 3:
		system("cls");

		cout << setw(200) << " " << endl;
		cout << setw(99) << "******************************************************************************" << endl;
		cout << setw(99) << "*                                                                            *" << endl;
		cout << setw(99) << "*                              MENU - REPORT SALE                            *" << endl;
		cout << setw(99) << "*                                                                            *" << endl;
		cout << setw(99) << "******************************************************************************" << "\n\n" << endl;
		cout << setw(57) << "1. Display Report\n\n";
		cout << setw(48) << "2. Back\n\n\n";
		cout << setw(50) << "Please Enter Your Choice : ";
		cin >> choose;

		if (choose == 1)
		{
			DisplayReport();
		}
		else if (choose == 2)
		{
			AdminMenu();
		}

		break;
	case 4:
		main();

	}

}

void Regcashier() //done
{
	system("cls");

	char option;
	string username = "";
	string password = "";
	string name = "";
	string age = "";
	string gender = "";
	string phoneNum = "";
	string email = "";
	string employmentStartDate = "";
	string role = "";
	int count = 0;
	int specials = 0;
	bool valid_password = true;

	
	cout << setw(200) << " " << endl;
	cout << setw(99) << "******************************************************************************" << endl;
	cout << setw(99) << "*                                                                            *" << endl;
	cout << setw(99) << "*                            MENU - NEW STAFF REGISTRATION                   *" << endl;
	cout << setw(99) << "*                                                                            *" << endl;
	cout << setw(99) << "******************************************************************************" << "\n" << endl;

	cout << "\n" << setw(45) << "Enter Username: ";
	cin.ignore(1, '\n');
	getline(cin, username);

	string checkuser_query = "select * from user where username = '" + username + "'";
	const char* cu = checkuser_query.c_str();
	qstate = mysql_query(conn, cu);

	if (!qstate)
	{
		res = mysql_store_result(conn);
		if (res->row_count == 1)
		{
			cout << "Username already exists. Press Enter to Try Again...";
			cin.ignore();
			Regcashier();
		}
		else
		{
			cout << "\n" << setw(85) << "- A password must have at least eight characters. " << endl;
			cout << " " << setw(87) << "- A password must consist of only letters and digits." << endl;
			cout << " " << setw(80) << "- A password must contain at least two digits." << endl;
			cout << " " << setw(45) << "Enter Password: ";
			char ch;
			while ((ch = _getch()) != 13)
			{
				password += ch;
				cout << '*';
			}
			for (int i = 0; i < password.length(); i++)
			{
				if (!isalnum(password[i]))
				{
					specials++;
				}
			}

			for (int j = 0; j < password.length(); j++) {
				if (isdigit(password[j]))
				{
					count++;
				}
			}

			if (count < 2 || (password.length() < 8) || (specials != 0)) {
				valid_password = false;
			}

			if (valid_password) {
				cout << "\n" << setw(46) << "Password valid";
			}
			else
			{
				cout << "\n" << setw(45) << "Invalid password. Please try again.";
				Regcashier(); // Restart the registration process if the password is invalid
				return;
			}

			cin.ignore(1, '\n');
			cout << " " << setw(45) << "Enter Name: ";
			getline(cin, name);
			cout << " " << setw(45) << "Enter Age: ";
			getline(cin, age);
			cout << " " << setw(45) << "Enter Gender: ";
			getline(cin, gender);
			cout << " " << setw(45) << "Enter Phone Number: ";
			getline(cin, phoneNum);
			cout << " " << setw(45) << "Enter Email: ";
			getline(cin, email);
			cout << " " << setw(45) << "Enter Start Date: ";
			getline(cin, employmentStartDate);
			cout << " " << setw(45) << "Enter Role: ";
			getline(cin, role);


			// Getting current date
			time_t now;
			struct tm ltm;
			time(&now);

#ifdef _WIN32
			localtime_s(&ltm, &now);
#else
			localtime_r(&now, &ltm);
#endif
			int currYear = 1900 + ltm.tm_year;
			int currMonth = 1 + ltm.tm_mon;
			int currDay = ltm.tm_mday;

			employmentStartDate = to_string(currYear) + "/" + to_string(currMonth) + "/" + to_string(currDay); // Get the current date




			string insertuser_query = "insert into user (username, password, name, age, gender, phoneNum, email, employmentStartDate, role) VALUES ('" + username + "', '" + password + "', '" + name + "', '" + age + "','" + gender + "','" + phoneNum + "','" + email + "','" + employmentStartDate + "','" + role + "')";
			const char* qu = insertuser_query.c_str();
			qstate = mysql_query(conn, qu);

			if (!qstate)
			{
				cout << "\n\n\n" << setw(80) << "You have been registered.\n\n";
				cout << setw(80) << "Do you want to add other staff? (y/n): ";
				cin >> option;

				if (option == 'y' || option == 'Y')
					Regcashier();
				else
					ListcashierAdmin();
				cin.ignore();
			}
			else
			{
				cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
			}
		}
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
}

void ListcashierAdmin()//done
{
	system("cls");

	cout << setw(280) << " " << endl;
	cout << setw(99) << "******************************************************************************" << endl;
	cout << setw(99) << "*                                                                            *" << endl;
	cout << setw(99) << "*                                  USER LIST                                 *" << endl;
	cout << setw(99) << "*                                                                            *" << endl;
	cout << setw(99) << "******************************************************************************" << "\n" << endl;
	qstate = mysql_query(conn, "SELECT * FROM user ");
	if (!qstate)
	{
		res = mysql_store_result(conn);

		cout << "\n";
		cout << setw(120) << "---------------------------------------------------------------------------------------------\n";
		//data show in box
		cout << setw(25) << "";
		printf("| %-3s | %-20s |%-7s | %-10s | %-20s | %-13s | %-5s|\n", "ID", "Name", "gender", "phoneNum", "Email", "employmentStartDate", "Level"); //database kne tukar
		cout << setw(120) << "---------------------------------------------------------------------------------------------\n";

		while ((row = mysql_fetch_row(res)))
		{


			cout << setw(25) << "";
			printf("| %-3s | %-20s |%-7s | %-10s | %-20s | %-13s | %-5s|\n", row[0], row[3], row[5], row[6], row[7], row[8], row[9]); //- still ada tukar no
			cout << setw(120) << "---------------------------------------------------------------------------------------------\n";
		}


	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
	cout << "Press Enter To Back....";
	_getch();
	AdminMenu();
}

void Addbook() //done
{

	system("cls");

	string title; // database
	string author;
	string genre;
	string publisher;
	string priceBook, quantityOfStock;
	char choose;

	cout << setw(200) << " " << endl;
	cout << setw(99) << "******************************************************************************" << endl;
	cout << setw(99) << "*                                                                            *" << endl;
	cout << setw(99) << "*                                     ADD BOOK                               *" << endl;
	cout << setw(99) << "*                                                                            *" << endl;
	cout << setw(99) << "******************************************************************************" << "\n" << endl;


	cout << setw(45) << "Enter Book Title: ";
	cin.ignore(1, '\n');
	getline(cin, title);

	string checkBook_query = "select * from book where title = '" + title + "'";
	const char* cu = checkBook_query.c_str();
	qstate = mysql_query(conn, cu);

	if (!qstate)
	{
		res = mysql_store_result(conn);
		if (res->row_count == 1)
		{
			cout << "Book is already exist. Press Enter to Try Again...";
			cin.ignore();
			Addbook();
		}
		else
		{
			cout << setw(45) << "Enter Book Author: ";
			getline(cin, author);
			cout << setw(45) << "Enter Book Genre: ";
			getline(cin, genre);
			cout << setw(47) << "Enter Publisher: ";
			getline(cin, publisher);
			cout << setw(47) << "Enter Book Price:RM ";
			getline(cin, priceBook);
			cout << setw(45) << "Enter Book Stock: ";
			getline(cin, quantityOfStock);
			

			string insert_query2 = "INSERT INTO book(title,author,genre,publisher,priceBook,quantityOfStock) VALUES ('" + title + "', '" + author + "', '" + genre + "', '" + publisher + "', '" + priceBook + "', '" + quantityOfStock + "')";
			const char* q = insert_query2.c_str();
			qstate = mysql_query(conn, q);

			if (!qstate)
			{
				cout << endl << setw(50) << "Book Successfully added \n\n " << endl;
				_getch();

			}
			else
			{
				cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
			}

			do
			{
				cout << setw(60) << "Do you want to add another book ?(y/n): ";
				cin >> choose;
				if (choose == 'y' || choose == 'Y')
				{
					Addbook();
				}
				else if (choose == 'n' || choose == 'N')
				{
					ViewBook();
				}
			} while (choose == 'y' || choose == 'Y' || choose == 'n' || choose == 'Y');
		}
	}
}

void UpdateBook()//done
{
	system("cls");
	string title = ""; // database
	string author = "";
	string genre = "";
	string publisher = "";
	string priceBook = "";
	string quantityOfStock = "";
	string items[5000];
	char choose;
	int indexForId = 0;
	int bookID = 0;
	bool HaveExcept = false;
	bool NotInDatabase = false;

	string storeid = "";
	string storebooktitle = "";
	string storebookauthor = "";
	string storebookgenre = "";
	string storebookpublisher = "";
	string storebookpriceBook = "";
	string storebookquantityOfStock = "";


	cout << setw(200) << " " << endl;
	cout << setw(99) << "******************************************************************************" << endl;
	cout << setw(99) << "*                                                                            *" << endl;
	cout << setw(99) << "*                                UPDATE BOOK                                 *" << endl;
	cout << setw(99) << "*                                                                            *" << endl;
	cout << setw(99) << "******************************************************************************" << "\n" << endl;

	qstate = mysql_query(conn, "SELECT * FROM book");
	if (!qstate)
	{
		res = mysql_store_result(conn);
		cout << endl << "----------------------------------------\n";
		while ((row = mysql_fetch_row(res)))
		{

			cout << "ID: " << row[0] << endl;
			cout << "Book Title: " << row[1] << endl;
			cout << "Book Author: " << row[2] << endl;
			cout << "Book Genre: " << row[3] << endl;
			cout << "Book Publisher: " << row[4] << endl;
			cout << "Book Price:RM" << row[5] << endl;
			cout << "Book Stock: " << row[6] << endl;
			cout << endl << "----------------------------------------\n";

		}

	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
	try
	{
		cout << endl;
		cout << "Enter Book ID: ";
		cin >> bookID;
		cout << endl;
	}
	catch (exception e)
	{
		cout << "Please enter a valid number" << endl;
		HaveExcept = true;
		//goto exit;
	}
	if (HaveExcept == false)
	{
		stringstream streamid;
		string strID;
		streamid << bookID;
		streamid >> strID;

		for (int i = 0; i < indexForId; i++)
		{
			if (strID != items[i])
			{
				NotInDatabase = true;
			}
			else
			{
				NotInDatabase = false;
				break;
			}
		}
		if (NotInDatabase == false)
		{
			string findbyid_query = "SELECT * FROM book where bookID='" + strID + "'";
			const char* qi = findbyid_query.c_str();
			qstate = mysql_query(conn, qi);

			if (!qstate)
			{
				res = mysql_store_result(conn);
				cout << endl;
				while ((row = mysql_fetch_row(res)))
				{
					system("cls");
					cout << setw(200) << " " << endl;
					cout << setw(99) << "******************************************************************************" << endl;
					cout << setw(99) << "*                                                                            *" << endl;
					cout << setw(99) << "*                                  UPDATE BOOK                               *" << endl;
					cout << setw(99) << "*                                                                            *" << endl;
					cout << setw(99) << "******************************************************************************" << "\n" << endl;

					cout << "\nBOOK ID:" << row[0];
					cout << "\nBOOK TITLE:" << row[1];
					cout << "\nBOOK AUTHOR:" << row[2];
					cout << "\nBOOK GENRE:" << row[3];
					cout << "\nBOOK PUBLISHER:" << row[4];
					cout << "\nBOOK PRICE:RM" << row[5];
					cout << "\nBOOK STOCK:" << row[6];
					cout << endl << endl;
					storeid = row[0];
					storebooktitle = row[1];
					string storebookauthor = row[2];
					string storebookgenre = row[3];
					string storebookpublisher = row[4];
					string storebookpriceBook = row[5];
					string storebookquantityOfStock = row[6];
				}
			}
			else
			{
				cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
				system("pause");
			}

			string data;
			int choose;

			cout << setw(200) << " " << endl;
			cout << setw(99) << "******************************************************************************" << endl;
			cout << setw(99) << "*                                 CATEGORY                                   *" << endl;
			cout << setw(99) << "******************************************************************************" << "\n" << endl;
			cout << setw(52) << "1. Book Title \n\n";
			cout << setw(52) << "2. Book Author\n\n";
			cout << setw(51) << "3. Book Genre\n\n";
			cout << setw(55) << "4. Book Publisher\n\n";
			cout << setw(51) << "5. Book Price\n\n";
			cout << setw(51) << "6. Book Stock\n\n";
			cout << setw(50) << "Please Enter Your Choice : ";
			cin >> choose;

			cin.ignore(1, '\n');
			if (choose == 1)
			{
				cout << endl << endl << setw(45) << "1. New Book Title : ";
				getline(cin, data);
				string update_query = "update book set title='" + data + "' where bookID='" + strID + "'";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
			}
			else if (choose == 2)
			{
				cout << endl << endl << setw(45) << "2. New Book Author: ";
				getline(cin, data);
				string update_query = "update book set author='" + data + "' where bookID='" + strID + "'";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
			}
			else if (choose == 3)
			{
				cout << endl << endl << setw(45) << "3. New Book Genre: ";
				getline(cin, data);
				string update_query = "update book set genre='" + data + "' where bookID='" + strID + "'";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
			}
			else if (choose == 4)
			{
				cout << endl << endl << setw(45) << "4. New Book Publisher: ";
				getline(cin, data);
				string update_query = "update book set publisher='" + data + "' where bookID='" + strID + "'";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
			}
			else if (choose == 5)
			{
				cout << endl << endl << setw(45) << "5. New Book Price:RM ";
				getline(cin, data);
				string update_query = "update book set priceBook ='" + data + "' where bookID='" + strID + "'";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
			}
			else  if (choose == 6)
			{
				cout << endl << endl << setw(45) << "6. New Book Stock: ";
				getline(cin, data);
				string update_query = "update book set quantityOfStock='" + data + "' where bookID='" + strID + "'";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
			}
			

		}
		else
		{
			cout << "Not Found in Database" << endl;
		}

		cout << endl << "Do you want to update another book? (y||n): ";
		cin >> choose;
		if (choose == 'y' || choose == 'Y')
		{
			UpdateBook();
		}
		else
		{
			system("cls");
			ViewBook();
		}
	}
}

void DelBook()//done
{
	system("cls");

	char choose;
	string id;
	cout << setw(200) << " " << endl;
	cout << setw(99) << "******************************************************************************" << endl;
	cout << setw(99) << "*                                                                            *" << endl;
	cout << setw(99) << "*                                 DELETE BOOK                                *" << endl;
	cout << setw(99) << "*                                                                            *" << endl;
	cout << setw(99) << "******************************************************************************" << "\n" << endl;
	qstate = mysql_query(conn, "SELECT * FROM book"); //book-nama drpd database
	if (!qstate)
	{
		res = mysql_store_result(conn);
		cout << endl << "--------------------------------------------------\n";
		while ((row = mysql_fetch_row(res)))
		{

			cout << "ID: " << row[0] << endl;
			cout << "Book Title: " << row[1] << endl;
			cout << "Book Author: " << row[2] << endl;
			cout << "Book Genre: " << row[3] << endl;
			cout << "Book Publisher: " << row[4] << endl;
			cout << "Book Price:RM" << row[5] << endl;
			cout << "Book STOCK: " << row[6] << endl;
			cout << endl << "----------------------------------------\n";

		}


	}
	cout << setw(45) << "Enter book ID to delete: ";
	cin >> id; //ikut database

	bool found = false;

	string query = "select bookID from book";
	const char* qd = query.c_str();
	qstate = mysql_query(conn, qd);
	res = mysql_store_result(conn);

	if (!qstate)
	{
		while ((row = mysql_fetch_row(res)))
		{
			if (row[0] == id)
			{
				found = true;
				break;
			}
		}
	}
	if (found)
	{
		query = "delete from book where bookID='" + id + "'";
		qd = query.c_str();
		qstate = mysql_query(conn, qd);

		if (!qstate)
		{
			cout << endl << setw(50) << "Successfully deleted from book record" << endl;
		}
		else
		{
			cout << setw(50) << "Failed to delete" << endl;
		}
	}
	else
	{

		cout << endl << setw(50) << "Please Enter a valid ID.Do You Want To Try Again? (y|n): ";
		cin >> choose;
		if (choose == 'y' || choose == 'Y')
		{
			DelBook();
		}
		else
		{
			system("cls");
			AdminMenu();
		}

	}

	cout << endl << setw(50) << "Do you want to Delete another book? (y||n): ";
	cin >> choose;

	if (choose == 'y' || choose == 'Y')
	{
		DelBook();
	}
	else
	{
		system("cls");
		AdminMenu();
	}
}

void ViewBook()//done
{
	system("cls");

	cout << setw(200) << " " << endl;
	cout << setw(99) << "******************************************************************************" << endl;
	cout << setw(99) << "*                                                                            *" << endl;
	cout << setw(99) << "*                               BOOK LIST                                    *" << endl;
	cout << setw(99) << "*                                                                            *" << endl;
	cout << setw(99) << "******************************************************************************" << "\n" << endl;

	qstate = mysql_query(conn, "SELECT * FROM book");
	if (!qstate)
	{
		res = mysql_store_result(conn);
		cout << endl << "--------------------------------------------------\n";
		while ((row = mysql_fetch_row(res)))
		{

			cout << "ID: " << row[0] << endl;
			cout << "Book Title: " << row[1] << endl;
			cout << "Book Author: " << row[2] << endl;
			cout << "Book Genre: " << row[3] << endl;
			cout << "Book Publisher: " << row[4] << endl;
			cout << "Book Price:RM" << row[5] << endl;
			cout << "Book STOCK: " << row[6] << endl;
			cout << endl << "----------------------------------------\n";

		}

	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
	cout << "Press Enter to continue" << endl;
	_getch();
	AdminMenu();
}

bool SearchBook()//done
{
	system("cls");
	char choose;
	string title;

	cout << setw(200) << " " << endl;
	cout << setw(99) << "******************************************************************************" << endl;
	cout << setw(99) << "*                                                                            *" << endl;
	cout << setw(99) << "*                                   SEARCH BOOK                              *" << endl;
	cout << setw(99) << "*                                                                            *" << endl;
	cout << setw(99) << "******************************************************************************" << "\n" << endl;

	cin.ignore(1, '\n');
	cout << setw(45) << "Search Book by title: ";
	getline(cin, title);

	string search_query = "select * from book where title LIKE '%" + title + "%'"; //LIKE -type 1 2 hurugf akan display
	const char* q = search_query.c_str();
	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		res = mysql_store_result(conn);
		if (res->row_count == 0) {
			cout << "\n No result found\n";
			cout << "\n-----------------------------------------------\n";
		}
		else {
			cout << "\n";
			while ((row = mysql_fetch_row(res)))
			{
				cout << endl << "-------------------------------------------\n";
				cout << "ID: " << row[0] << endl;
				cout << "Book Title: " << row[1] << endl;
				cout << "Book Author: " << row[2] << endl;
				cout << "Book Genre: " << row[3] << endl;
				cout << "Book Publisher: " << row[4] << endl;
				cout << "Book Price:RM" << row[5] << endl;
				cout << "Book STOCK: " << row[6] << endl;
				cout << endl << "-------------------------------------------\n";
			}
		}
		cout << endl << setw(50) << "Do you want to search other Book? (y/n): ";
		cin >> choose;

		if (choose == 'y' || choose == 'Y')
			return SearchBook();
		else if (choose == 'n' || choose == 'N')
			AdminMenu();
	}
	else
	{
		cout << "Query Execution Problem! Error Code: " << mysql_errno(conn) << endl;
		return false;
	}
	return true;
}

void DisplayReport() {
	// Clear screen
	system("cls");

	cout << setw(200) << " " << endl;
	cout << setw(99) << "******************************************************************************" << endl;
	cout << setw(99) << "*                                                                            *" << endl;
	cout << setw(99) << "*                                 SALES REPORT                               *" << endl;
	cout << setw(99) << "*                                                                            *" << endl;
	cout << setw(99) << "******************************************************************************" << "\n" << endl;

	string query = "SELECT * FROM `payment`";
	qstate = mysql_query(conn, query.c_str());
	double totalSales = 0.0;

	if (!qstate) {
		res = mysql_store_result(conn);

		cout << "\n";
		cout << setw(108) << "----------------------------------------------------------------------------------------\n";
		// data show in box
		cout << setw(19) << "";
		printf("| %-10s | %-10s | %-25s | %-15s |\n", "Payment ID", "User ID", "Bill Date", "Amount (RM)");
		cout << setw(108) << "----------------------------------------------------------------------------------------\n";

		while ((row = mysql_fetch_row(res))) {
			double amount = stod(row[3] ? row[3] : "0");
			totalSales += amount;

			cout << setw(19) << "";
			printf("| %-10s | %-10s | %-25s | %-15.2f |\n", row[0], row[1], row[2], amount);
			cout << setw(108) << "----------------------------------------------------------------------------------------\n";
		}

		cout << "\nTotal Sales Overall: RM " << totalSales << endl;

		// Query to get the user with the most payments
		string userQuery = "SELECT userID, COUNT(*) as payments FROM `payment` GROUP BY userID ORDER BY payments DESC LIMIT 1";
		qstate = mysql_query(conn, userQuery.c_str());

		if (!qstate) {
			res = mysql_store_result(conn);
			if ((row = mysql_fetch_row(res))) {
				string topUserID = row[0];
				string topUserPayments = row[1];

				// Get user name
				string userNameQuery = "SELECT name FROM `user` WHERE userID = '" + topUserID + "'";
				qstate = mysql_query(conn, userNameQuery.c_str());

				if (!qstate) {
					res = mysql_store_result(conn);
					if ((row = mysql_fetch_row(res))) {
						string userName = row[0];
						cout << "User with the most payments: " << topUserID << " (" << userName << ") with " << topUserPayments << " payments." << endl;
					}
				}
			}
		}

		// Query to get the book with the most sales
		string bookQuery = "SELECT bookID, SUM(quantity) as totalQuantity FROM `order` GROUP BY bookID ORDER BY totalQuantity DESC LIMIT 1";
		qstate = mysql_query(conn, bookQuery.c_str());

		if (!qstate) {
			res = mysql_store_result(conn);
			if ((row = mysql_fetch_row(res))) {
				string topBookID = row[0];
				string topBookSales = row[1];

				// Get book name
				string bookNameQuery = "SELECT title FROM `book` WHERE bookID = '" + topBookID + "'";
				qstate = mysql_query(conn, bookNameQuery.c_str());

				if (!qstate) {
					res = mysql_store_result(conn);
					if ((row = mysql_fetch_row(res))) {
						string bookName = row[0];
						cout << "Book with the most sales: " << topBookID << " (" << bookName << ") with " << topBookSales << " sales." << endl;
					}
				}
			}
		}

		// Pause after displaying the report
		cout << "\nPress any key to continue...";
		cin.ignore();
		cin.get();

		AdminMenu();
	}
	else {
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
}

void Regmember() // done

{
	system("cls");

	char option;
	string username = "";
	string password = "";
	string fullname = "";
	string email = "";
	string address = "";
	string phoneNum = "";
	string gender = "";
	string role = "";
	int count = 0;
	int specials = 0;
	bool valid_password = true;

	cout << setw(200) << " " << endl;
	cout << setw(99) << "******************************************************************************" << endl;
	cout << setw(99) << "*                                                                            *" << endl;
	cout << setw(99) << "*                            MENU - NEW MEMBER REGISTRATION                  *" << endl;
	cout << setw(99) << "*                                                                            *" << endl;
	cout << setw(99) << "******************************************************************************" << "\n" << endl;

	cout << "\n" << setw(45) << "Enter Username: ";
	cin.ignore(); // Clear input buffer
	getline(cin, username);

	string checkmember_query = "select * from member where username = '" + username + "'";
	const char* cu = checkmember_query.c_str();
	qstate = mysql_query(conn, cu);

	if (!qstate)
	{
		res = mysql_store_result(conn);
		if (res->row_count == 1)
		{
			cout << "Username already exists. Press Enter to Try Again...";
			cin.ignore();
			Regmember(); // Retry registration process
		}
		else
		{
			cout << "\n" << setw(85) << "- A password must have at least eight characters. " << endl;
			cout << " " << setw(87) << "- A password must consist of only letters and digits." << endl;
			cout << " " << setw(80) << "- A password must contain at least two digits." << endl;
			cout << " " << setw(45) << "Enter Password: ";
			char ch;
			while ((ch = _getch()) != 13)
			{
				password += ch;
				cout << '*';
			}

			for (int i = 0; i < password.length(); i++)
			{
				if (!isalnum(password[i]))
				{
					specials++;
				}
			}

			for (int j = 0; j < password.length(); j++) {
				if (isdigit(password[j]))
				{
					count++;
				}
			}

			if (count < 2 || (password.length() < 8) || (specials != 0)) {
				valid_password = false;
			}

			if (valid_password) {
				cout << "\n" << setw(46) << "Password valid";
			}
			else
			{
				cout << "\n" << setw(45) << "Invalid password. Please try again.";
				Regmember(); // Restart the registration process if the password is invalid
				return;
			}

			cin.ignore(); // Clear input buffer
			cout << " " << setw(45) << "Enter Name: ";
			getline(cin, fullname);

			cout << " " << setw(45) << "Enter Email: ";
			getline(cin, email);
			cout << " " << setw(45) << "Enter Address: ";
			getline(cin, address);
			cout << " " << setw(45) << "Enter Phone Number: ";
			getline(cin, phoneNum);
			cout << " " << setw(45) << "Enter Gender: ";
			getline(cin, gender);
			cout << " " << setw(45) << "Enter Role: ";
			getline(cin, role);

			string insertmember_query = "insert into member (username, password, fullname, email, address, phoneNum, gender, role) VALUES ('" + username + "', '" + password + "', '" + fullname + "', '" + email + "','" + address + "','" + phoneNum + "','" + gender + "','" + role + "')";

			const char* qu = insertmember_query.c_str();
			qstate = mysql_query(conn, qu);

			if (!qstate)
			{
				cout << "\n\n\n" << setw(80) << "You have been registered.\n\n";
				cout << setw(80) << "Do you want to add other staff? (y|n): ";
				cin >> option;

				if (option == 'y' || option == 'Y')
					Regmember();
				else
					main();
				cin.ignore();
			}
			else
			{
				cout << "Query Execution Problem! " << mysql_errno(conn) << endl;
			}
		}
	}
	else
	{
		cout << "Query Execution Problem! " << mysql_errno(conn) << endl;
	}
}

void memberMenu(string userID) //not done
{

	system("cls");
	int menu;
	cout << setw(200) << " " << endl;
	cout << setw(99) << "******************************************************************************" << endl;
	cout << setw(99) << "*                                                                            *" << endl;
	cout << setw(99) << "*                              MAIN MENU - MEMBER                            *" << endl;
	cout << setw(99) << "*                                                                            *" << endl;
	cout << setw(99) << "******************************************************************************" << endl;
	cout << "\n\n\t\tLogged in as : " << name << endl << endl;
	cout << setw(57) << "1. Manage Purchases\n\n";
	cout << setw(48) << "2. Payment\n\n";
	cout << setw(48) << "3. Logout\n\n\n";
	cout << setw(50) << "Please Enter Your Choice : ";
	cin >> menu;

	switch (menu)
	{
	case 1:

		system("cls");
		int choose;

		cout << setw(200) << " " << endl;
		cout << setw(99) << "******************************************************************************" << endl;
		cout << setw(99) << "*                                                                            *" << endl;
		cout << setw(99) << "*                              MENU - MANAGE PURCHASE                        *" << endl;
		cout << setw(99) << "*                                                                            *" << endl;
		cout << setw(99) << "******************************************************************************" << "\n\n" << endl;
		cout << setw(56) << "1. Add Purchase\n\n";
		cout << setw(59) << "2. Update Purchase\n\n";
		cout << setw(59) << "3. Delete Purchase\n\n";
		cout << setw(60) << "4. Display Purchase\n\n";
		cout << setw(49) << "5. Back\n\n\n";
		cout << setw(50) << "Please Enter Your Choice : ";
		cin >> choose;

		if (choose == 1)
		{
			Addpurchase(userID);
		}
		if (choose == 2)
		{
			Updatepurchase(userID);
		}
		if (choose == 3)
		{
			Delpurchase(userID);
		}
		if (choose == 4)
		{
			Viewpurchase(userID);
		}
		else if (choose == 5)
		{
			memberMenu(userID);
		}

		break;

	case 2:
		system("cls");
		payment(userID);
		break;

	case 3:
		main();

	}

}

struct CartItem {
	int bookID;
	string title;
	string author;
	string genre;
	float price;
	int quantity;
};

vector<CartItem> cart;

void add_to_cart(int bookID, string title, string author, string genre, float price, int quantity) {
	CartItem item = { bookID, title, author, genre, price, quantity };
	cart.push_back(item);
	cout << "Added to cart: " << title << " (Quantity: " << quantity << ")\n";
}

float calculate_total() {
	float total = 0;
	for (const auto& item : cart) {
		total += item.price * item.quantity;
	}
	return total;
}

void display_cart() {
	if (cart.empty()) {
		cout << "Cart is empty.\n";
		return;
	}
	cout << "Cart items:\n";
	cout << "--------------------------------------------------\n";
	for (const auto& item : cart) {
		cout << "Book ID: " << item.bookID << "\n";
		cout << "Title: " << item.title << "\n";
		cout << "Author: " << item.author << "\n";
		cout << "Genre: " << item.genre << "\n";
		cout << "Price: RM" << item.price << "\n";
		cout << "Quantity: " << item.quantity << "\n";
		cout << "--------------------------------------------------\n";
	}
	cout << "Total Price: RM" << calculate_total() << "\n";
}

void Addpurchase(string userID) //done
{
	int menu();
	// Variable declarations
	string quantity,orderID,orderDate ;
	string title, author, genre, publisher, quantityOfStock ;
	string priceBook,price;

	
	float totalprice;
	char choose;
	int bookID;
	int selectedIndex = 0;

	// Clear screen
	system("cls");

	cout << setw(200) << " " << endl;
	cout << setw(99) << "******************************************************************************" << endl;
	cout << setw(99) << "*                                                                            *" << endl;
	cout << setw(99) << "*                               SEARCH & PURCHASE BOOK                       *" << endl;
	cout << setw(99) << "*                                                                            *" << endl;
	cout << setw(99) << "******************************************************************************" << "\n" << endl;

	// Prompt user to search for a book by title
	cin.ignore(1, '\n');
	cout << setw(45) << "Search Book by title: ";
	getline(cin, title);

	// Query to search for books by title
	string search_query = "SELECT * FROM book WHERE title LIKE '%" + title + "%'";
	const char* q = search_query.c_str();
	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		res = mysql_store_result(conn);
		cout << endl << "--------------------------------------------------\n";
		while ((row = mysql_fetch_row(res)))
		{
			cout << "ID: " << row[0] << endl;
			cout << "Book Title: " << row[1] << endl;
			cout << "Book Author: " << row[2] << endl;
			cout << "Book Genre: " << row[3] << endl;
			cout << "Book Price: RM" << row[5] << endl;
			cout << "Book Stock: " << row[6] << endl;
			cout << endl << "----------------------------------------\n";
		}
	}
	else
	{
		cout << "\n\n\t\tQuery Execution Problem: " << mysql_errno(conn) << endl;
		return;
	}

	// Prompt user to enter Book ID to order
	cout << "\n\n\t\tEnter Book ID to order: ";
	cin >> bookID;
	cin.ignore();

	// Query to find book by ID
	string findbyid_query = "SELECT * FROM book WHERE bookID = " + to_string(bookID);
	const char* qi = findbyid_query.c_str();
	qstate = mysql_query(conn, qi);

	if (!qstate) {
		res = mysql_store_result(conn);
		if ((row = mysql_fetch_row(res))) {
			string title = row[1];
			string author = row[2];
			string genre = row[3];
			float price = stof(row[5]);
			int stock = stoi(row[6]);

			cout << "Enter quantity to order: ";
			int quantityOfStock;
			cin >> quantityOfStock;

			if (quantityOfStock > stock) {
				cout << "Quantity exceeds available stock.\n";
			}
			else {
				add_to_cart(bookID, title, author, genre, price, quantityOfStock);

				// Update the order table
				orderID = "some_unique_order_id"; // Generate or get a unique order ID
				totalprice = price * quantityOfStock;

				// Getting current date
				time_t now;
				struct tm ltm;
				time(&now);

#ifdef _WIN32
				localtime_s(&ltm, &now);
#else
				localtime_r(&now, &ltm);
#endif
				int currYear = 1900 + ltm.tm_year;
				int currMonth = 1 + ltm.tm_mon;
				int currDay = ltm.tm_mday;

				orderDate = to_string(currYear) + "/" + to_string(currMonth) + "/" + to_string(currDay); // Get the current date



				string insert_query = "INSERT INTO `order` (orderID, quantity, totalprice, price, bookID, orderDate, userID) VALUES ('" + orderID + "', '" + to_string(quantityOfStock) + "', '" + to_string(totalprice) + "', '" + to_string(price) + "', '" + to_string(bookID) + "', '" + orderDate + "', '" + userID + "')";
				const char* q_insert = insert_query.c_str();
				qstate = mysql_query(conn, q_insert);

				if (!qstate) {
					cout << "Order successfully added." << endl;
					// Display cart
					display_cart();

					int currentstock = stock - quantityOfStock;
					string update_query = "UPDATE book SET quantityOfStock = " + to_string(currentstock) + " WHERE bookID = " + to_string(bookID); // tgk database
					const char* q_update = update_query.c_str();
					qstate = mysql_query(conn, q_update);
					if (qstate) {
						cout << "Stock update failed! Error: " << mysql_errno(conn) << endl;
					}


					do {
						cout << setw(50) << "Do you want to add another purchase ?(y/n): "; //  add dulu baru stock tu berubah
						cin >> choose;
						if (choose == 'y' || choose == 'Y') {
							int currentstock = stock - quantityOfStock;
							string update_query = "UPDATE book SET quantityOfStock = " + to_string(currentstock) + " WHERE bookID = " + to_string(bookID); // tgk database
							const char* q_update = update_query.c_str();
							qstate = mysql_query(conn, q_update);
							Addpurchase(userID); // Corrected function call
						}
						else if (choose == 'n' || choose == 'N') {
							Viewpurchase(userID); // Corrected function call
						}
					} while (choose == 'y' || choose == 'Y' || choose == 'n' || choose == 'N');
					
				}
				else {
					cout << "Query Execution Problem! Error: " << mysql_errno(conn) << endl;
				}

			}

		}
		else {
			cout << "Book not found.\n";
		}

	}else {
		cout << "\n\n\t\tQuery Execution Problem: " << mysql_errno(conn) << endl;
	}
	
	
}

void Viewpurchase(string userID)//done 
{
	system("cls");

	cout << setw(200) << " " << endl;
	cout << setw(99) << "******************************************************************************" << endl;
	cout << setw(99) << "*                                                                            *" << endl;
	cout << setw(99) << "*                                 PURCHASE LIST                              *" << endl;
	cout << setw(99) << "*                                                                            *" << endl;
	cout << setw(99) << "******************************************************************************" << "\n" << endl;
	string view = "SELECT * FROM `order` WHERE userID = " +userID;
	qstate = mysql_query(conn, view.c_str());
	if (!qstate)
	{
		res = mysql_store_result(conn);

		cout << "\n";
		cout << setw(108) << "-----------------------------------------------------------------------------------------\n";
		//data show in box
		cout << setw(19) << "";
		printf("| %-3s | %-5s | %-10s | %-15s | %-20s | %-15s |\n", "ID", "Book", "Quantity", "Book Price RM :", "Total Purchase RM :", "Date"); 
		cout << setw(108) << "-----------------------------------------------------------------------------------------\n";

		while ((row = mysql_fetch_row(res)))
		{


			cout << setw(19) << "";
			printf("| %-3s | %-5s | %-10s | %-15s | %-20s | %-15s |\n", row[0], row[4], row[1], row[2], row[3], row[5]); 
			cout << setw(108) << "-----------------------------------------------------------------------------------------\n";
		}
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
	cout << "Press Enter To Back....";
	_getch();
	memberMenu(userID);
}

void Updatepurchase(string userID) //done
{
	int menu();
	// Variable declarations
	string orderIDStr, orderDate, title, author, genre, priceBook, price;
	float totalprice;
	char choose;
	int orderID, newQuantity, oldQuantity, bookID;
	int selectedIndex = 0;

	// Clear screen
	system("cls");

	cout << setw(200) << " " << endl;
	cout << setw(99) << "******************************************************************************" << endl;
	cout << setw(99) << "*                                                                            *" << endl;
	cout << setw(99) << "*                               UPDATE PURCHASE BOOK                         *" << endl;
	cout << setw(99) << "*                                                                            *" << endl;
	cout << setw(99) << "******************************************************************************" << "\n" << endl;

	string view = "SELECT * FROM `order` WHERE userID = " + userID;
	qstate = mysql_query(conn, view.c_str());
	if (!qstate)
	{
		res = mysql_store_result(conn);

		cout << "\n";
		cout << setw(108) << "-----------------------------------------------------------------------------------------\n";
		//data show in box
		cout << setw(19) << "";
		printf("| %-3s | %-5s | %-10s | %-15s | %-20s | %-15s |\n", "ID", "Book", "Quantity", "Book Price RM :", "Total Purchase RM :", "Date"); 
		cout << setw(108) << "-----------------------------------------------------------------------------------------\n";

		while ((row = mysql_fetch_row(res)))
		{


			cout << setw(19) << "";
			printf("| %-3s | %-5s | %-10s | %-15s | %-20s | %-15s |\n", row[0], row[4], row[1], row[2], row[3], row[5]); //
			cout << setw(108) << "-----------------------------------------------------------------------------------------\n";
		}


	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
	// Prompt user to enter Order ID to update
	cout << "\n\n\t\tEnter Order ID: ";
	cin >> orderID;
	cin.ignore();

	// Query to find order by ID
	string findOrderQuery = "SELECT * FROM `order` WHERE orderID = " + to_string(orderID);
	const char* qo = findOrderQuery.c_str();
	qstate = mysql_query(conn, qo);

	if (!qstate) {
		res = mysql_store_result(conn);
		if ((row = mysql_fetch_row(res))) {
			orderIDStr = row[0]; // Use the correct type here
			bookID = stoi(row[4]);
			oldQuantity = stoi(row[1]);
			float price = stof(row[3]);

			cout << "Current quantity: " << oldQuantity << endl;
			cout << "Enter new quantity: ";
			cin >> newQuantity;

			// Calculate the difference in quantities
			int quantityChange = newQuantity + oldQuantity;

			// Update the order table
			totalprice = price * quantityChange;

			string updateOrderQuery = "UPDATE `order` SET quantity = " + to_string(quantityChange) + ", totalprice = " + to_string(totalprice) + " WHERE orderID = " + to_string(orderID);
			const char* q_update_order = updateOrderQuery.c_str();
			qstate = mysql_query(conn, q_update_order);

			if (!qstate) {
				cout << "Order successfully updated." << endl;

				/// Update stock
				string update_query = "UPDATE book SET quantityOfStock = " + to_string(quantityChange) + " WHERE bookID = " + to_string(bookID);
				const char* q_update = update_query.c_str();
				qstate = mysql_query(conn, q_update);
				if (qstate) {
					cout << "Stock update failed! Error: " << mysql_errno(conn) << endl;
				}// Decrease stock if quantity increased, increase stock if quantity decreased


				do {
					cout << setw(50) << "Do you want to update another purchase? (y/n): ";
					cin >> choose;
					if (choose == 'y' || choose == 'Y') {
						Updatepurchase(userID);
					}
					else if (choose == 'n' || choose == 'N') {
						Viewpurchase(userID);
					}
				} while (choose == 'y' || choose == 'Y' || choose == 'n' || choose == 'N');
			}
			else {
				cout << "Query Execution Problem! Error: " << mysql_errno(conn) << endl;
			}
		}
		else {
			cout << "Order not found.\n";
		}
	}
	else {
		cout << "\n\n\t\tQuery Execution Problem: " << mysql_errno(conn) << endl;
	}
}

void Delpurchase(string userID) // done
{
	int menu();
	// Variable declarations
	string orderID;
	char choose;
	int orderIDInt, bookID, quantity;

	// Clear screen
	system("cls");

	cout << setw(200) << " " << endl;
	cout << setw(99) << "******************************************************************************" << endl;
	cout << setw(99) << "*                                                                            *" << endl;
	cout << setw(99) << "*                               DELETE PURCHASE BOOK                         *" << endl;
	cout << setw(99) << "*                                                                            *" << endl;
	cout << setw(99) << "******************************************************************************" << "\n" << endl;

	string view = "SELECT * FROM `order` WHERE userID = " + userID;
	qstate = mysql_query(conn, view.c_str());
	if (!qstate)
	{
		res = mysql_store_result(conn);

		cout << "\n";
		cout << setw(108) << "-----------------------------------------------------------------------------------------\n";
		//data show in box
		cout << setw(19) << "";
		printf("| %-3s | %-5s | %-10s | %-15s | %-20s | %-15s |\n", "ID", "Book", "Quantity", "Book Price RM :", "Total Purchase RM :", "Date");
		cout << setw(108) << "-----------------------------------------------------------------------------------------\n";

		while ((row = mysql_fetch_row(res)))
		{


			cout << setw(19) << "";
			printf("| %-3s | %-5s | %-10s | %-15s | %-20s | %-15s |\n", row[0], row[4], row[1], row[2], row[3], row[5]); 
			cout << setw(108) << "-----------------------------------------------------------------------------------------\n";
		}


	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}

	// Prompt user to enter Order ID to delete
	cout << "\n\n\t\tEnter Order ID : ";
	cin >> orderIDInt;
	cin.ignore();

	// Query to find order by ID
	string findOrderQuery = "SELECT * FROM `order` WHERE orderID = " + to_string(orderIDInt);
	const char* qo = findOrderQuery.c_str();
	qstate = mysql_query(conn, qo);

	if (!qstate) {
		res = mysql_store_result(conn);
		if ((row = mysql_fetch_row(res))) {
			orderID = row[0];
			bookID = stoi(row[4]);
			quantity = stoi(row[1]);

			// Update stock
			string update_query = "UPDATE book SET quantityOfStock = " + to_string(quantity) + " WHERE bookID = " + to_string(bookID);
			const char* q_update = update_query.c_str();
			qstate = mysql_query(conn, q_update);

			// Delete the order
			string deleteOrderQuery = "DELETE FROM `order` WHERE orderID = " + to_string(orderIDInt);
			const char* q_delete_order = deleteOrderQuery.c_str();
			qstate = mysql_query(conn, q_delete_order);

			if (!qstate) {
				cout << "Order successfully deleted." << endl;


				do {
					cout << setw(50) << "Do you want to delete another purchase? (y/n): ";
					cin >> choose;
					if (choose == 'y' || choose == 'Y') {
						Delpurchase(userID);
					}
					else if (choose == 'n' || choose == 'N') {
						Viewpurchase(userID);
					}
				} while (choose == 'y' || choose == 'Y' || choose == 'n' || choose == 'N');
			}
			else {
				cout << "Query Execution Problem! Error: " << mysql_errno(conn) << endl;
			}
		}
		else {
			cout << "Order not found.\n";
		}
	}
	else {
		cout << "\n\n\t\tQuery Execution Problem: " << mysql_errno(conn) << endl;
	}
}

void payment(string userID) {
	// Variable declarations
	double amountPaid = 0.0;
	double totalAmount = 0.0;

	// Clear screen
	system("cls");

	cout << setw(200) << " " << endl;
	cout << setw(99) << "******************************************************************************" << endl;
	cout << setw(99) << "*                                                                            *" << endl;
	cout << setw(99) << "*                               PAYMENT                                      *" << endl;
	cout << setw(99) << "*                                                                            *" << endl;
	cout << setw(99) << "******************************************************************************" << "\n" << endl;

	string view = "SELECT * FROM `order` WHERE userID = '" + userID + "' AND status = 'unpaid'";
	qstate = mysql_query(conn, view.c_str());
	if (!qstate) {
		res = mysql_store_result(conn);

		cout << "\n";
		cout << setw(108) << "-----------------------------------------------------------------------------------------\n";
		//data show in box
		cout << setw(19) << "";
		printf("| %-3s | %-5s | %-10s | %-15s | %-20s | %-15s |\n", "ID", "Book", "Quantity", "Book Price RM :", "Total Purchase RM :", "Date");
		cout << setw(108) << "-----------------------------------------------------------------------------------------\n";

		while ((row = mysql_fetch_row(res))) {
			double bookPrice = stod(row[2]);
			int orderQuantity = stoi(row[1]);
			double totalPurchase = bookPrice * orderQuantity;
			totalAmount += totalPurchase;

			cout << setw(19) << "";
			printf("| %-3s | %-5s | %-10s | %-15s | %-20.2f | %-15s |\n", row[0], row[4], row[1], row[2], totalPurchase, row[5]);
			cout << setw(108) << "-----------------------------------------------------------------------------------------\n";
		}

		// Display total amount to be paid
		cout << "\n" << setw(108) << "Total Amount to be Paid: RM " << totalAmount << endl;

		bool flag = false;

		// Prompt user to enter payment amount
		while (amountPaid < totalAmount) {
			flag = true;
			double payment;
			cout << "\n\n\t\tEnter payment amount: RM ";
			cin >> payment;
			cin.ignore();

			if (payment <= 0) {
				cout << "Invalid payment amount. It must be greater than 0.\n";
				continue;
			}

			amountPaid += payment;
			cout << "Total Paid: RM " << amountPaid << endl;
			cout << "Remaining Amount: RM " << totalAmount - amountPaid << endl;
		}

		if (flag)
		{
			// Display receipt
			cout << setw(200) << " " << endl;
			cout << "******************************************************************************" << endl;
			cout << "*                               RECEIPT                                      *" << endl;
			cout << "******************************************************************************" << endl;
			cout << "Total Amount to be Paid: RM " << totalAmount << endl;
			cout << "Total Paid: RM " << amountPaid << endl;
			cout << "Change: RM " << amountPaid - totalAmount << endl;
			cout << "******************************************************************************" << endl;

			// Insert payment details into the payment table
			string insertPaymentQuery = "INSERT INTO `payment` (userID, amount) VALUES ('" + userID + "', " + to_string(totalAmount) + ")";
			const char* q_insert_payment = insertPaymentQuery.c_str();
			qstate = mysql_query(conn, q_insert_payment);

			if (!qstate) {
				cout << "Payment details recorded successfully." << endl;
			}
			else {
				cout << "Error recording payment details! Error: " << mysql_errno(conn) << endl;
			}

			// Update the order status to 'paid' for all unpaid orders of the user
			string updateOrderStatusQuery = "UPDATE `order` SET status = 'paid' WHERE userID = '" + userID + "' AND status = 'unpaid'";
			const char* q_update_status = updateOrderStatusQuery.c_str();
			qstate = mysql_query(conn, q_update_status);

			if (!qstate) {
				cout << "All orders successfully paid." << endl;
			}
			else {
				cout << "Query Execution Problem! Error: " << mysql_errno(conn) << endl;
			}
		}

		

		// Pause after displaying receipt
		cout << "\nPress any key to continue...";
		cin.ignore();
		cin.get();

		// Go back to the previous menu
		// Assuming Viewpurchase is a function to view purchases
		Viewpurchase(userID);
	}
	else {
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
}


