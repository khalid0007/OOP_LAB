#include<iostream>
#include<algorithm>
#include<string.h>
#include<fstream>

#define _INIT_SIZE_ 100
#define dbg(x) cout << #x << " = " << x << endl;

using namespace std;

class BookListInterface;
class MemberListInterface;
class TransactionListInterface;
class transaction;
class Library;

class Date{
public:
    int d, m, y;

    Date(int dd, int mm, int yy)
    {
        d = dd; m = mm; y = yy; 
    }

    friend istream& operator>>(istream& stream, Date& a);
    friend ostream& operator>>(ostream& stream, const Date& a);
};

istream& operator>>(istream& stream, Date& a) {cout << "Enter date (dd mm yyyy): "; stream >> a.d >> a.m >> a.y; return stream;}

ostream& operator>>(ostream& stream, const Date& a) {stream << "Date: " << a.d << "/" << a.m << "/" << a.y << endl; return stream;}


class Book{
protected:
    char name[50], author[50], publisher[50];
    int id, price;
    int num_copies;
    bool copies[_INIT_SIZE_]; // Index is serial number;\
                    bool flag checks the availibility of corresponding copy

public:
    Book() : id(-1), price(-1)
    {
        num_copies = 0;
        name[0] = author[0] = publisher[0] = '\0';
        for(int i = 0; i < _INIT_SIZE_; i++) copies[i] = true;
    }

    Book(char* nm, char* a, char* pub, int id_book, int book_price) : id(id_book), price(book_price)
    {
        num_copies = 0;
        strcpy(name, nm);
        strcpy(author, a);
        strcpy(publisher, pub);
        for(int i = 0; i < _INIT_SIZE_; i++) copies[i] = true;
    }

    ~Book() {}

    void add_copies(int additional)
    {
        // dbg(num_copies);
        if(_INIT_SIZE_ - num_copies >= additional) num_copies += additional;
        
        else cout << "No Space for additional copies!\n";
    }

    int available_copy() {
        for(int i = 0; i < num_copies; i++) if(copies[i]) {copies[i] = false; return i;}
        return -1;
    }

    bool Return(int serial)
    {
        if(serial >= num_copies) return false;

        if(!copies[serial]) {
            copies[serial] = true;
            return true;
        }

        else return false;
    }

    friend istream& operator>>(istream& stream, Book& a);
    friend ostream& operator<<(ostream& stream, const Book& a);
    friend class BookListInterface;
};

istream& operator>>(istream& stream, Book& a)
{
    cout << "\n\tEnter book details:\n";
    cout << "________________________________________\n";
    cout << "Enter Book name: "; stream >> a.name; cin.get();
    cout << "Enter Author: "; stream >> a.author; cin.get();
    cout << "Enter publisher: "; stream >> a.publisher; cin.get();
    cout << "Enter book id: "; stream >> a.id;
    cout << "Number of copies: "; stream >> a.num_copies;
    cout << "Enter price: "; stream >> a.price;
    cout << "\n";

    return stream;
}

ostream& operator<<(ostream& stream, const Book& a){
    cout << "\n\tBook Details\n";
    cout << "________________________________________\n";
    cout << "ID: " << a.id << "\tCopies: " << a.num_copies << endl;
    cout << "Author: " << a.author << endl;
    cout << "Name: " << a.name << endl;
    cout << "Publishers: " << a.publisher << endl;
}


class member{
protected:
    int id;
    char name[30], email[30], address[30];
    int transact_limit, issued;
    char memtype; // faculty = false for student
public:
    member()
    {
        name[0] = email[0] = address[0] = '\0';
        transact_limit = 0; issued = 0;
        memtype = 'U'; // U : unknown
    }

    member(char *n, char* eml, char* ad, char *type) : issued(0) 
    {
        strcpy(name, n); strcpy(email, eml); strcpy(address, ad);
        memtype = type[0];

        if(memtype == 'F' | memtype == 'f') transact_limit = 10;
        else transact_limit = 2;
    }

    bool issue()
    {
        if(issued >= transact_limit) return false; 

        else {issued++; return true;}
    }


    bool Return()
    {
        if(issued <= 0) return false;
        else {issued--; return true;}
    }

    friend class MemberListInterface;
    friend istream& operator>>(istream& stream, member& a);
    friend ostream& operator<<(ostream& stream, const member& a);
};

istream& operator>>(istream& stream, member& a)
{
    cout << "Enter member id: "; stream >> a.id;
    cout << "Enter Member name: "; stream >> a.name; cin.get();
    cout << "Enter email: "; stream >> a.email; cin.get();
    cout << "Enter address: "; stream >> a.address; cin.get();
    cout << "Member type: \n<1>Faculty\n<2>Student\nEnter type: "; int x; stream >> x;
    if(x == 1) {
        a.memtype = 'F';
        a.transact_limit = 10;
    }
    if(x == 2) {
        a.memtype = 'S';
        a.transact_limit = 2;
    }

    a.issued = 0;

    return stream;
}

ostream& operator<<(ostream& stream, const member& a){
    cout << "\n\t\t\tMember Details!!\n";
    cout << "_______________________________________________________________________\n";
    if(a.memtype == 'f' || a.memtype == 'F')
        cout << "Member Type: Faculty\t\t\t";
    else
        cout << "Member Type: Student\t\t\t";

    cout << "Member ID: " << a.id << endl;
    cout << "Name: " << a.name << "\t\t\t" << "E-mail: " << a.email << endl;
    cout << "Issued: " << a.issued << "\t\t\t\t" << "Transaction Limit: " << a.transact_limit << endl;    
}

class transaction
{
protected:
    int member_id, book_id, serial;
    bool returned;

public:
    transaction() : member_id(-1), book_id(-1), serial(-1), returned(false) {} 
    transaction(int mid, int bid) : member_id(mid), book_id(bid), returned(false), serial(-1) {}
    transaction(int mid, int bid, int sl) : member_id(mid), book_id(bid), returned(true), serial(sl) {}

    bool operator==(transaction& a)
    {return (member_id == a.member_id && book_id == a.member_id && serial == a.serial);}

    friend istream& operator>>(istream& stream, transaction& a);
    friend class TransactionListInterface;
    friend class Library;
};

istream& operator>>(istream& stream, transaction& a)
{
    cout << "Transaction type: \n<1>Issue Request?\n<2>Return Request?";
    cout << "\nEnter type: ";
    int x; stream >> x;

    if(x == 1)
    {
        cout << "Member id: "; stream >> a.member_id;
        cout << "Book id: "; stream >> a.book_id;
        a.returned = false;
    }

    else if(x == 2){
        cout << "Member id: "; stream >> a.member_id;
        cout << "Book id: "; stream >> a.book_id;
        cout << "Serial Number: "; stream >> a.serial;
        a.returned = true;
    }

    return stream;
}


class BookListInterface{
protected:
    char FILE_NAME[50];
public:
    BookListInterface(const char* name) {
        strcpy(FILE_NAME, name);
        fstream createStream(FILE_NAME, ios::out | ios::in | ios::binary);
        createStream.close();
    }

    // Returns file offset position of the object
    int find_book(int book_id){
        ifstream searchStream(FILE_NAME, ios::in | ios::binary);

        if(!searchStream) {
            cout << "Error while opening file!!\n";
            exit(1);
        }
        int offset = -1;

        Book a;
        while(searchStream.read((char *) &a, sizeof(Book)))
        {
            offset++;

            if(a.id == book_id) {searchStream.close(); return offset;}
        }

        searchStream.close();
        return -1;
    }


    void add_book()
    {
        ofstream appendStream(FILE_NAME, ios::app | ios::binary);

        Book a; cin >> a;
        // dbg(a);
        appendStream.write((char *) &a, sizeof(Book));
        appendStream.close();
    }

    void add_copies(int book_id, int additional)
    {
        fstream stream(FILE_NAME, ios::in | ios::out | ios::binary);

        int offset = find_book(book_id);

        Book a;

        stream.seekg(offset*sizeof(Book), ios::beg);
        stream.read((char *)&a, sizeof(Book));

        a.add_copies(additional);

        stream.seekp(offset*sizeof(Book), ios::beg);
        stream.write((char *)&a, sizeof(Book));

        stream.close();
    }

    int issue_b(int offset)
    {
        fstream modifyStream(FILE_NAME, ios::in | ios::out | ios::binary);

        Book a;
        modifyStream.seekg(offset*sizeof(Book), ios::beg);
        modifyStream.read((char *)&a, sizeof(Book));
        int serial = a.available_copy();

        modifyStream.seekp(offset*sizeof(Book), ios::beg);
        modifyStream.write((char *) &a, sizeof(Book));
        modifyStream.close();
        return serial;
    }

    bool Return_b(int offset, int serial)
    {
        fstream modifyStream(FILE_NAME, ios::in | ios::out | ios::binary);
        Book a;
        modifyStream.seekg(offset*sizeof(Book), ios::beg);
        modifyStream.read((char *)&a, sizeof(Book));

        bool done = a.Return(serial);
        modifyStream.seekp(offset*sizeof(Book), ios::beg);
        modifyStream.write((char *) &a, sizeof(Book));
        modifyStream.close();
        return done;
    }


    void read_file_b(){
        ifstream stream(FILE_NAME, ios::in | ios::binary);

        Book a;

        cout << "Reading book list: " << endl;
        while(stream.read((char *)&a, sizeof(Book))){
            cout << a << endl;
        }

        stream.close();
    }
};

class MemberListInterface{
protected:
    char FILE_NAME[50];

public:
    MemberListInterface(const char* name){
        strcpy(FILE_NAME, name);
        fstream createStream(FILE_NAME, ios::out | ios::in | ios::binary);
        createStream.close();
    }

    void add_member(){
        member a; cin >> a;

        // dbg(a);
        ofstream addStream(FILE_NAME, ios::app | ios::binary);
        addStream.write((char *)&a, sizeof(member));
        addStream.close();
    }

    int find_member(int id){
        ifstream searchStream(FILE_NAME, ios::in | ios::binary);

        member a; int offset = -1;
        while(searchStream.read((char *)&a, sizeof(member)))
        {
            offset++;

            if(a.id == id) {
                searchStream.close();
                return offset;
            }
        }

        searchStream.close(); return -1;
    }

    bool issue_m(int offset)
    {
        fstream modifyStream(FILE_NAME, ios::in | ios::out | ios::binary);

        member a;
        modifyStream.seekg(offset*sizeof(member), ios::beg);
        modifyStream.read((char *)&a, sizeof(member));

        int ans = a.issue();
        modifyStream.seekp(offset*sizeof(member), ios::beg);
        modifyStream.write((char *)&a, sizeof(member));
        modifyStream.close();
        return ans;
    }

    bool Return_m(int offset)
    {
        fstream modifyStream(FILE_NAME, ios::in | ios::out | ios::binary);

        member a;
        modifyStream.seekg(offset*sizeof(member), ios::beg);
        modifyStream.read((char *)&a, sizeof(member));

        int ans = a.Return();
        modifyStream.seekp(offset*sizeof(member), ios::beg);
        modifyStream.write((char *)&a, sizeof(member));
        modifyStream.close();
        return ans;
    }

    void read_file_m(){
        ifstream stream(FILE_NAME, ios::in | ios::binary);
        member b;

        cout << "Reading member files: " << endl;
        while(stream.read((char *)&b, sizeof(member))){
            cout << b << endl;
        }
    }
};

class TransactionListInterface{
protected:
    char FILE_NAME[50];
public:
    TransactionListInterface(const char* name){
        strcpy(FILE_NAME, name);
        fstream createStream(FILE_NAME, ios::out | ios::in | ios::binary);
        createStream.close();
    }

    void add_transaction(transaction& a){
        ofstream addStream(FILE_NAME, ios::app | ios::binary);
        addStream.write((char *)&a, sizeof(transaction));
        addStream.close();
    }

    int find_transaction(transaction& a){
        ifstream findStream(FILE_NAME, ios::in | ios::binary);

        int offset = -1;
        transaction b;
        while(findStream.read((char *)&b, sizeof(transaction))){
            offset++;
            
            if(a == b) {
                findStream.close();
                return offset;
            }
        }
        
        findStream.close();
        return -1;
    }

    bool Return_t(int offset)
    {
        bool ans = false;
        fstream findStream(FILE_NAME, ios::in | ios::out | ios::binary);
        transaction a;
        findStream.seekg(offset*sizeof(transaction), ios::beg);
        findStream.read((char *)&a, sizeof(transaction));
        if(!a.returned) {a.returned = true; ans = true;}
        findStream.seekp(offset*sizeof(transaction), ios::beg);
        findStream.write((char *)&a, sizeof(transaction));

        findStream.close();
        return ans;
    }
};



class Library : public TransactionListInterface, public MemberListInterface, public BookListInterface
{
public:
    Library(const char* BookFile, const char* MemberFile, const char* TransactionFile)
        : TransactionListInterface(TransactionFile), MemberListInterface(MemberFile), BookListInterface(BookFile) {}
    
    void transact(){
        transaction a;
        cin >> a;

        if(a.returned){
            int transact_offset = find_transaction(a);
            if(transact_offset == -1){
                cout << "Please check transaction details!!\n";
                return;
            }

            bool successful = Return_t(transact_offset);

            if(!successful){
                cout << "Already returned book!!\n";
                return;
            }

            else{
                int book_offset = find_book(a.book_id);
                int serial = a.serial;
                int member_offset = find_member(a.member_id);

                if(book_offset == -1 || member_offset == -1)
                {
                    cout << "Incorrect details!!\n";
                    return;
                }

                if(Return_b(book_offset, serial) && Return_m(member_offset)) {
                    cout << "Book successfully returned!!\n";
                    return;
                }

                else {
                    cout << "Wrong details!!\n";
                    return;
                }
            }
        }

        else{
            int book_id = a.book_id;
            int member_id = a.member_id;

            int member_offset = find_member(member_id);
            int book_offset = find_book(book_id);

            if(member_offset == -1){
                cout << "Please, check member details!!\n";
                return;
            }
            if(book_offset == -1){
                cout << "Please, check book details!!\n";
                return;
            }

            int serial = issue_b(book_offset);

            if(serial == -1){
                cout << "No copy of this book is available!!\n";
                return;
            }

            bool successful = issue_m(member_offset);

            if(!successful){
                Return_b(book_offset, serial);
                cout << "Your transaction limit exeeded!!\n";
                return;
            }

            else{
                a.serial = serial;
                add_transaction(a);
                cout << "Transaction successful!!\n";
                cout << "Book serial code is: " << serial << "\n";
                return;
            }
        }
    }

};

int main()
{
    Library a("books.bin", "members.bin", "transactions.bin");

    // for(int i = 0; i < 2; i++) a.add_book();

    a.read_file_b();

    return 0;
}
