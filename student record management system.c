#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for student details
struct Student {
    int id;
    char name[50];
    int age;
    char course[50];
    float marks;
};

// Function prototypes
void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();
void saveStudent(struct Student);
void loadStudents();

FILE *fp;
struct Student students[100];  // Maximum 100 students
int studentCount = 0;          // Track number of students

// Main Menu
int main() {
    int choice;
    loadStudents();

    while (1) {
        printf("\n===== Student Record Management System =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6:
                printf("Exiting Student Record System...\n");
                exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}

// Load students from file
void loadStudents() {
    fp = fopen("students.dat", "rb");
    if (fp == NULL) return;

    while (fread(&students[studentCount], sizeof(struct Student), 1, fp)) {
        studentCount++;
    }
    fclose(fp);
}

// Save student to file
void saveStudent(struct Student student) {
    fp = fopen("students.dat", "ab");
    fwrite(&student, sizeof(struct Student), 1, fp);
    fclose(fp);
}

// Add a new student
void addStudent() {
    struct Student student;
    printf("\nEnter Student ID: ");
    scanf("%d", &student.id);
    getchar();
    printf("Enter Name: ");
    fgets(student.name, 50, stdin);
    student.name[strcspn(student.name, "\n")] = 0; // Remove newline
    printf("Enter Age: ");
    scanf("%d", &student.age);
    getchar();
    printf("Enter Course: ");
    fgets(student.course, 50, stdin);
    student.course[strcspn(student.course, "\n")] = 0; // Remove newline
    printf("Enter Marks: ");
    scanf("%f", &student.marks);

    students[studentCount++] = student;
    saveStudent(student);

    printf("Student Added Successfully!\n");
}

// Display all students
void displayStudents() {
    printf("\n===== Student List =====\n");
    for (int i = 0; i < studentCount; i++) {
        printf("ID: %d | Name: %s | Age: %d | Course: %s | Marks: %.2f\n",
               students[i].id, students[i].name, students[i].age,
               students[i].course, students[i].marks);
    }
}

// Search for a student by ID
void searchStudent() {
    int id, found = 0;
    printf("\nEnter Student ID to Search: ");
    scanf("%d", &id);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            printf("Student Found!\nID: %d | Name: %s | Age: %d | Course: %s | Marks: %.2f\n",
                   students[i].id, students[i].name, students[i].age,
                   students[i].course, students[i].marks);
            found = 1;
            break;
        }
    }
    if (!found) printf("Student not found!\n");
}

// Update student details
void updateStudent() {
    int id, found = 0;
    printf("\nEnter Student ID to Update: ");
    scanf("%d", &id);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            getchar();
            printf("Enter New Name: ");
            fgets(students[i].name, 50, stdin);
            students[i].name[strcspn(students[i].name, "\n")] = 0;
            printf("Enter New Age: ");
            scanf("%d", &students[i].age);
            getchar();
            printf("Enter New Course: ");
            fgets(students[i].course, 50, stdin);
            students[i].course[strcspn(students[i].course, "\n")] = 0;
            printf("Enter New Marks: ");
            scanf("%f", &students[i].marks);
            found = 1;
            printf("Student Record Updated Successfully!\n");
            break;
        }
    }

    if (!found) printf("Student not found!\n");

    // Save updated data to file
    fp = fopen("students.dat", "wb");
    for (int i = 0; i < studentCount; i++) {
        fwrite(&students[i], sizeof(struct Student), 1, fp);
    }
    fclose(fp);
}

// Delete a student
void deleteStudent() {
    int id, found = 0;
    printf("\nEnter Student ID to Delete: ");
    scanf("%d", &id);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            found = 1;
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }
            studentCount--;
            printf("Student Deleted Successfully!\n");
            break;
        }
    }

    if (!found) printf("Student not found!\n");

    // Save updated data to file
    fp = fopen("students.dat", "wb");
    for (int i = 0; i < studentCount; i++) {
        fwrite(&students[i], sizeof(struct Student), 1, fp);
    }
    fclose(fp);
}
