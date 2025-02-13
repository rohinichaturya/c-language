#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for train details
struct Train {
    int trainNo;
    char trainName[50];
    char source[50];
    char destination[50];
    int seatsAvailable;
};

// Structure for passenger details
struct Passenger 
{
    int ticketNo;
    char name[50];
    int age;
    int trainNo;
};

// Function prototypes
void addTrain();
void displayTrains();
void bookTicket();
void displayPassengers();
void searchPassenger();
void cancelTicket();
void loadTrains();
void saveTrains();
void savePassenger(struct Passenger);
void loadPassengers();

FILE *fp;
struct Train trains[100];      // Maximum 100 trains
struct Passenger passengers[100]; // Maximum 100 passengers
int trainCount = 0;            // Track number of trains
int passengerCount = 0;        // Track number of passengers

// Main Menu
int main() 
{
    int choice;
    loadTrains();
    loadPassengers();

    while (1) {
        printf("\n===== Railway Reservation System =====\n");
        printf("1. Add Train Details\n");
        printf("2. Display Train Details\n");
        printf("3. Book Ticket\n");
        printf("4. View Passenger Details\n");
        printf("5. Search Passenger\n");
        printf("6. Cancel Ticket\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1: addTrain(); break;
            case 2: displayTrains(); break;
            case 3: bookTicket(); break;
            case 4: displayPassengers(); break;
            case 5: searchPassenger(); break;
            case 6: cancelTicket(); break;
            case 7:
                printf("Exiting Railway Reservation System...\n");
                exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}

// Load train details from file
void loadTrains() 
{
    fp = fopen("trains.dat", "rb");
    if (fp == NULL) return;

    while (fread(&trains[trainCount], sizeof(struct Train), 1, fp)) 
    {
        trainCount++;
    }
    fclose(fp);
}

// Save train details to file
void saveTrains()
{
    fp = fopen("trains.dat", "wb");
    for (int i = 0; i < trainCount; i++) 
    {
        fwrite(&trains[i], sizeof(struct Train), 1, fp);
    }
    fclose(fp);
}

// Load passenger details from file
void loadPassengers() {
    fp = fopen("passengers.dat", "rb");
    if (fp == NULL) return;

    while (fread(&passengers[passengerCount], sizeof(struct Passenger), 1, fp)) 
    {
        passengerCount++;
    }
    fclose(fp);
}

// Save passenger details to file
void savePassenger(struct Passenger passenger) 
{
    fp = fopen("passengers.dat", "ab");
    fwrite(&passenger, sizeof(struct Passenger), 1, fp);
    fclose(fp);
}

// Add train details
void addTrain() 
{
    struct Train train;
    printf("\nEnter Train Number: ");
    scanf("%d", &train.trainNo);
    getchar();
    printf("Enter Train Name: ");
    fgets(train.trainName, 50, stdin);
    train.trainName[strcspn(train.trainName, "\n")] = 0;
    printf("Enter Source Station: ");
    fgets(train.source, 50, stdin);
    train.source[strcspn(train.source, "\n")] = 0;
    printf("Enter Destination Station: ");
    fgets(train.destination, 50, stdin);
    train.destination[strcspn(train.destination, "\n")] = 0;
    printf("Enter Available Seats: ");
    scanf("%d", &train.seatsAvailable);

    trains[trainCount++] = train;
    saveTrains();

    printf("Train Added Successfully!\n");
}

// Display all train details
void displayTrains() 
{
    printf("\n===== Train List =====\n");
    for (int i = 0; i < trainCount; i++) {
        printf("Train No: %d | Name: %s | From: %s | To: %s | Seats Available: %d\n",
               trains[i].trainNo, trains[i].trainName, trains[i].source,
               trains[i].destination, trains[i].seatsAvailable);
    }
}

// Book a train ticket
void bookTicket() {
    int trainNo, found = 0;
    struct Passenger passenger;
    
    printf("\nEnter Train Number to Book Ticket: ");
    scanf("%d", &trainNo);
    
    for (int i = 0; i < trainCount; i++) {
        if (trains[i].trainNo == trainNo && trains[i].seatsAvailable > 0) 
        {
            passenger.ticketNo = passengerCount + 1;
            getchar();
            printf("Enter Passenger Name: ");
            fgets(passenger.name, 50, stdin);
            passenger.name[strcspn(passenger.name, "\n")] = 0;
            printf("Enter Passenger Age: ");
            scanf("%d", &passenger.age);
            passenger.trainNo = trainNo;

            passengers[passengerCount++] = passenger;
            savePassenger(passenger);

            trains[i].seatsAvailable--;
            saveTrains();

            printf("Ticket Booked Successfully! Ticket No: %d\n", passenger.ticketNo);
            found = 1;
            break;
        }
    }
    
    if (!found) printf("Train not found or no available seats!\n");
}

// Display all passengers
void displayPassengers() 
{
    printf("\n===== Passenger List =====\n");
    for (int i = 0; i < passengerCount; i++) 
    {
        printf("Ticket No: %d | Name: %s | Age: %d | Train No: %d\n",
               passengers[i].ticketNo, passengers[i].name, passengers[i].age, passengers[i].trainNo);
    }
}

// Search passenger by ticket number
void searchPassenger() 
{
    int ticketNo, found = 0;
    printf("\nEnter Ticket Number to Search: ");
    scanf("%d", &ticketNo);

    for (int i = 0; i < passengerCount; i++) 
    {
        if (passengers[i].ticketNo == ticketNo) 
        {
            printf("Passenger Found!\nTicket No: %d | Name: %s | Age: %d | Train No: %d\n",
                   passengers[i].ticketNo, passengers[i].name, passengers[i].age, passengers[i].trainNo);
            found = 1;
            break;
        }
    }
    if (!found) printf("Passenger not found!\n");
}

// Cancel a booked ticket
void cancelTicket() 
{
    int ticketNo, found = 0;
    printf("\nEnter Ticket Number to Cancel: ");
    scanf("%d", &ticketNo);

    for (int i = 0; i < passengerCount; i++) 
    {
        if (passengers[i].ticketNo == ticketNo) 
        {
            for (int j = 0; j < trainCount; j++)
              {
                if (trains[j].trainNo == passengers[i].trainNo) 
                {
                    trains[j].seatsAvailable++;
                    break;
                }
            }

            for (int j = i; j < passengerCount - 1; j++) 
            {
                passengers[j] = passengers[j + 1];
            }
            passengerCount--;

            saveTrains();
            fp = fopen("passengers.dat", "wb");
            for (int j = 0; j < passengerCount; j++)
              {
                fwrite(&passengers[j], sizeof(struct Passenger), 1, fp);
            }
            fclose(fp);

            printf("Ticket Canceled Successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found) printf("Ticket not found!\n");
}
