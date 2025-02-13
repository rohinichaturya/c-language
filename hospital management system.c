#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for patient details
struct Patient 
{
    int id;
    char name[50];
    int age;
    char disease[50];
    char doctor[50];
};

// Function prototypes
void addPatient();
void displayPatients();
void searchPatient();
void assignDoctor();
void deletePatient();
void savePatient(struct Patient);
void loadPatients();

FILE *fp;
struct Patient patients[100];  // Maximum 100 patients
int patientCount = 0;          // Track number of patients

// Main Menu
int main() 
{
    int choice;
    loadPatients();

    while (1) 
{
        printf("\n===== Hospital Management System =====\n");
        printf("1. Add Patient\n");
        printf("2. Display Patients\n");
        printf("3. Search Patient\n");
        printf("4. Assign Doctor\n");
        printf("5. Delete Patient\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
{
            case 1: addPatient(); break;
            case 2: displayPatients(); break;
            case 3: searchPatient(); break;
            case 4: assignDoctor(); break;
            case 5: deletePatient(); break;
            case 6:
                printf("Exiting Hospital Management System...\n");
                exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}

// Load patients from file
void loadPatients() {
    fp = fopen("hospital.dat", "rb");
    if (fp == NULL) return;

    while (fread(&patients[patientCount], sizeof(struct Patient), 1, fp))
{
        patientCount++;
    }
    fclose(fp);
}

// Save patient to file
void savePatient(struct Patient patient) 
{
    fp = fopen("hospital.dat", "ab");
    fwrite(&patient, sizeof(struct Patient), 1, fp);
    fclose(fp);
}

// Add a new patient
void addPatient() 
{
    struct Patient patient;
    printf("\nEnter Patient ID: ");
    scanf("%d", &patient.id);
    getchar();
    printf("Enter Name: ");
    fgets(patient.name, 50, stdin);
    patient.name[strcspn(patient.name, "\n")] = 0;
    printf("Enter Age: ");
    scanf("%d", &patient.age);
    getchar();
    printf("Enter Disease: ");
    fgets(patient.disease, 50, stdin);
    patient.disease[strcspn(patient.disease, "\n")] = 0;
    strcpy(patient.doctor, "Not Assigned");

    patients[patientCount++] = patient;
    savePatient(patient);

    printf("Patient Added Successfully!\n");
}

// Display all patients
void displayPatients() 
{
    printf("\n===== Patient List =====\n");
    for (int i = 0; i < patientCount; i++) {
        printf("ID: %d | Name: %s | Age: %d | Disease: %s | Doctor: %s\n",
               patients[i].id, patients[i].name, patients[i].age,
               patients[i].disease, patients[i].doctor);
    }
}

// Search for a patient by ID
void searchPatient() {
    int id, found = 0;
    printf("\nEnter Patient ID to Search: ");
    scanf("%d", &id);

    for (int i = 0; i < patientCount; i++) 
{
        if (patients[i].id == id) 
{
            printf("Patient Found!\nID: %d | Name: %s | Age: %d | Disease: %s | Doctor: %s\n",
                   patients[i].id, patients[i].name, patients[i].age,
                   patients[i].disease, patients[i].doctor);
            found = 1;
            break;
        }
    }
    if (!found) printf("Patient not found!\n");
}

// Assign a doctor to a patient
void assignDoctor() 
{
    int id, found = 0;
    char doctor[50];
    printf("\nEnter Patient ID to Assign Doctor: ");
    scanf("%d", &id);
    getchar();
    printf("Enter Doctor Name: ");
    fgets(doctor, 50, stdin);
    doctor[strcspn(doctor, "\n")] = 0;

    for (int i = 0; i < patientCount; i++)
{
        if (patients[i].id == id) {
            strcpy(patients[i].doctor, doctor);
            found = 1;
            printf("Doctor Assigned Successfully!\n");
            break;
        }
    }

    if (!found) printf("Patient not found!\n");

    // Save updated data to file
    fp = fopen("hospital.dat", "wb");
    for (int i = 0; i < patientCount; i++)
{
        fwrite(&patients[i], sizeof(struct Patient), 1, fp);
    }
    fclose(fp);
}

// Delete a patient
void deletePatient() 
{
    int id, found = 0;
    printf("\nEnter Patient ID to Delete: ");
    scanf("%d", &id);

    for (int i = 0; i < patientCount; i++) 
{
        if (patients[i].id == id) 
{
            found = 1;
            for (int j = i; j < patientCount - 1; j++)
{
                patients[j] = patients[j + 1];
            }
            patientCount--;
            printf("Patient Deleted Successfully!\n");
            break;
        }
    }

    if (!found) printf("Patient not found!\n");

    // Save updated data to file
    fp = fopen("hospital.dat", "wb");
    for (int i = 0; i < patientCount; i++) 
{
        fwrite(&patients[i], sizeof(struct Patient), 1, fp);
    }
    fclose(fp);
}
