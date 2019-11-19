#include<iostream>
#include<algorithm>
#include<string.h>

#define _INIT_SIZE_ 100

using namespace std;

class Book_list;
class member_list;
class transaction;
class transaction_list;
class library;

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
    bool* copies; // Index is serial number;\
                    bool flag checks the availibility of corresponding copy

public:
    Book()
    {
        name[0] = author[0] = publisher[0] = '\0';
        id = -1, price = -1;
        num_copies = 0;
        copies = NULL;
    }

    Book(char* nm, char* a, char* pub, int id_book, int book_price)
    {
        strcpy(name, nm);
        strcpy(author, a);
        strcpy(publisher, pub);
        num_copies = 0;
        copies = NULL;
        id = id_book, price = book_price;
    }

    ~Book()
    {
        if(!copies) delete copies;
    }

    void reset(char* nm, char* a, char* pub, int id_book, int book_price)
    {
        strcpy(name, nm);
        strcpy(author, a);
        strcpy(publisher, pub);
        num_copies = 0;
        copies = NULL;
        id = id_book, price = book_price;
    }

    void add_copies(int additional)
    {
        int i = num_copies;
        num_copies += additional;
        int *temp = new bool[num_copies];

        if(copies) copy(copies, copies + i, temp);

        for(int j = i; j < num_copies; j++) temp[j] = true;

        delete copies; // Free the previously allocated memory
        copies = temp;
    }

    friend istream& operator>>(istream& stream, Book& a);


    friend class Book_list;
};

istream& operator>>(istream& stream, Book& a)
{
    cout << "Enter Book name: "; stream >> a.name; cin.get();
    cout << "Enter Author: "; stream >> a.author; cin.get();
    cout << "Enter publisher: "; stream >> a.publisher; cin.get();
    cout << "Enter book id: "; stream >> a.id;
    cout << "Enter price: "; stream >> a.price;

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

    member(char *n, char* eml, char* ad, char *type)
    {
        strcpy(name, n); strcpy(email, eml); strcpy(address, ad);
        memtype = type[0];

        if(memtype == 'F' | memtype == 'f') transact_limit = 10;
        else transact_limit = 2;

        issued = 0;
    }


    void reset(char *n, char* eml, char* ad, char *type)
    {
        strcpy(name, n); strcpy(email, eml); strcpy(address, ad);
        memtype = type[0];

        if(memtype == 'F' | memtype == 'f') transact_limit = 10;
        else transact_limit = 2;

        issued = 0;
    }

    friend class member_list;
    friend ostream& operator>>(ostream& stream, member& a);
};

ostream& operator>>(ostream& stream, member& a)
{
    cout << "Enter member id: "; stream >> a.id;
    cout << "Enter Book name: "; stream >> a.name; cin.get();
    cout << "Enter email: "; stream >> a.email; cin.get();
    cout << "Enter address: "; stream >> a.address; cin.get();
    cout << "Memner type: \n<1>Faculty\n<2>Student\nEnter type: "; int x; stream >> x;
    if(x == 1) a.transact_limit = 10;
    if(x == 2) a.transact_limit = 2;
    a.issued = 0;

    return stream;
}

class member_list{
    member list;
    int top;

public:
    member_list()
    {
        top = 0;
    }

    int find_indx(int ID)
    {
        for(int i = 0; i < top; i++) if(list[i].id == ID) return i;

        return -1;
    }

    void add()
    {
        cin >> list[a++];
    }

    void issue(int id)
    {
        int indx = find_indx(id);
        list[indx].issued = min(list[indx].issued + 1, list[indx].transaction_limit);
    }

    void return_b(int id)
    {
        int indx = find_indx(id);
        list[indx].issued = max(list[indx].issued - 1, 0);    
    }

    friend class library;
}


class Book_list
{
private:
    int max_limit;
    int top;
    Book* list;
    bool* issued_books; // Stores book-id of issued c

    int find_index(int ID)
    {
        for(int i = 0; i < top; i++) if(list[i].id == ID) return i;

        return -1;
    }

public:

    // Find the available serial_code for a perticular book
    int available_serial_code(int ID)
    {
        int indx = find_index(ID);

        if(indx == -1) return -1;

        Book& boc = list[indx]; // boc : book of concern

        for(int i = 0; i < boc.num_copies; i++) if(boc.copies[i]) return i;

        return -1;
    }

    Book_list()
    {
        top = 0;
        max_limit = _INIT_SIZE_;
        list = new Book[max_limit];
        issued_books = new Book[max_limit];
    }

    ~Book_list()
    {
        if(list) delete[] list;
        if(issued_books) delete[] issued_books;
    }

    void add_book()
    {
        // If current max_limit is insufficient\
        allocate more memory 
        if(top >= max_limit) 
        {
            max_limit += _INIT_SIZE_;
            Book* temp = new Book[max_limit];
            bool* btemp = new bool[max_limit];

            copy(list, list + top, temp);
            copy(issued_books, issued_books + top, btemp);

            delete[] list;
            delete[] issued_books;
            issued_books = btemp;
            list = temp;
        }

        issued_books[top] = false; cin >> list[top++];
    }

    void add_copies(int ID, int add) {
        int indx = find_index(ID);

        if(indx == -1) {cout << "Invalid Book-ID!!!" << endl; return;}

        else list[indx].add_copies(add);
    }

    void issue_copy(int ID, int sl)
    {
        int indx = find_index(ID);
        list[indx].copies[sl] = false;
    }

    void return_copy(int ID, int sl)
    {
        int indx = find_index(ID);
        lisy[indx].copies[sl] = true;
    }

    friend class library;
};


class transaction
{
    int student_id, book_id, serial;
    bool returned;

public:
    transaction(int sid, int bid)
    {
        student_id = sid;
        book_id = bid;
        returned = false; // Issue request
    }

    transaction(int sid, int bid, int sl)
    {
        student_id = sid;
        book_id = bid;
        returned = false;
        serial = sl;
    }

    friend class transaction;
    friend ostream& operator>>(ostream& stream, transaction& a);
    friend class library;
};

ostream& operator>>(ostream& stream, transaction& a)
{
    cout << "Transaction type: \n<1>Issue\n<2>Return";
    cout << "Enter type: ";
    int x; cin >> x;

    if(x == 1)
    {
        cout << "Student id: "; stream >> a.student_id;
        cout << "Book id: "; stream >> a.book_id;
        a.returned = false;
    }

    else{
        cout << "Student id: "; stream >> a.student_id;
        cout << "Book id: "; stream >> a.book_id;
        cout << "Serial Number: "; stream >> a.serial;
        a.returned = true;
        a.returned = false;   
    }

    return stream;
}

class transaction_list{
    transaction list[_INIT_SIZE_];
    Date dlist[_INIT_SIZE_];
    int top;

public:
    transaction_list()
    {
        top = 0;
    }

    void find_index(transaction& a)
    {
        a.returned = false;
        for(int i = 0; i < top; i++) if(list[i] == a) return i;
        return -1;
    }

    void add(transaction& a)
    {
        list[top] = a;
        cin >> dlist[top++];
    }

    void modify(transaction& a)
    {
        int indx = find_index(a);

        if(indx == -1) {cout << "Invalid transaction details!!\n"; return;}

        list[indx].returned = true;
        cin >> dlist[indx];
    }

    friend class library;
}

class library
{
    member_list m;
    Book_list b;
    transaction_list t;
public:

    void add_member()
    {
        m.add();
    }

    void Add_book()
    {
        b.add_book();
    }

    void Add_copies()
    {
        int id; cout << "Enter Book_ID: "; cin >> id;
        int cp; cout << "Enter number of copies you want to add: "; cin >> cp;
        b.add_copies(id, cp); 
    }

    void transact()
    {
        transaction a;
        cin >> a;

        if(a.returned == false)
        {
            int mi = m.find_index(a.student_id);
            int bi = b.find_index(a.book_id);

            if(mi == -1) {
                cout << "Invalid member info!!\n"; return;
            }

            if(bi == -1)
            {
                cout << "Invalid book info!!\n"; return;
            }

            if(m[mi].issue_limit >= m[mi].issued)
            {
                cout << "Member issue limit exeeced!!\n";
                return;
            }
            int sr = b.available_serial_code(a.book_id);
            if(sr == -1)
            {
                cout << "No copies available!!\n";
            }

            a.serial = sl;
            b.issue_book(a.book_id, a.serial);
            t.add(a);
            m.issue(a.student_id);
        }

        else{
            t.modify(a);
            b.return_copy(a.book_id, a.serial);
            m.return_b(a.student_id);
        }
    }
    
};

int main()
{
    return 0;
}