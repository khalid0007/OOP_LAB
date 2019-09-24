#include<iostream>
#include<string.h>
using namespace std;
class subject;
class details;
class student
{
	char name[20];
	int roll,no[10];
	public:
		student(char* s,int r,int *a)
		{
			strcpy(name,s);
			roll=r;
			for(int i=0;i<10;i++)
			no[i]=a[i];
		}
		
		friend class details;
		friend class subject;
		
};

class subject
{
	char sub_name[15];
	int code;
	public:
		subject(char*s ,int c)
		{
			strcpy(sub_name,s);
			code=c;
		}
		
		friend class details;
		friend class student;
		
};

class details
{
	int students_for_subject[5][5];
	int subjects_for_student[5][5];
	public:
		details()
		{
			for(int i=0;i<5;i++)
			{
				for(int j=0;j<5;j++)
				{
					students_for_subject[i][j]=-1;
					subjects_for_student[i][j]=-1;
				}
			}
		}
		void update(int* a,int x,int sz)
		{
			for(int i=0;i<sz;i++)
			{
				for(int j=0;j<5;j++)
				{
			
				if(subjects_for_student[x][j]==-1)
				{
				subjects_for_student[x][j]=a[i];
				break;
				}
				
				}
				
				for(int j=0;j<5;j++)
				{
					if(students_for_subject[a[i]][j]==-1)
					{
					students_for_subject[a[i]][j]=x;
					break;
					}
					
				}
			}
			
			
		}
		void update2(int sub,int* a,int sz)
		{
				
				for(int i=0;i<sz;i++){
				
				for(int j=0;j<5;j++)
				{
					if(students_for_subject[sub][j]==-1)
					{
					students_for_subject[sub][j]=a[i];
					break;
					}
					
				}
				
				
				
				for(int j=0;j<5;j++)
				{
			
				if(subjects_for_student[a[i]][j]==-1)
				{
				subjects_for_student[a[i]][j]=sub;
				break;
				}
				
				}
			}
		}
		void display()
		{
			for(int i=0;i<5;i++)
			{
				cout<<"subjects for student with roll "<<i+1<<" ";
				for(int j=0;j<5;j++)
				{
					if(subjects_for_student[i][j]==-1)
					break;
					
					cout<<subjects_for_student[i][j]<<" ";
				}
				cout<<endl;
			}
			
			for(int i=0;i<5;i++)
			{
				cout<<"students for subject with code "<<i+1<<" ";
				for(int j=0;j<5;j++)
				{
					if(students_for_subject[i][j]==-1)
					break;
					
					cout<<students_for_subject[i][j]<<" ";
				}
				cout<<endl;
			}
		}
};
int main()
{
	
}
