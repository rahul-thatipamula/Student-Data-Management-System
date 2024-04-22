#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
void add_student();
void update_student();
void remove_student();
void display_student();
void display_all_students();
int noOfStudents();
void colors(int);
char *id_checking(char *);
void file_check(FILE *);
int processStudentData(char *, int, FILE *, FILE *);
typedef struct studentDetails
{
    char *rollNo;
    char *studentName;
    char *branch;
    char *dateOfBirth;
    char *gender;
    char *courseDuration;
    char *midMarks;
    char *midpercentage;
    char *attendancePercentage;
} s;
void releaseMemory(s *);
void allocate_memory(s *);
static int student_found = 0, i;
enum color
{
    red = 1,
    green,
    yellow,
    white
};
enum selection_process
{
    updateDetails = 1,
    display_all,
    display_single_student
};
void main()
{
    int choice;
 do{
        printf("\t\t\t\t\t\tSTUDENT DATA\n\n\n");
        printf("\t1. Add the student details\n");
        printf("\t2. update student details\n");
        printf("\t3. Remove student details\n");
        printf("\t4. Display student details\n");
        printf("\t5. Print all students data\n");
        printf("\t6. Exit\n\n");
        printf("Choose the option: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            add_student();
            system("cls");
            break;
        case 2:
            update_student();
            system("cls");
            break;
        case 3:
            remove_student();
            sleep(3);
            system("cls");
            break;
        case 4:
            display_student();
            break;

        case 5:
            display_all_students();
            break;
        case 6:
            exit(0);
        default:
            printf("Enter valid option\n");
        }
 }while(choice>0);
}
char *id_checking(char *id)
{
    int i;
    char *copied_id = (char *)malloc(7 * sizeof(char));
checking_id:
{
    if (i == 5)
    {
        printf("Too many wrong entries...\n");
        printf("Try again after some time\n");
        exit(0);
    }
    printf("Enter the ID of the student \t: ");
    fflush(stdin);
    fgets(id, 11, stdin);
}
    id[5] = toupper(id[5]);
    strncpy(copied_id, id, 6);

    copied_id[7] = '\0';
    if ((strlen(id) != 10) && ((strcmp(copied_id, "22311A") != 0) ||
                               (strcmp(copied_id, "22311A") == 0)))
    {
        printf("\t\t\t****Please enter 10 digit I'D Number****\n");
        i++;
        goto checking_id;
    }
    free(copied_id);
    return id;
}
void add_student()
{
    char *line = (char *)malloc(200 * sizeof(char));
    char *id = (char *)malloc(11);
    FILE *studentFile = fopen("student_bio_data.csv", "r");
    file_check(studentFile);
    fseek(studentFile, 0, 1);
    id_checking(id);
    fgets(line, 200, studentFile);
    while (fgets(line, 200, studentFile))
    {
        int len = strlen(line);
        line = realloc(line, (len * sizeof(char)));
        if (strcmp(id, strtok(line, ",")) == 0)
        {
            printf("Student Details already Exist\nRedirecting to main menu...\n");
            sleep(3);

            return;
        }
        free(line);
        char *line = (char *)malloc(200 * sizeof(char));
    }
    fclose(studentFile);
    s *student = (s *)malloc(sizeof(s));
    allocate_memory(student);
    strcpy(student->rollNo, id);
    studentFile = fopen("student_bio_data.csv", "a");
    file_check(studentFile);
    fseek(studentFile, 0, SEEK_END);
    printf("Enter student Name \t: ");
    fflush(stdin);
    gets(student->studentName);
    printf("Enter the Branch of the Student :");
    gets(student->branch);
    printf("Enter the DOB of the Student (DD/MM/YYYY) :");
    gets(student->dateOfBirth);
    printf("Gender \t\t:");
    gets(student->gender);
    printf("Enter course duration \t:");
    gets(student->courseDuration);
    printf("Enter mid-1 marks \t: ");
    gets(student->midMarks);
    printf("Enter attendance percentage \t: ");
    gets(student->attendancePercentage);

    float num;
    num = atoi(student->midMarks);
    num = (num / 120) * 100;
    fprintf(studentFile, "%s,%s,%s,%s,%s,%s,%s,%.2f,%s\n", student -> rollNo, student->studentName, student->branch, student->dateOfBirth, student -> gender, student->courseDuration, student->midMarks, num, student -> attendancePercentage);
    printf("\t\t\t****Data Entered sucessfully****\n\n");
    printf("Please wait redirecting to main menu.\n");
    releaseMemory(student);
    fclose(studentFile);
    free(id);
    sleep(3);
}
void display_student()
{
    student_found = 0;
    char *line = (char *)malloc(200);
    char *id = (char *)malloc(11);
    FILE *studentFile = fopen("student_bio_data.csv", "r");
    file_check(studentFile);
    fgets(line, 200, studentFile);
    free(line);
    if (studentFile == NULL)
    {
        printf("Failed to open file\n");
        exit(0);
    }
    id_checking(id);
    processStudentData(id, display_single_student, NULL, studentFile);

    if (student_found == 0)
        printf("!! Student details not found\n");
    fclose(studentFile);
    free(id);
    return;
}
void display_all_students()
{
    char *line = (char *)malloc(200);
    FILE *studentFile = fopen("student_bio_data.csv", "r");
    file_check(studentFile);
    fgets(line, 200, studentFile);
    free(line);
 printf("%10s %25s %8s %13s %10s %10s %9s %5s %9s", "ROLL NO","STUDENT NAME","BRANCH","DATE OF BIRTH","GENDER","COURSE DURATION","MID-1 MARKS","MID-%","ATTENDANCE %\n");
 processStudentData("\0",display_all,NULL,studentFile);
 colors(white);
 printf("\n\t\tTotal No. of students are : %d\n\n",noOfStudents());
 fclose(studentFile);
return ;
}
void remove_student()
{
    student_found = 0;
    char *id = (char *)malloc(11);
    char *line = (char *)malloc(200);

    FILE *studentFile = fopen("student_bio_data.csv", "r");
    file_check(studentFile);
    FILE *temp = fopen("temp.csv", "w");
    file_check(temp);
    id_checking(id);
    fgets(line, 200, studentFile);
    fprintf(temp, "%s", line);
    free(line);
    processStudentData(id, display_single_student, temp, studentFile);
    if (student_found != 0)
    {
        colors(red);
        printf("The above data is deleting please wait...\n");
        colors(white);
        sleep(2);
        printf("student with %s id has been deleted successfully\n", id);
        printf("Redirecting to main menu.\n");
        sleep(2);
    }
    else
        printf("Student details not found.\n");
    free(id);
    fclose(studentFile);
    fclose(temp);
    remove("student_bio_data.csv");
    rename("temp.csv", "student_bio_data.csv");
}

int processStudentData(char *roll, int x, FILE *temp, FILE *studentFile)
{
    char *line = (char *)malloc(200);
    char *readd = (char *)malloc(30);
    int count;
    int choice;
    while ((fgets(line, 200, studentFile)))
    {
        s *student = (s *)malloc(sizeof(*student));
        allocate_memory(student);
        strcpy(student->rollNo, strtok(line, ","));
        strcpy(student->studentName, strtok(NULL, ","));
        strcpy(student->branch, strtok(NULL, ","));
        strcpy(student->dateOfBirth, strtok(NULL, ","));
        strcpy(student->gender, strtok(NULL, ","));
        strcpy(student->courseDuration, strtok(NULL, ","));
        strcpy(student->midMarks, strtok(NULL, ","));
        strcpy(student->midpercentage, strtok(NULL, ","));
        strcpy(student->attendancePercentage, strtok(NULL, ","));
        if (x == display_all)
        {
            colors(yellow);
            printf("%10s %24s %8s %13s %10s %10s %10s %10s %10s", student -> rollNo, student->studentName, student->branch, student->dateOfBirth, student -> gender, student->courseDuration, student->midMarks, student -> midpercentage, student->attendancePercentage);
        }
        if ((strcmp(student->rollNo, roll) != 0) && temp != NULL)
            fprintf(temp, "%s,%s,%s,%s,%s,%s,%s,%s,%s", student->rollNo, student -> studentName, student->branch, student->dateOfBirth, student->gender, student -> courseDuration, student->midMarks, student->midpercentage, student -> attendancePercentage);

        if (strcmp(student->rollNo, roll) == 0)
        {
            student_found++;
            if (x == updateDetails || x == display_single_student)
            {
                colors(green);
                printf("_____________________________________\n");
                colors(white);
                printf("|Roll No : %s\n", student->rollNo);
                printf("|Student Name : %s\n", student->studentName);
                printf("|Branch : %s\n", student->branch);
                printf("|Date of Birth : %s\n", student->dateOfBirth);
                printf("|Gender : %s\n", student->gender);
                printf("|Course duration : %s\n", student->courseDuration);
                printf("|Mid-1 marks : %s\n", student->midMarks);
                printf("|mid-1 percentage : %s\n", student->midpercentage);
                printf("|attendance percentage: %s\n", student -> attendancePercentage);
                colors(green);
                printf("--------------------------------------\n");
                colors(white);
                if (x == updateDetails)
                {
                    printf("\t\t1. Name \n\t\t2. branch\n\t\t3. date of birth\n\t\t4. gender\n\t\t 5. course_ duratuon\n\t\t6. mid marks\n\t\t7. attendance :\n");
                    printf("Select the option to edit : \n");
                    fflush(stdin);
                    scanf("%d", &choice);
                    switch (choice)
                    {
                    case 1:
                        printf("Enter the name: ");
                        fflush(stdin);

                        gets(student->studentName);
                        break;
                    case 2:
                        printf("Enter the branch: ");
                        fflush(stdin);
                        gets(student->branch);
                        break;
                    case 3:
                        printf("Enter the date of birth ");
                        fflush(stdin);
                        gets(student->dateOfBirth);
                        break;
                    case 4:
                        printf("Enter the gender: ");
                        fflush(stdin);
                        gets(student->gender);
                        break;
                    case 5:
                        printf("Enter the course duration ");
                        fflush(stdin);
                        gets(student->courseDuration);
                        break;
                    case 6:
                        printf("Enter the mid marks ");
                        fflush(stdin);
                        gets(student->midMarks);
                        break;
                    case 7:
                        printf("Enter the attendance");
                        fflush(stdin);
                        gets(student->attendancePercentage);
                        break;

                    default:
                        i++;
                        printf("Entered invalid option.\n");
                        sleep(3);
                        break;
                    }
                    fprintf(temp, "%s,%s,%s,%s,%s,%s,%s,%s,%s", student -> rollNo, student->studentName, student->branch, student->dateOfBirth, student -> gender, student->courseDuration, student->midMarks, student -> midpercentage, student->attendancePercentage);
                }
            }
        }
        free(line);
        char *line = (char *)malloc(200 * sizeof(char));
        releaseMemory(student);
    }
    return student_found;
}
void update_student()
{
    char *id = (char *)malloc(11);
    char *line = (char *)malloc(256);
    FILE *studentFile = fopen("student_bio_data.csv", "r");
    file_check(studentFile);
    FILE *temp = fopen("temp.csv", "w");
    file_check(temp);
    student_found = 0;

    i = 0;
    id_checking(id);
    fgets(line, 256, studentFile);
    fprintf(temp, "%s", line);
    free(line);
    processStudentData(id, updateDetails, temp, studentFile);
    if (student_found == 0)
    {
        printf("Student details not found\nRedirecting to main menu\n");
        sleep(2);
    }
    else
    {
        if (i == 0)
        {
            printf("Updating Student details");
            for (int i = 0; i < 3; i++)
            {
                sleep(i);
                printf(" .");
            }
            printf("\nUpdated successfully. Redirecting to main menu\n");
            sleep(2);
        }
    }
    free(id);
    fclose(studentFile);
    fclose(temp);
    remove("student_bio_data.csv");
    rename("temp.csv", "student_bio_data.csv");
    return;
}
void allocate_memory(s *student)
{
    student->rollNo = (s *)malloc(11);
    student->studentName = (s *)malloc(30);
    student->branch = (char *)malloc(8);
    student->dateOfBirth = (s *)malloc(11);
    student->gender = (s *)malloc(7);
    student->courseDuration = (s *)malloc(10);
    student->midMarks = (s *)malloc(4);
    student->midpercentage = (s *)malloc(4);
    student->attendancePercentage = (s *)malloc(4);
}
void releaseMemory(s *student)
{
    free(student->rollNo);
    free(student->studentName);
    free(student->branch);
    free(student->dateOfBirth);
    free(student->gender);
    free(student->courseDuration);
    free(student->midMarks);
    free(student->midpercentage);
    free(student->attendancePercentage);
    free(student);
}
int noOfStudents()
{

    int i = 0;
    char *line = (char *)malloc(200);
    FILE *studentFile = fopen("student_bio_data.csv", "r");
    fgets(line, 200, studentFile);
    while (fgets(line, 200, studentFile))
        i++;
    fclose(studentFile);
    return i;
}
void colors(int x)
{
    switch (x)
    {
    case 1:
        printf("\e[1;31m");
        break; // red
    case 2:
        printf("\e[0;32m");
        break; // green
    case 3:
        printf("\e[1;33m");
        break; // yellow
    case 4:
        printf("\e[0;37m");
        break; // white
    }
}
void file_check(FILE *ptr)
{
    if (ptr == NULL)
    {
        printf("Failed to open file\n");
        exit(0);
    }
    return;
}
