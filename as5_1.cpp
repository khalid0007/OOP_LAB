  
#include<iostream>
#include<string.h>

#define __MAX_SIZE__ 20

using namespace std;

class student_list;
class subject_list;
class relation;

class student{
private:
	int roll;
	char name[30];
public:
	student() {roll = -1; name[0] = '\0';}
	student(int r, char* n)
	{
		roll = r;
		strcpy(name, n);
	}

	student(const student& a)
	{
		roll = a.roll;
		strcpy(name, a.name);
	}

	friend class student_list;
	friend class relation;
	friend ostream& operator<<(ostream& stream,const student& a);
};

ostream& operator<<(ostream& stream, const student& a)
{
	stream << "\t\tStudent Details\n" << "Name: " << a.name << "\n" << "Roll: " << a.roll << "\n";

	return stream;
}

class subject
{
public:
	int code;
	char name[30];
public:
	subject() {code = -1; name[0] = '\0';}
	subject(int c, char* n)
	{
		code = c;
		strcpy(name, n);
	}

	subject(const subject& s)
	{
		code = s.code;
		strcpy(name, s.name);
	}

	friend class subject_list;
	friend class relation;
	friend ostream& operator<<(ostream& stream,const subject& a);
};

ostream& operator<<(ostream& stream,const subject& a)
{
	stream << "\t\tSubject Details\n" << "Name: " << a.name << "\n" << "Sub-code: " << a.code << "\n";

	return stream;
}

class student_list{
private:
	int top;
	student l[__MAX_SIZE__];
public:
	student_list() {top = 0;}
	void insert(const student& a)
	{
		l[top++] = a;
	}

	void insert(int r, char* n)
	{
		l[top].roll = r;
		strcpy(l[top++].name, n);
	}

	student& operator[](int indx)
	{
		if(indx >= top) {cerr << "Index out of range!!"; return l[top+1];}

		else return l[indx]; 
	}

	friend class relation;
	friend ostream& operator<<(ostream& stream, student_list a);
};

ostream& operator<<(ostream& stream, student_list a)
{
	if(a.top == 0) {cout << "No student opted for corresponding subject!!\n"; return stream;}

	for(int i = 0; i < a.top; i++) stream << a[i] << "\n";

	return stream;
}


class subject_list{
private:
	int top;
	subject l[__MAX_SIZE__];
public:
	subject_list() {top = 0;}
	void insert(const subject& a)
	{
		l[top++] = a;
	}

	void insert(int c, char* n)
	{
		l[top].code = c;
		strcpy(l[top++].name, n);
	}

	subject operator[](int indx)
	{
		if(indx >= top) {cerr << "Index out of range!!"; return l[top+1];}

		else return l[indx]; 
	}

	friend class relation;
	friend ostream& operator<<(ostream& stream, subject_list a);
};

ostream& operator<<(ostream& stream, subject_list a)
{
	if(a.top == 0) {cout << "No subject opted!!\n"; return stream;}

	for(int i = 0; i < a.top; i++) stream << a[i] << "\n";

	return stream;
}



class relation{
	student_list stdl;
	subject_list subl;
	bool relate[__MAX_SIZE__][__MAX_SIZE__];

	int find_student(int roll)
	{
		for(int i = 0; i < stdl.top; i++) {
			if(stdl[i].roll == roll) return i;
		}

		cerr << "Student don't exist!!\n";
		return __MAX_SIZE__;
	}

	int find_subject(int code)
	{
		for(int i = 0; i < subl.top; i++)
		{
			if(subl[i].code == code) return i;
		}

		cerr << "Student don't exist!!\n";
		return __MAX_SIZE__;
	}

public:
	relation()
	{
		memset(relate, false, sizeof(relate));
	}

	void add_student(const student& s)
	{
		stdl.insert(s);
	}

	void add_subject(const subject& s)
	{
		subl.insert(s);
	}

	void opt(int std_roll, int sub_code)
	{
		int stdindx = find_student(std_roll);
		int subindx = find_subject(sub_code);

		if(subindx == __MAX_SIZE__) {cerr << "Can't find subject!!\n"; return;}
		if(stdindx == __MAX_SIZE__) {cerr << "Can't find student!!\n"; return;}

		relate[stdindx][subindx] = true;
		relate[subindx][stdindx] = true;
	}

	void show_student(int subcode)
	{
		int subindx = find_subject(subcode);

		if(subindx == __MAX_SIZE__) {cerr << "Can't find subject!!\n"; return;}

		student_list temp;

		for(int i = 0; i < stdl.top; i++)
		{
			if(relate[subindx][i]) temp.insert(stdl[i]);
		}

		cout << subl[subindx] << "Students choose this subject: \n";

		cout << temp;
	}

	void show_subject(int stdroll)
	{
		int stdindx = find_student(stdroll);

		if(stdindx == __MAX_SIZE__) {cerr << "Can't find student!!\n"; return;}

		subject_list temp;

		for(int i = 0; i < subl.top; i++)
		{
			if(relate[stdindx][i]) temp.insert(subl[i]);
		}

		cout << stdl[stdindx] << "Opted for subjects: \n";


		cout << temp;
	}
};

int main()
{
	int r;
	char name[30] = "Unknown";
	relation x;

	for(int i = 0; i < 5; i++)
		x.add_student(student(i+1, name));

	for(int i = 0; i < 5; i++)
		x.add_subject(subject(i+1, name));

	for(int i = 1; i < 6; i ++)
	{
		x.opt(i, 1);
	}

	x.show_student(1);

	return 0;
}
