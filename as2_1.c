#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
    // We will set roll to -1 if want to delete data logically
    int roll;
    char name[30];
    int marks[5];
    int deleted;
} student;

student* __init__(student *x)
{
    printf("Enter Student Name: ");
    scanf("%[^\n]s", x->name);
    getchar();

    printf("Enter Roll: ");
    scanf("%d", &x->roll);
    getchar();

    printf("Enter Subjectwise Score: ");

    int i = 0;
    
    for(i; i < 5; ++i) {scanf("%d", (x->marks + i)); getchar();}

    // Set deleted to false
    x->deleted = 0;

    return x;
}


void append(void)
{
    FILE *fp = fopen("list.txt", "r+");

    fseek(fp, 0, SEEK_END);

    student *temp = __init__((student*)malloc(sizeof(student)));

    fwrite(temp, sizeof(student), 1, fp);

    free(temp);

    printf("\n\nData successfully added to list.......\n");
    printf("Press enter to continue.....\n");
    getchar();
    fclose(fp);
}

void delete()
{
	FILE *fp = fopen("list.txt","r+");
	
    if(fp == NULL)
	{
		fclose(fp);
		printf("File is empty.\n");
		return ;
	}
    
    int del_option;
    int success = 0;
    

    printf("**********DELETE OPTION**********\n");
    printf("\t<1> Delete permanently.\n");
    printf("\t<2> Delete logically. \n");

    printf("Enter choice: "); scanf("%d", &del_option); getchar();

    int roll_ref;

    fseek(fp, 0, SEEK_SET);

    student temp;

    if(del_option == 1)
    {
        printf("\nEnter roll to be deleted: "); scanf("%d", &roll_ref); getchar();
        FILE *fp1 = fopen("temp.txt", "w+");
        while(fread(&temp, sizeof(student), 1, fp) != 0)
        {
            if(temp.roll == roll_ref) {success = 1; continue;}

            fwrite(&temp, sizeof(student), 1, fp1);
        }

        rewind(fp1);
        rewind(fp);


        fclose(fp);
        fp = fopen("list.txt", "w+");
        while(fread(&temp, sizeof(student), 1, fp1) != 0) fwrite(&temp, sizeof(student), 1, fp);

        fclose(fp1);
    }

    else if(del_option == 2)
    {
        printf("\nEnter roll to be deleted: "); scanf("%d", &roll_ref); getchar();
        while(fread(&temp, sizeof(student), 1, fp) != 0)
        {
            if(temp.roll == roll_ref && temp.deleted == 0)
            {
                temp.deleted = 1;
                fseek(fp, -1*sizeof(student), SEEK_CUR);
                fwrite(&temp, sizeof(student), 1, fp);
                success = 1;
                break;
            }
            else if(temp.roll == roll_ref && temp.deleted == 1) {success = -1; break;}
        }
    }

    else 
    {
        printf("\nUnsupported op-code...\n");
        fclose(fp);
        return;
    }

    fclose(fp);

    // Success report print
    if(success == 1) printf("\nItem successfully deleted...\n");

    else if(success == -1) printf("\nItem is already deleted...\n");

    else if(success == 0) printf("\nItem no longer exits in the file...\n");
}

void display_list(void)
{
    FILE *fp = fopen("list.txt", "r");

	if(fp == NULL)
	{
		fclose(fp);
		printf("File is empty.\n");
        printf("\n\nEnter any key to continue......\n");
        getchar();
		return ;
	}

    fseek(fp, 0, SEEK_SET);

    // Clear screen:
    // For linux, unix, mac
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    // For win32 & win64
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif

    int cnt = 0;

    printf("SL\tName\t\t\t\t\tRoll\tTotal_Marks\n");
    printf("_______________________________________________________________________\n");

    student temp;

    while(fread(&temp, sizeof(temp), 1, fp))
    {
        // If it's logically deleted continue;
        if(temp.deleted) continue;

        char name_temp[30];

        int i = 0, len = strlen(temp.name);
        for(i; i < 29; i++)
        {
            if(i < len) name_temp[i] = temp.name[i];
            else name_temp[i] = ' ';
        }

        name_temp[i] = '\0';
        len = 0;
        for(i = 0; i < 5; i++) len += temp.marks[i];

        fprintf(stdout, "<%d>%c\t%s\t\t%c%d\t%c%d\n",++cnt, 179, name_temp, 179, temp.roll, 179, len); 
    }

    // If list is virtually empty
    if(cnt == 0)
    {
        // Clear screen:
        // For linux, unix, mac
        #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
            system("clear");
        #endif

        // For win32 & win64
        #if defined(_WIN32) || defined(_WIN64)
            system("cls");
        #endif

        printf("\nList is empty...\n");
    }

    printf("\n\nEnter any key to continue......\n");
    getchar();
    fclose(fp);
}

void disp_student_info()
{
    FILE *fp = fopen("list.txt", "r");

    if(fp == NULL)
    {
        printf("List is empty!!\n");
        printf("\nPress Enter to continue!!\n");
        getchar();
    }

    int roll_inf;
    printf("Enter roll number: ");
    scanf("%d", &roll_inf);
    getchar();

    student temp;

    fseek(fp, 0, SEEK_SET);
    int cnt = 0;
    while(fread(&temp, sizeof(student), 1, fp))
    {
        if(temp.roll == roll_inf && temp.deleted == 0)
        {
            #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
                system("clear");
            #endif

            #if defined(_WIN32) || defined(_WIN64)
                system("cls");
            #endif

            printf("\n________________________Student_Info________________________\n");
            printf("Name: %s", temp.name);
            printf("\tRoll: %d", temp.roll);
            printf("\n________________________SubjectWise Marks________________________\n");

            char subs[5][30] = {"MATHEMATICS", "DS_ALGO", "OOP", "DIGITAL LOGIC", "COMPUTER_ORGANISATION"};
            int i = 0;
            for(i; i < 5; i++) 
                printf("%s: %d\n", subs[i], temp.marks[i]);

            printf("\n\nPress enter to continue....\n");
            getchar();
            fclose(fp);
            return;
        }

        cnt++;
    }

    if(cnt == 0)
    {
        printf("\nList is empty!!\n");
        printf("\n\nPress enter to continue....\n");
        getchar();
        fclose(fp);
        return;
    }

    else
    {
        printf("\nData don't exits in the list.\n");
        printf("\n\nPress enter to continue....\n");
        getchar();
        fclose(fp);
        return;
    }
}

void modify()
{
    FILE *fp = fopen("list.txt", "r+");

    if(fp == NULL)
    {
        fclose(fp);
        printf("List is empty!!\n");
        printf("Press Enter to continue.......\n");
        getchar();
    }


    int roll_mod;
    printf("Enter roll: "); scanf("%d", &roll_mod); getchar();

    student temp;
    while(fread(&temp, sizeof(student), 1, fp))
    {
        if(temp.roll == roll_mod)
        {
            printf("\n***********Modification options***********\n");
            printf("<1> Name Update\n");
            printf("<2> Marks Update\n");

            int choice;
            printf("Enter choice: ");
            scanf("%d", &choice); getchar();

            if(choice == 1)
            {
                printf("Enter modified name: ");
                scanf("%[^\n]s", temp.name);
                getchar();

                fseek(fp, -1*sizeof(student), SEEK_CUR);
                fwrite(&temp, sizeof(student), 1, fp);

                printf("\nData successfully updated!!\n");
                fclose(fp);
                return;
            }

            else if(choice == 2)
            {
                printf("Enter modified marks: ");
                int i = 0;
                for(i; i < 5; i++) {scanf("%d", &temp.marks[i]); getchar();}

                fseek(fp, -1*sizeof(student), SEEK_CUR);
                fwrite(&temp, sizeof(student), 1, fp);

                printf("\nData successfully updated!!\n");
                fclose(fp);
                return;
            }
        }

    }

    printf("Data don't exist in the list!!\n");
    fclose(fp);
}

// Return value indicates wheather we have to terminate the program or not
int operations(void)
{
    // Menu driven program
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif

    printf("\t\t\t\t****************<MENU>****************\n");

    printf("\t\t\t\tYou can perform following operations: \n");
    printf("\t\t\t\t\t<1> Insert new data\n");
    printf("\t\t\t\t\t<2> Delete data\n");
    printf("\t\t\t\t\t<3> Display List\n");
    printf("\t\t\t\t\t<4> Show student info\n");
    printf("\t\t\t\t\t<5> Edit data\n");
    printf("\t\t\t\t\t<6> Exit menu\n");


    int choice;
    int flag = 1;

    printf("\n\nENTER CHOICE: ");
    scanf("%d", &choice);
    getchar();

    switch (choice)
    {
        case 1:
            // Clear screen:
            // For linux, unix, mac
            #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
                system("clear");
            #endif

            // For win32 & win64
            #if defined(_WIN32) || defined(_WIN64)
                system("cls");
            #endif

            //FILE *fp = fopen("")

            append();
            break;
        case 2:
            // Clear screen:
            // For linux, unix, mac
            #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
                system("clear");
            #endif

            // For win32 & win64
            #if defined(_WIN32) || defined(_WIN64)
                system("cls");
            #endif

            delete();
            printf("\nPress enter to continue....\n");
            getchar();
            break;

        case 3:
            // Clear screen:
            // For linux, unix, mac
            #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
                system("clear");
            #endif

            // For win32 & win64
            #if defined(_WIN32) || defined(_WIN64)
                system("cls");
            #endif

            display_list();
            break;
        case 4:
            disp_student_info();
            break;
        case 5:
            modify();
            printf("\nPress Enter to continue...\n");
            getchar();
            break;

        case 6:
            flag = 0;
            break;

        default:
            printf("\nInvalid op-code...Press enter to try again....\n");
            getchar();
            break;
    }

    return flag;
}

int main()
{
    FILE *fp = fopen("list.txt", "r+");

    // If "list.txt" doesn't exist create it
    if(fp == NULL)
    {
        fclose(fp);
        fp = fopen("list.txt", "w+");
        fclose(fp);
    }

    while(operations());

    return 0;
}