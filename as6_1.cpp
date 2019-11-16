#include<iostream>
#include<algorithm>
#include<string.h>
#include<fstream>

#define _INIT_SIZE_ 100

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
private:
    char name[50], author[50], publisher[50];
    int id, price;
    int num_copies;
    bool copies[_INIT_SIZE_]; // Index is serial number;\
                    bool flag checks the availibility of corresponding copy

public:
    Book() : id(-1), price(-1), num_copies(0)
    {
        name[0] = author[0] = publisher[0] = '\0';
        id = -1, price = -1;
        num_copies = 0;
        for(int i = 0; i < _INIT_SIZE_; i++) copies[i] = true;
    }

    Book(char* nm, char* a, char* pub, int id_book, int book_price) : id(id_book), price(book_price), num_copies(0)
    {
        strcpy(name, nm);
        strcpy(author, a);
        strcpy(publisher, pub);
        for(int i = 0; i < _INIT_SIZE_; i++) copies[i] = true;
    }

    ~Book() {}

    void add_copies(int additional)
    {
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
    friend class BookListInterface;
};

istream& operator>>(istream& stream, Book& a)
{
    cout << "\n\t\tEnter book details:\n";
    cout << "Enter Book name: "; stream >> a.name; cin.get();
    cout << "Enter Author: "; stream >> a.author; cin.get();
    cout << "Enter publisher: "; stream >> a.publisher; cin.get();
    cout << "Enter book id: "; stream >> a.id;
    cout << "Enter price: "; stream >> a.price;
    cout << "\n";

    return stream;
}


class member{
private:
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
        if(transact_limit <= issued) return false; 

        else {issued++; return true;}
    }


    bool Return()
    {
        if(issued <= 0) return false;
        else {issued--; return true;}
    }

    friend class MemberListInterface;
    friend istream& operator>>(istream& stream, member& a);
};

istream& operator>>(istream& stream, member& a)
{
    cout << "Enter member id: "; stream >> a.id;
    cout << "Enter Member name: "; stream >> a.name; cin.get();
    cout << "Enter email: "; stream >> a.email; cin.get();
    cout << "Enter address: "; stream >> a.address; cin.get();
    cout << "Member type: \n<1>Faculty\n<2>Student\nEnter type: "; int x; stream >> x;
    if(x == 1) a.transact_limit = 10;
    if(x == 2) a.transact_limit = 2;
    a.issued = 0;

    return stream;
}



class transaction
{
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
    friend class library;
};

istream& operator>>(istream& stream, transaction& a)
{
    cout << "Transaction type: \n<1>Issue Request?\n<2>Return Request?";
    cout << "Enter type: ";
    int x; cin >> x;

    if(x == 1)
    {
        cout << "Student id: "; stream >> a.member_id;
        cout << "Book id: "; stream >> a.book_id;
        a.returned = false;
    }

    else{
        cout << "Student id: "; stream >> a.member_id;
        cout << "Book id: "; stream >> a.book_id;
        cout << "Serial Number: "; stream >> a.serial;
        a.returned = true;
        a.returned = false;   
    }

    return stream;
}


class BookListInterface{
private:
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

        while(!searchStream.eof())
        {
            offset++;
            Book a;
            searchStream.read((char *) &a, sizeof(Book));

            if(a.id == book_id) {searchStream.close(); return offset;}
        }

        searchStream.close();
        return -1;
    }


    void add_book()
    {
        ofstream appendStream(FILE_NAME, ios::app | ios::binary);

        Book a; cin >> a;
        appendStream.write((char *) &a, sizeof(Book));
        appendStream.close();
    }

    int issue(int offset)
    {
        fstream modifyStream(FILE_NAME, ios::in | ios::out | ios::binary);

        Book a;
        modifyStream.seekg(offset, ios::beg);
        modifyStream.read((char *)&a, sizeof(Book));
        int serial = a.available_copy();

        modifyStream.seekp(offset, ios::beg);
        modifyStream.write((char *) &a, sizeof(Book));
        modifyStream.close();
        return serial;
    }

    bool Return(int offset, int serial)
    {
        fstream modifyStream(FILE_NAME, ios::in | ios::out | ios::binary);
        Book a;
        modifyStream.seekg(offset, ios::beg);
        modifyStream.read((char *)&a, sizeof(Book));

        bool done = a.Return(serial);
        modifyStream.seekp(offset, ios::beg);
        modifyStream.write((char *) &a, sizeof(Book));
        modifyStream.close();
        return done;
    }
};

class MemberListInterface{
private:
    char FILE_NAME[50];

public:
    MemberListInterface(const char* name){
        strcpy(FILE_NAME, name);
        fstream createStream(FILE_NAME, ios::out | ios::in | ios::binary);
        createStream.close();
    }

    void add_member(){
        member a; cin >> a;

        ofstream addStream(FILE_NAME, ios::app | ios::binary);
        addStream.write((char *)&a, sizeof(member));
        addStream.close();
    }

    int find_member(int id){
        ifstream searchStream(FILE_NAME, ios::in | ios::binary);

        member a; int offset = -1;
        while(!searchStream.eof())
        {
            offset++;
            searchStream.read((char *)&a, sizeof(member));
            if(a.id == id) {
                searchStream.close();
                return offset;
            }
        }

        searchStream.close(); return -1;
    }

    bool issue(int offset)
    {
        fstream modifyStream(FILE_NAME, ios::in | ios::out | ios::binary);

        member a;
        modifyStream.seekg(offset, ios::beg);
        modifyStream.read((char *)&a, sizeof(member));

        int ans = a.issue();
        modifyStream.seekp(offset, ios::beg);
        modifyStream.write((char *)&a, sizeof(member));
        modifyStream.close();
        return ans;
    }

    bool Return(int offset)
    {
        fstream modifyStream(FILE_NAME, ios::in | ios::out | ios::binary);

        member a;
        modifyStream.seekg(offset, ios::beg);
        modifyStream.read((char *)&a, sizeof(member));

        int ans = a.Return();
        modifyStream.seekp(offset, ios::beg);
        modifyStream.write((char *)&a, sizeof(member));
        modifyStream.close();
        return ans;
    }
};

class TransactionListInterface{
private:
    char FILE_NAME[50];
public:
    TransactionListInterface(const char* name){
        strcpy(FILE_NAME, name);
        fstream createStream(FILE_NAME, ios::out | ios::in | ios::binary);
        createStream.close();
    }

    void add(transaction& a){
        ofstream addStream(FILE_NAME, ios::app | ios::binary);
        addStream.write((char *)&a, sizeof(transaction));
        addStream.close();
    }

    int find(transaction& a){
        ifstream findStream(FILE_NAME, ios::in | ios::binary);

        int offset = -1;
        while(!findStream.eof()){
            offset++;
            transaction b;
            findStream.read((char *)&b, sizeof(transaction));

            if(a == b) {
                findStream.close();
                return offset;
            }
        }
        findStream.close();
        return -1;
    }

    bool Return(int offset)
    {
        bool ans = false;
        fstream findStream(FILE_NAME, ios::in | ios::out | ios::binary);
        transaction a;
        findStream.seekg(offset, ios::beg);
        findStream.read((char *)&a, sizeof(transaction));
        if(!a.returned) {a.returned = true; ans = true;}
        findStream.seekp(offset, ios::beg);
        findStream.write((char *)&a, sizeof(transaction));

        findStream.close();
        return ans;
    }
};


class Library{

};

int main()
{
    BookListInterface a("books.bin");
    MemberListInterface b("members.bin");
    TransactionListInterface c("transactions.bin");

    return 0;
}
