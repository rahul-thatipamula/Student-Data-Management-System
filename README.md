Overview:

The project is a simple student management system implemented in C. It allows users to perform various operations related to managing student data, such as adding new students, updating existing student details, removing students, and displaying student information.



Components of the Project:

Main Function (main):



The main function acts as the entry point of the program. It displays a menu of options for the user to choose from.

Users can select options such as adding a new student, updating existing student details, removing a student, displaying details of a single student, printing details of all students, and exiting the program.

The program utilizes a do-while loop to keep presenting the menu until the user chooses to exit.

Student Structure (s):



The s struct represents the details of a student, including attributes like roll number, student name, branch, date of birth, gender, course duration, mid-1 marks, mid-1 percentage, and attendance percentage.

Functions:



Add Student (add_student):



Prompts the user to enter details for a new student.

Validates the entered ID and checks if it already exists in the system.

Calculates the percentage of mid-1 marks and stores the student details in a CSV file named "student_bio_data.csv".

Allocates memory dynamically for storing student details.

Update Student (update_student):



Allows the user to update details of an existing student.

Prompts the user to enter the ID of the student to be updated and the details to be modified.

Updates the student's details in the CSV file.

Remove Student (remove_student):



Enables the user to remove a student from the system by providing the student's ID.

Deletes the student's details from the CSV file.

Display Student (display_student):



Displays details of a single student by prompting the user to enter the student's ID.

Searches for the student's details in the CSV file and prints them if found.

Display All Students (display_all_students):



Prints details of all students stored in the CSV file.

Others:



Functions like id_checking, processStudentData, allocate_memory, releaseMemory, noOfStudents, file_check, and colors are utility functions to perform specific tasks like input validation, file operations, memory allocation, etc.

File Operations:



The program reads and writes student data from/to a CSV file named "student_bio_data.csv".

It uses file handling functions like fopen, fclose, fgets, fprintf, etc., to perform file operations.






