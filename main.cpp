#include <iostream>
#include<winsock.h>
#include<windows.h>
#include<sstream>
#include<ctime>
#include<string>
#include<mysql.h>
#include<cstring>
#include<conio.h>
#include<cstring>
#include<map>
#include <limits>
using namespace std;
int users =0;
int count_attempt=0;
int curr_user=0;
int user_no=0;
map <string,string> issued;
string loggedin_user="";

void showtime()
{
	time_t now = time(0);
	char *dt = ctime(&now);
	cout<<dt;
	cout<<endl<<endl;
}
bool adminLogin() {
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "localhost", "root", "root", "librarydb", 0, NULL, 0);

    if (!conn) {
        cout << "Connection to database failed: " << mysql_error(conn) << endl;
        return false;
    }

    string user_name;
    string pass_word;
    int maxAttempts = 3;
    int attempts = 0;
    bool loginSuccessful = false;

    while (attempts < maxAttempts && !loginSuccessful) {
        cout << "Enter Credentials for Login (ID Password)" << endl;
        cout << "Username: ";
        cin >> user_name;
        cout << "Password: ";
        cin >> pass_word;
        cin.ignore();

        stringstream ss;
        ss << "SELECT username, password FROM admin WHERE username = '" << user_name << "' AND password = '" << pass_word << "'";
        string query = ss.str();
        const char* q = query.c_str();
        int qstate = mysql_query(conn, q);

        if (!qstate) {
            res = mysql_store_result(conn);
            if (mysql_num_rows(res) > 0) {
                cout << "Login Successful" << endl;
                loggedin_user = user_name;
                curr_user = 1;
                loginSuccessful = true;
            } else {
                cout << "Invalid username or password. Please try again." << endl;
                attempts++;
                if (attempts < maxAttempts) {
                    cout << "Attempts remaining: " << (maxAttempts - attempts) << endl;
                }
            }
        } else {
            cout << "Query failed: " << mysql_error(conn) << endl;
            break;
        }

        cin.ignore();
        system("cls");
    }

    if (!loginSuccessful) {
        cout << "Max login attempts reached. Exiting login." << endl;
    }

    mysql_free_result(res);
    mysql_close(conn);
    return loginSuccessful;
}

bool librarianLogin() {
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "localhost", "root", "root", "librarydb", 0, NULL, 0);

    if (!conn) {
        cout << "Connection to database failed: " << mysql_error(conn) << endl;
        return false;
    }

    string user_name;
    string pass_word;
    int maxAttempts = 3;
    int attempts = 0;
    bool loginSuccessful = false;

    while (attempts < maxAttempts && !loginSuccessful) {
        cout << "Enter Credentials for Login (ID Password)" << endl;
        cout << "Username: ";
        cin >> user_name;
        cout << "Password: ";
        cin >> pass_word;
        cin.ignore();

        stringstream ss;
        ss << "SELECT username, password FROM librarian WHERE username = '" << user_name << "' AND password = '" << pass_word << "'";
        string query = ss.str();
        const char* q = query.c_str();
        int qstate = mysql_query(conn, q);

        if (!qstate) {
            res = mysql_store_result(conn);
            if (mysql_num_rows(res) > 0) {
                cout << "Login Successful" << endl;
                loggedin_user = user_name;
                curr_user = 2; // Assuming `curr_user` is set to 2 for Librarian
                loginSuccessful = true;
            } else {
                cout << "Invalid username or password. Please try again." << endl;
                attempts++;
                if (attempts < maxAttempts) {
                    cout << "Attempts remaining: " << (maxAttempts - attempts) << endl;
                }
            }
        } else {
            cout << "Query failed: " << mysql_error(conn) << endl;
            break;
        }

        cin.ignore();
        system("cls");
    }

    if (!loginSuccessful) {
        cout << "Max login attempts reached. Exiting login." << endl;
    }

    mysql_free_result(res);
    mysql_close(conn);
    return loginSuccessful;
}

bool userLogin() {
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "localhost", "root", "root", "librarydb", 0, NULL, 0);

    if (!conn) {
        cout << "Connection to database failed: " << mysql_error(conn) << endl;
        return false;
    }

    string user_name;
    string pass_word;
    int maxAttempts = 3;
    int attempts = 0;
    bool loginSuccessful = false;

    while (attempts < maxAttempts && !loginSuccessful) {
        cout << "Enter Credentials for Login (ID Password)" << endl;
        cout << "Username: ";
        cin >> user_name;
        cout << "Password: ";
        cin >> pass_word;
        cin.ignore();

        stringstream ss;
        ss << "SELECT username, password FROM user WHERE username = '" << user_name << "' AND password = '" << pass_word << "'";
        string query = ss.str();
        const char* q = query.c_str();
        int qstate = mysql_query(conn, q);

        if (!qstate) {
            res = mysql_store_result(conn);
            if (mysql_num_rows(res) > 0) {
                cout << "Login Successful" << endl;
                loggedin_user = user_name;
                curr_user = 3; // Assuming `curr_user` is set to 3 for User
                loginSuccessful = true;
            } else {
                cout << "Invalid username or password. Please try again." << endl;
                attempts++;
                if (attempts < maxAttempts) {
                    cout << "Attempts remaining: " << (maxAttempts - attempts) << endl;
                }
            }
        } else {
            cout << "Query failed: " << mysql_error(conn) << endl;
            break;
        }

        cin.ignore();
        system("cls");
    }

    if (!loginSuccessful) {
        cout << "Max login attempts reached. Exiting login." << endl;
    }

    mysql_free_result(res);
    mysql_close(conn);
    return loginSuccessful;
}


class admin {
public:
    void addlibrarian() {
        string username, password;
        int LibrarianId;
        MYSQL *conn;
        conn = mysql_init(0);
        conn = mysql_real_connect(conn,"localhost","root","root","librarydb",0,NULL,0);
        cout << "Id For Librarian : ";
        while (!(cin >> LibrarianId)) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore leftover newline
            cout << "Invalid input. Please enter a valid integer for Librarian: "<<endl;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore leftover newline

        cout<<"Username For Librarian : ";
        cin>>username;
        cout<<"Password For Librarian : ";
        cin>>password;

        int qstate =0;
        stringstream ss;
        ss<<"INSERT INTO librarian(LibrarianId, Username , Password) VALUES('"<<LibrarianId<<"','"<<username<<"','"<<password<<"')";
        string query =  ss.str();
        const char* q= query.c_str();
        qstate = mysql_query(conn,q);
        if(qstate==0)
            cout<<"Record Inserted Succesfully ... "<<endl;
        else cout<<"Already Exist With Same ID!!"<<endl;
    }

    void deletelibrarian() {
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "localhost", "root", "root", "librarydb", 0, NULL, 0);

    if (conn) {
        int LibrarianId;
         while (!(cin >> LibrarianId)) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a valid integer for Librarian Id: ";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        stringstream ss;
        ss << "DELETE FROM librarian WHERE LibrarianId = " << LibrarianId;
        string query = ss.str();
        const char* q = query.c_str();
        int qstate = mysql_query(conn, q);

        if (qstate == 0) {
            // Check the number of affected rows
            if (mysql_affected_rows(conn) > 0) {
                cout << "Record Deleted Successfully ..." << endl;
            } else {
                cout << "Librarian ID not found" << endl;
            }
        } else {
            cout << "Failed: " << mysql_error(conn) << endl;
        }

        mysql_close(conn);
    } else {
        cout << "Connection to database failed: " << mysql_error(conn) << endl;
    }
}

    void printalllibrarians() {
        cout<<"The Librarians are:  "<<endl;
        MYSQL* conn;
        MYSQL_ROW row;
        MYSQL_RES* res;
        conn = mysql_init(0);
        conn = mysql_real_connect(conn,"localhost","root","root","librarydb",0,NULL,0);
        if(conn)
        {
            int qstate = mysql_query(conn,"SELECT LibrarianId, username FROM librarian");
        //    bool flag=false;
            if(!qstate)
            {
                res = mysql_store_result(conn);
                int i=1;
                while(row = mysql_fetch_row(res))
                    {
                        cout<<row[0]<<". "<<row[1]<<endl;
                        i++;

                    }
            }
        }
    }
};


class user
{
private:
string username;
string password;
int UserId;
public:
void adduser() {
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "localhost", "root", "root", "librarydb", 0, NULL, 0);

    if (!conn) {
        cout << "Connection to database failed: " << mysql_error(conn) << endl;
        return;
    }

    int UserId;
    string username;
    string password;

    cout << "Id: ";
    while (!(cin >> UserId)) {
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        cout << "Invalid input. Please enter a valid integer for UserId: "<<endl;
    }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore leftover newline


    cout << "Username: ";
    cin >> username;

    cout << "Password: ";
    cin >> password;

    stringstream ss;
    ss << "INSERT INTO user(UserId, username, password) VALUES(" << UserId << ", '" << username << "', '" << password << "')";
    string query = ss.str();
    const char* q = query.c_str();
    int qstate = mysql_query(conn, q);

    if (qstate == 0) {
        cout << "Record Inserted Successfully ..." << endl;
    } else {
        cout << "Failed to insert record: User Already Exist"<< endl;
    }

    mysql_close(conn);
}


void deleteuser() {
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "localhost", "root", "root", "librarydb", 0, NULL, 0);

    if (!conn) {
        cout << "Connection to database failed: " << mysql_error(conn) << endl;
        return;
    }

    int UserId;
    cout << "Id of User You Want To Delete: ";
    while (!(cin >> UserId)) {
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        cout << "Invalid input. Please enter a valid integer for UserId: " << endl;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore leftover newline

    // Check if the user has any books issued
    stringstream check_ss;
    check_ss << "SELECT COUNT(*) FROM issue WHERE username = (SELECT username FROM user WHERE UserId = " << UserId << ")";
    string check_query = check_ss.str();
    const char* check_q = check_query.c_str();
    int qstate = mysql_query(conn, check_q);

    if (!qstate) {
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row = mysql_fetch_row(res);
        int issuedBooksCount = atoi(row[0]);

        mysql_free_result(res);

        if (issuedBooksCount > 0) {
            cout << "Cannot delete user. The user has issued books." << endl;
            mysql_close(conn);
            return;
        }

        // Delete all requests related to the user
        stringstream delete_requests_ss;
        delete_requests_ss << "DELETE FROM request WHERE username = (SELECT username FROM user WHERE UserId = " << UserId << ")";
        string delete_requests_query = delete_requests_ss.str();
        const char* delete_requests_q = delete_requests_query.c_str();
        qstate = mysql_query(conn, delete_requests_q);

        if (qstate) {
            cout << "Failed to delete requests: " << mysql_error(conn) << endl;
            mysql_close(conn);
            return;
        }

        // Delete the user
        stringstream delete_user_ss;
        delete_user_ss << "DELETE FROM user WHERE UserId = " << UserId;
        string delete_user_query = delete_user_ss.str();
        const char* delete_user_q = delete_user_query.c_str();
        qstate = mysql_query(conn, delete_user_q);

        if (qstate == 0) {
            if (mysql_affected_rows(conn) > 0) {
                cout << "Record Deleted Successfully ..." << endl;
            } else {
                cout << "User ID not found" << endl;
            }
        } else {
            cout << "Failed to delete user: " << mysql_error(conn) << endl;
        }
    } else {
        cout << "Failed to check issued books: " << mysql_error(conn) << endl;
    }

    mysql_close(conn);
}



void getcount() {
    cout << "The number of users in the database are: " << endl;
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;

    conn = mysql_init(0);
    if (conn == nullptr) {
        cerr << "mysql_init() failed" << endl;
        return;
    }

    conn = mysql_real_connect(conn,"localhost","root","root","librarydb",0,NULL,0);
    if (conn) {
        int qstate = mysql_query(conn, "SELECT COUNT(*) AS total_entries FROM user");
        if (qstate == 0) {
            res = mysql_store_result(conn);
            if (res) {
                row = mysql_fetch_row(res);
                if (row) {
                    cout << row[0] << endl;
                }
                mysql_free_result(res);
            } else {
                cerr << "Failed to retrieve result: " << mysql_error(conn) << endl;
            }
        } else {
            cerr << "Query failed: " << mysql_error(conn) << endl;
        }
    } else {
        cerr << "Connection failed: " << mysql_error(conn) << endl;
    }
    mysql_close(conn);
}
void printallusers()
{
	cout<<"The users are:  "<<endl;
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);
	conn = mysql_real_connect(conn,"localhost","root","root","librarydb",0,NULL,0);
	if(conn)
    {
        int qstate = mysql_query(conn,"SELECT UserId,username FROM user");
    //    bool flag=false;
        if(!qstate)
        {
            res = mysql_store_result(conn);
            int i=1;
            while(row = mysql_fetch_row(res))
                {
                    cout<<row[0]<<"."<<row[1]<<endl;
                    i++;

                }
        }
    }


}

};
class book : public user
{
	long long int bno;
	string bookname;
	string aname;
	int bcount;
	public:
    void addbook() {

        cout << "Enter book number: ";
        while (!(cin >> bno)) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a valid integer for Book Number: " << endl;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore leftover newline

        cout << "Enter book name: ";
        getline(cin, bookname);

        cout << "Enter author name: ";
        getline(cin, aname);

        cout << "Enter the count of the book: ";
        while (!(cin >> bcount)) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a valid integer for Book Quantity: " << endl;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore leftover newline

        MYSQL* conn;
        MYSQL_RES* res;
        MYSQL_ROW row;
        conn = mysql_init(0);
        conn = mysql_real_connect(conn, "localhost", "root", "root", "librarydb", 0, NULL, 0);

        if (!conn) {
            cout << "Connection to database failed: " << mysql_error(conn) << endl;
            return;
        }

        // Check if book already exists
        stringstream check_ss;
        check_ss << "SELECT * FROM book WHERE BookNo = '" << bno << "'";
        string check_query = check_ss.str();
        const char* check_q = check_query.c_str();
        int check_qstate = mysql_query(conn, check_q);

        if (!check_qstate) {
            res = mysql_store_result(conn);
            if (mysql_num_rows(res) > 0) {
                cout << "A book with this number already exists. Please choose a different book number." << endl;
                mysql_free_result(res);
                mysql_close(conn);
                return;
            }
            mysql_free_result(res);
        } else {
            cout << "Query failed: " << mysql_error(conn) << endl;
            mysql_close(conn);
            return;
        }

        // Insert new book
        stringstream insert_ss;
        insert_ss << "INSERT INTO book (BookNo, Book_Name, Author, Quantity) VALUES ('" << bno << "', '" << bookname << "', '" << aname << "', " << bcount << ")";
        string insert_query = insert_ss.str();
        const char* insert_q = insert_query.c_str();
        int insert_qstate = mysql_query(conn, insert_q);

        if (insert_qstate == 0) {
            cout << "Book Added Successfully ..." << endl;
        } else {
            cout << "Failed to add book: " << mysql_error(conn) << endl;
        }

        mysql_close(conn);
    }

    void deletebook() {
        MYSQL* conn;
        MYSQL_RES* res;
        MYSQL_ROW row;
        conn = mysql_init(0);
        conn = mysql_real_connect(conn, "localhost", "root", "root", "librarydb", 0, NULL, 0);

        if (!conn) {
            cout << "Connection to database failed: " << mysql_error(conn) << endl;
            return;
        }

        string bno;
        cout << "Enter book number: ";
        cin >> bno;

        // Validate the book number input
        int bookNo;
        stringstream ss(bno);
        if (!(ss >> bookNo) || !ss.eof()) {
            cout << "Invalid input. Please enter a valid integer for Book Number." << endl;
            mysql_close(conn);
            return;
        }

        // Check if the book exists before attempting to delete
        stringstream check_ss;
        check_ss << "SELECT * FROM book WHERE BookNo = " << bookNo;
        string check_query = check_ss.str();
        const char* check_q = check_query.c_str();
        int check_qstate = mysql_query(conn, check_q);

        if (!check_qstate) {
            res = mysql_store_result(conn);
            if (mysql_num_rows(res) == 0) {
                cout << "Book not found." << endl;
                mysql_free_result(res);
                mysql_close(conn);
                return;
            }
            mysql_free_result(res);
        } else {
            cout << "Query failed: " << mysql_error(conn) << endl;
            mysql_close(conn);
            return;
        }

        // Proceed with deletion if the book exists
        stringstream delete_ss;
        delete_ss << "DELETE FROM book WHERE BookNo = " << bookNo;
        string delete_query = delete_ss.str();
        const char* delete_q = delete_query.c_str();
        int delete_qstate = mysql_query(conn, delete_q);

        if (delete_qstate == 0) {
            cout << "Book deleted successfully." << endl;
        } else {
            cout << "Failed to delete book: " << mysql_error(conn) << endl;
        }

        mysql_close(conn);
    }

		bool searchbook(string no)
		{

			bool flag=false;
            //cout<<"No"<<"\t\t"<<"Name"<<"\t\t"<<"Author"<<"\t\t"<<"Count"<<endl;

			MYSQL* conn;
            MYSQL_ROW row;
            MYSQL_RES* res;
            conn = mysql_init(0);
            conn = mysql_real_connect(conn,"localhost","root","root","librarydb",0,NULL,0);
            if(conn)
            {
            int qstate = mysql_query(conn,"SELECT BookNo,Book_Name,Author,Quantity from book");
            if(!qstate)
            {
                res = mysql_store_result(conn);
                while(row = mysql_fetch_row(res))
                {
              //     cout<<row[]<<endl;
                        if(row[0]== no)
                        {
                            //cout<<row[0]<<"\t\t"<<row[1]<<"\t\t"<<row[2]<<"\t\t"<<row[3]<<endl;

                            cout<<"Book Found"<<endl;
                            flag=true;
                            mysql_close(conn);
                            return true;
                        }
                }
            }
            else cout<<"Failed"<<endl;
            if(!flag)
                {
                    cout<<"Book Not Found"<<endl;
                    return false;
                }
            }
		}
		void allbooks()
		{
			MYSQL* conn;
            MYSQL_ROW row;
            MYSQL_RES* res;
            conn = mysql_init(0);
            conn = mysql_real_connect(conn,"localhost","root","root","librarydb",0,NULL,0);
            if(conn)
            {
            int qstate = mysql_query(conn,"SELECT BookNo,Book_Name,Author,Quantity from book");

            cout<<"No"<<"\t\t"<<"Name"<<"\t\t"<<"Author"<<"\t\t"<<"Count"<<endl;
            if(!qstate)
            {
                res = mysql_store_result(conn);
                while(row = mysql_fetch_row(res))
                {

                    cout<<row[0]<<"\t\t"<<row[1]<<"\t\t"<<row[2]<<"\t\t"<<row[3]<<endl;
                }
                return;

            }
            }
            else cout<<"Failed"<<endl;
		}
/*
	void issue() {
    if (loggedin_user == "") {
        cout << "Please Login" << endl;
        return;
    }

    string bno;
    cout << "Enter book number to be issued: ";
    cin >> bno;



    bool found = searchbook(bno);
    if (found) {
        MYSQL* conn;
        MYSQL_ROW row;
        MYSQL_RES* res;
        conn = mysql_init(0);
        conn = mysql_real_connect(conn,"localhost","root","root","librarydb",0,NULL,0);

        if (conn) {
            stringstream ss;
            ss << "SELECT BookNo, Issued_By FROM book WHERE BookNo = '" << bno << "'";
            string query = ss.str();
            const char* q = query.c_str();
            int qstate = mysql_query(conn, q);

            if (!qstate) {
                res = mysql_store_result(conn);
                if ((row = mysql_fetch_row(res))) {
                    if (row[1] != nullptr && string(row[1]) == loggedin_user) {
                        cout << "You have already issued this book" << endl;
                    } else if (row[1] == nullptr || string(row[1]).empty()) {
                        ss.str("");
                        ss << "UPDATE book SET Issued_By = '" << loggedin_user << "' WHERE BookNo = '" << bno << "'";
                        query = ss.str();
                        q = query.c_str();
                        qstate = mysql_query(conn, q);

                        if (qstate == 0) {
                            cout << "Book Issued Successfully ..." << endl;
                            issued[bno] = loggedin_user;  // Add to issued map
                        } else {
                            cout << "Failed to issue book: " << mysql_error(conn) << endl;
                        }
                    } else {
                        cout << "Book is already issued by another user" << endl;
                    }
                } else {
                    cout << "Book Not Found" << endl;
                }

                mysql_free_result(res);
            } else {
                cout << "Query failed: " << mysql_error(conn) << endl;
            }

            mysql_close(conn);
        } else {
            cout << "Connection to database failed: " << mysql_error(conn) << endl;
        }
    } else {
        cout << "Book Not Found" << endl;
    }
}*/
void issue() {
    string bno;
    cout << "Enter book number to be issued: ";
    cin >> bno;

    bool found = searchbook(bno);
    if (found) {
        MYSQL* conn;
        MYSQL_ROW row;
        MYSQL_RES* res;
        conn = mysql_init(0);
        conn = mysql_real_connect(conn, "localhost", "root", "root", "librarydb", 0, NULL, 0);

        if (conn) {
            stringstream ss;
            ss << "SELECT Quantity FROM book WHERE BookNo = '" << bno << "'";
            string query = ss.str();
            const char* q = query.c_str();
            int qstate = mysql_query(conn, q);

            if (!qstate) {
                res = mysql_store_result(conn);
                if ((row = mysql_fetch_row(res))) {
                    int quantity = atoi(row[0]);
                    if (quantity > 0) {
                        ss.str("");
                        ss << "INSERT INTO request (BookNo, username) VALUES ('" << bno << "', '" << loggedin_user << "')";
                        query = ss.str();
                        q = query.c_str();
                        qstate = mysql_query(conn, q);

                        if (qstate == 0) {
                            cout << "Your request has been sent successfully ..." << endl;
                        } else {
                            cout << "Failed to send request: " << mysql_error(conn) << endl;
                        }
                    } else {
                        cout << "Book is out of stock" << endl;
                    }
                } else {
                    cout << "Book Not Found" << endl;
                }

                mysql_free_result(res);
            } else {
                cout << "Query failed: " << mysql_error(conn) << endl;
            }

            mysql_close(conn);
        } else {
            cout << "Connection to database failed: " << mysql_error(conn) << endl;
        }
    } else {
        cout << "Book Not Found" << endl;
    }
}


void deposit() {
    if (loggedin_user == "") {
        cout << "Please Login" << endl;
        return;
    }

    string bno;
    cout << "Enter book number to be deposited: ";
    cin >> bno;

    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "localhost", "root", "root", "librarydb", 0, NULL, 0);

    if (conn) {
        // Check if the book is issued by the logged-in user
        stringstream ss;
        ss << "SELECT BookNo FROM issue WHERE BookNo = '" << bno << "' AND username = '" << loggedin_user << "'";
        string query = ss.str();
        const char* q = query.c_str();
        int qstate = mysql_query(conn, q);

        if (!qstate) {
            res = mysql_store_result(conn);
            if ((row = mysql_fetch_row(res))) {
                // Book is found in the issued records, proceed to update and delete
                // Increment the quantity of the book in the book table
                ss.str("");
                ss << "UPDATE book SET Quantity = Quantity + 1 WHERE BookNo = '" << bno << "'";
                query = ss.str();
                q = query.c_str();
                qstate = mysql_query(conn, q);

                if (qstate == 0) {
                    // Delete the issued record from the issue table
                    ss.str("");
                    ss << "DELETE FROM issue WHERE BookNo = '" << bno << "' AND username = '" << loggedin_user << "'";
                    query = ss.str();
                    q = query.c_str();
                    qstate = mysql_query(conn, q);

                    if (qstate == 0) {
                        cout << "Book Deposited Successfully ..." << endl;
                        issued.erase(bno);  // Remove from issued map if applicable
                    } else {
                        cout << "Failed to remove issued record: " << mysql_error(conn) << endl;
                    }
                } else {
                    cout << "Failed to update book quantity: " << mysql_error(conn) << endl;
                }
            } else {
                cout << "You have not issued this book" << endl;
            }

            mysql_free_result(res);
        } else {
            cout << "Query failed: " << mysql_error(conn) << endl;
        }

        mysql_close(conn);
    } else {
        cout << "Connection to database failed: " << mysql_error(conn) << endl;
    }
}

	void print_user()
	{
		 map<string ,string>:: iterator itr;
		 bool flag=false;
				 for(itr=issued.begin();itr!=issued.end();itr++)
				 {
				 	if(itr->second==loggedin_user )
				 	{
					 cout<<"Current user is "<<itr->second<<"   has issued book no   : "<<itr->first;
					 flag=true;

					 }

				}
				if(!flag)
					cout<<loggedin_user<<" has issued no book";
				 	cout<<endl;
	}


};
/*
void seependingrequests() {
    cout<<"Working on this functionality"<<endl;
}*/
/*
void seependingrequests() {
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,"localhost","root","root","librarydb",0,NULL,0);

    if (conn) {
        string query = "SELECT BookNo, username FROM request";
        const char* q = query.c_str();
        int qstate = mysql_query(conn, q);

        if (!qstate) {
            res = mysql_store_result(conn);
            if (mysql_num_rows(res) == 0) {
                cout << "No pending requests" << endl;
            } else {
                cout << "Pending Requests:" << endl;
                while ((row = mysql_fetch_row(res))) {
                    cout << "BookNo: " << row[0] << ", Username: " << row[1] << endl;
                }

                string action;
                cout << "Enter 'accept' or 'reject': ";
                cin >> action;

                mysql_data_seek(res, 0); // Reset the result pointer to the beginning

                while ((row = mysql_fetch_row(res))) {
                    string bno = row[0];
                    string username = row[1];

                    if (action == "accept") {
                        stringstream ss;
                        ss << "UPDATE book SET Issued_By = '" << username << "' WHERE BookNo = " << bno;
                        query = ss.str();
                        q = query.c_str();
                        qstate = mysql_query(conn, q);

                        if (qstate == 0) {
                            ss.str("");
                            ss << "DELETE FROM request WHERE BookNo = " << bno << " AND username = '" << username << "'";
                            query = ss.str();
                            q = query.c_str();
                            qstate = mysql_query(conn, q);

                            if (qstate == 0) {
                                cout << "Request approved successfully" << endl;
                            } else {
                                cout << "Failed to remove request: " << mysql_error(conn) << endl;
                            }
                        } else {
                            cout << "Failed to update book: " << mysql_error(conn) << endl;
                        }
                    } else if (action == "reject") {
                        stringstream ss;
                        ss << "DELETE FROM request WHERE BookNo = " << bno << " AND username = '" << username << "'";
                        query = ss.str();
                        q = query.c_str();
                        qstate = mysql_query(conn, q);

                        if (qstate == 0) {
                            cout << "Request rejected successfully" << endl;
                        } else {
                            cout << "Failed to remove request: " << mysql_error(conn) << endl;
                        }
                    } else {
                        cout << "Invalid action" << endl;
                    }
                }
            }
            mysql_free_result(res);
        } else {
            cout << "Query failed: " << mysql_error(conn) << endl;
        }
        mysql_close(conn);
    } else {
        cout << "Connection to database failed: " << mysql_error(conn) << endl;
    }
}
*/
void seependingrequests() {
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "localhost", "root", "root", "librarydb",0, NULL, 0);

    if (conn) {
        string query = "SELECT BookNo, username FROM request";
        const char* q = query.c_str();
        int qstate = mysql_query(conn, q);

        if (!qstate) {
            res = mysql_store_result(conn);
            if (mysql_num_rows(res) == 0) {
                cout << "No pending requests" << endl;
            } else {
                while ((row = mysql_fetch_row(res))) {
                    string bno = row[0];
                    string username = row[1];

                    cout << "BookNo: " << bno << ", Username: " << username << endl;

                    string action;
                    cout << "Enter 'accept' or 'reject': ";
                    cin >> action;

                    if (action == "accept") {
                        stringstream ss;
                        ss << "UPDATE book SET Quantity = Quantity - 1 WHERE BookNo = " << bno;
                        string query = ss.str();
                        const char* q = query.c_str();
                        int qstate = mysql_query(conn, q);

                        if (qstate == 0) {
                            ss.str("");
                            ss << "INSERT INTO issue (username, BookNo) VALUES ('" << username << "', " << bno << ")";
                            query = ss.str();
                            q = query.c_str();
                            qstate = mysql_query(conn, q);

                            if (qstate == 0) {
                                // Delete the request from the request table
                                ss.str("");  // Clear the stringstream
                                ss << "DELETE FROM request WHERE BookNo = " << bno << " AND username = '" << username << "'";
                                query = ss.str();
                                q = query.c_str();
                                qstate = mysql_query(conn, q);

                                if (qstate == 0) {
                                    cout << "Request approved successfully" << endl;
                                } else {
                                    cout << "Failed to remove request: " << mysql_error(conn) << endl;
                                }
                            } else {
                                cout << "Failed to insert into issue table: " << mysql_error(conn) << endl;
                            }
                        } else {
                            cout << "Failed to update book quantity: " << mysql_error(conn) << endl;
                        }
                    }
                     else if (action == "reject") {
                        stringstream ss;
                        ss << "DELETE FROM request WHERE BookNo = " << bno << " AND username = '" << username << "'";
                        query = ss.str();
                        q = query.c_str();
                        qstate = mysql_query(conn, q);

                        if (qstate == 0) {
                            cout << "Request rejected successfully" << endl;
                        } else {
                            cout << "Failed to remove request: " << mysql_error(conn) << endl;
                        }
                    } else {
                        cout << "Invalid action" << endl;
                    }
                }
            }
            mysql_free_result(res);
        } else {
            cout << "Query failed: " << mysql_error(conn) << endl;
        }
        mysql_close(conn);
    } else {
        cout << "Connection to database failed: " << mysql_error(conn) << endl;
    }
}

void mybooks() {
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "localhost", "root", "root", "librarydb", 0, NULL, 0);

    if (conn) {
        // Query to get all BookNo for the logged-in user from the issue table
        stringstream ss;
        ss << "SELECT BookNo FROM issue WHERE username = '" << loggedin_user << "'";
        string query = ss.str();
        const char* q = query.c_str();
        int qstate = mysql_query(conn, q);

        if (!qstate) {
            res = mysql_store_result(conn);
            if (mysql_num_rows(res) > 0) {
                // If there are issued books, fetch their details
                cout << "Books currently issued to you:" << endl;

                while ((row = mysql_fetch_row(res))) {
                    string bookNo = row[0];

                    // Query to get book details from the book table
                    ss.str("");
                    ss << "SELECT BookNo, Book_Name FROM book WHERE BookNo = '" << bookNo << "'";
                    query = ss.str();
                    q = query.c_str();
                    qstate = mysql_query(conn, q);

                    if (!qstate) {
                        MYSQL_RES* bookRes = mysql_store_result(conn);
                        if ((row = mysql_fetch_row(bookRes))) {
                            cout << "Book Number: " << row[0] << ", Book Name: " << row[1] << endl;
                        } else {
                            cout << "Failed to retrieve book details" << endl;
                        }
                        mysql_free_result(bookRes);
                    } else {
                        cout << "Query failed: " << mysql_error(conn) << endl;
                    }
                }
            } else {
                cout << "No books issued" << endl;
            }

            mysql_free_result(res);
        } else {
            cout << "Query failed: " << mysql_error(conn) << endl;
        }

        mysql_close(conn);
    } else {
        cout << "Connection to database failed: " << mysql_error(conn) << endl;
    }
}

int main() {




    int x;
    bool exitProgram = false;

    user u1;
    book b1;
    admin manager;

    while (!exitProgram) {
            system("cls");
            showtime();
    cout << "\t\t\t\t\t\t Library Management System Main Menu" << endl << endl << endl << endl;
        cout << endl;
        cout << "Choose from the Following:" << endl;
        cout << "1. Login as Admin" << endl;
        cout << "2. Login as Librarian" << endl;
        cout << "3. Login as User" << endl;
        cout << "0 to exit" << endl;
        cin >> x;

        switch (x) {
            case 1:
                if (adminLogin()) {
            system("cls");
            showtime();
    cout << "\t\t\t\t\t\t Admin Menu" << endl << endl << endl << endl;
                    bool adminMenuActive = true;
                    while (adminMenuActive && !exitProgram) {
                        cout << endl;
                        cout << "Admin Options:" << endl;
                        cout << "1. Add Librarian" << endl;
                        cout << "2. Delete Librarian" << endl;
                        cout << "3. Add Book" << endl;
                        cout << "4. Delete Book" << endl;
                        cout << "5. Print All Books" << endl;
                        cout << "6. Print All Librarians" << endl;
                        cout << "7. Add User" << endl;
                        cout << "8. Delete User" << endl;
                        cout << "9. Print All Users" << endl;
                        cout << "10. Logout" << endl;
                        cout << "0 to exit" << endl;
                        cin >> x;

                        switch (x) {
                            case 1: manager.addlibrarian(); break;
                            case 2: manager.deletelibrarian(); break;
                            case 3: b1.addbook(); break;
                            case 4: b1.deletebook(); break;
                            case 5: b1.allbooks(); break;
                            case 6: manager.printalllibrarians(); break;
                            case 7: u1.adduser(); break;
                            case 8: u1.deleteuser(); break;
                            case 9: u1.printallusers(); break;
                            case 10: adminMenuActive = false; break;
                            case 0: exitProgram = true; break;
                            default: cout << "Invalid option. Please try again." << endl; break;
                        }
                    }
                }
                break;

            case 2:
                if (librarianLogin()) {
                    system("cls");
                    showtime();
    cout << "\t\t\t\t\t\t Librarian Menu" << endl << endl << endl << endl;
                    bool librarianMenuActive = true;
                    while (librarianMenuActive && !exitProgram) {
                        cout << endl;
                        cout << "Librarian Options:" << endl;
                        cout << "1. Add User" << endl;
                        cout << "2. Delete User" << endl;
                        cout << "3. Add Book" << endl;
                        cout << "4. Delete Book" << endl;
                        cout << "5. Print all Users" << endl;
                        cout << "6. Print all Books" << endl;
                        cout << "7. See Pending Requests" << endl;
                        cout << "8. Logout" << endl;
                        cout << "0 to exit" << endl;
                        cin >> x;

                        switch (x) {
                            case 1: u1.adduser(); break;
                            case 2: u1.deleteuser(); break;
                            case 3: b1.addbook(); break;
                            case 4: b1.deletebook(); break;
                            case 5: u1.printallusers(); break;
                            case 6: b1.allbooks(); break;
                            case 7: seependingrequests(); break;
                            case 8: librarianMenuActive = false; break;
                            case 0: exitProgram = true; break;
                            default: cout << "Invalid option. Please try again." << endl; break;
                        }
                    }
                }
                break;

            case 3:
                if (userLogin()) {
                                    system("cls");
                                    showtime();
    cout << "\t\t\t\t\t\t User Menu" << endl << endl << endl << endl;
                    bool userMenuActive = true;
                    while (userMenuActive && !exitProgram) {
                        cout << endl;
                        cout << "User Options:" << endl;
                        cout << "1. See All Books" << endl;
                        cout << "2. Request to Issue Book" << endl;
                        cout << "3. Deposit Book" << endl;
                        cout << "4. My Books" << endl;
                        cout << "5. Logout" << endl;
                        cout << "0 to exit" << endl;
                        cin >> x;

                        switch (x) {
                            case 1: b1.allbooks(); break;
                            case 2: b1.issue(); break;
                            case 3: b1.deposit(); break;
                            case 4: mybooks(); break;
                            case 5: userMenuActive = false; break;
                            case 0: exitProgram = true; break;
                            default: cout << "Invalid option. Please try again." << endl; break;
                        }
                    }
                }
                break;

            case 0:
                exitProgram = true;
                break;

            default:
                cout << "Invalid option. Please try again." << endl;
                break;
        }
    }

    return 0;
}
