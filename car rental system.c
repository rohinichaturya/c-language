#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARS 100
#define MAX_CUSTOMERS 100

// Structure to store car details
struct Car 
{
    int id;
    char name[50];
    float pricePerDay;
    int available; // 1 = available, 0 = rented
};

// Structure to store customer rental details
struct Rental 
{
    int carId;
    char customerName[50];
    int days;
    float totalCost;
};

// Global variables
struct Car cars[MAX_CARS];
struct Rental rentals[MAX_CUSTOMERS];
int carCount = 0, rentalCount = 0;

// Function prototypes
void addCar();
void displayCars();
void rentCar();
void returnCar();
void viewRentals();
void saveToFile();
void loadFromFile();

int main()
{
    int choice;
    loadFromFile();

    while (1)
      {
        printf("\n===== CAR RENTAL SYSTEM =====\n");
        printf("1. Add Car\n2. Display Cars\n3. Rent a Car\n4. Return Car\n5. View Rentals\n6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1: addCar(); break;
            case 2: displayCars(); break;
            case 3: rentCar(); break;
            case 4: returnCar(); break;
            case 5: viewRentals(); break;
            case 6: printf("Exiting System...\n"); saveToFile(); exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}

// Load data from file
void loadFromFile() 
{
    FILE *fp = fopen("cars.dat", "rb");
    if (fp != NULL) 
    {
        fread(&carCount, sizeof(int), 1, fp);
        fread(cars, sizeof(struct Car), carCount, fp);
        fclose(fp);
    }
    fp = fopen("rentals.dat", "rb");
    if (fp != NULL) 
    {
        fread(&rentalCount, sizeof(int), 1, fp);
        fread(rentals, sizeof(struct Rental), rentalCount, fp);
        fclose(fp);
    }
}

// Save data to file
void saveToFile() 
{
    FILE *fp = fopen("cars.dat", "wb");
    fwrite(&carCount, sizeof(int), 1, fp);
    fwrite(cars, sizeof(struct Car), carCount, fp);
    fclose(fp);

    fp = fopen("rentals.dat", "wb");
    fwrite(&rentalCount, sizeof(int), 1, fp);
    fwrite(rentals, sizeof(struct Rental), rentalCount, fp);
    fclose(fp);
}

// Add a new car
void addCar() 
{
    if (carCount >= MAX_CARS) 
    {
        printf("Car storage full!\n");
        return;
    }
    struct Car newCar;
    newCar.id = carCount + 1;
    getchar(); // Clear input buffer
    printf("Enter Car Name: ");
    fgets(newCar.name, 50, stdin);
    newCar.name[strcspn(newCar.name, "\n")] = 0;
    printf("Enter Price per Day: ₹");
    scanf("%f", &newCar.pricePerDay);
    newCar.available = 1; // Initially available

    cars[carCount++] = newCar;
    saveToFile();
    printf("Car Added Successfully!\n");
}

// Display all available cars
void displayCars() 
{
    printf("\n===== AVAILABLE CARS =====\n");
    if (carCount == 0)
    {
        printf("No cars available.\n");
        return;
    }
    for (int i = 0; i < carCount; i++) 
    {
        if (cars[i].available) 
        {
            printf("ID: %d | Car: %s | Price/Day: ₹%.2f\n", cars[i].id, cars[i].name, cars[i].pricePerDay);
        }
    }
}

// Rent a car
void rentCar() 
{
    int id, days;
    char name[50];

    displayCars();
    printf("Enter Car ID to Rent: ");
    scanf("%d", &id);
    getchar();
    printf("Enter Your Name: ");
    fgets(name, 50, stdin);
    name[strcspn(name, "\n")] = 0;
    printf("Enter Number of Days: ");
    scanf("%d", &days);

    for (int i = 0; i < carCount; i++)
      {
        if (cars[i].id == id && cars[i].available) 
        {
            cars[i].available = 0;
            rentals[rentalCount].carId = id;
            strcpy(rentals[rentalCount].customerName, name);
            rentals[rentalCount].days = days;
            rentals[rentalCount].totalCost = days * cars[i].pricePerDay;
            rentalCount++;

            saveToFile();
            printf("Car Rented Successfully! Total Cost: ₹%.2f\n", rentals[rentalCount - 1].totalCost);
            return;
        }
    }
    printf("Car not available!\n");
}

// Return a rented car
void returnCar() 
{
    int id, found = 0;
    printf("Enter Car ID to Return: ");
    scanf("%d", &id);

    for (int i = 0; i < rentalCount; i++) 
    {
        if (rentals[i].carId == id) 
        {
            found = 1;
            printf("\n===== RETURN RECEIPT =====\n");
            printf("Customer: %s\nCar ID: %d\nDays Rented: %d\nTotal Cost: ₹%.2f\n",
                   rentals[i].customerName, rentals[i].carId, rentals[i].days, rentals[i].totalCost);

            // Mark car as available
            for (int j = 0; j < carCount; j++) 
            {
                if (cars[j].id == id) 
                {
                    cars[j].available = 1;
                    break;
                }
            }

            // Remove rental record by shifting
            for (int j = i; j < rentalCount - 1; j++) 
            {
                rentals[j] = rentals[j + 1];
            }
            rentalCount--;
            saveToFile();
            printf("Car Returned Successfully!\n");
            return;
        }
    }
    if (!found) 
    {
        printf("Car not found in rentals!\n");
    }
}

// View all rentals
void viewRentals() 
{
    printf("\n===== ACTIVE RENTALS =====\n");
    if (rentalCount == 0) 
    {
        printf("No cars are currently rented.\n");
        return;
    }
    for (int i = 0; i < rentalCount; i++) 
    {
        printf("Car ID: %d | Customer: %s | Days: %d | Total Cost: ₹%.2f\n",
               rentals[i].carId, rentals[i].customerName, rentals[i].days, rentals[i].totalCost);
    }
}
