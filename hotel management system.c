#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROOMS 50

// Structure to store guest details
struct Guest 
{
    int roomNumber;
    char name[50];
    int days;
    float bill;
};

// Global variables
struct Guest hotel[MAX_ROOMS];
int guestCount = 0;

// Function prototypes
void bookRoom();
void checkOut();
void displayGuests();
void saveToFile();
void loadFromFile();
void generateBill(int index);

int main() 
{
    int choice;
    loadFromFile();

    while (1)
      {
        printf("\n===== HOTEL MANAGEMENT SYSTEM =====\n");
        printf("1. Book Room\n2. Check-Out Guest\n3. View Guests\n4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1: bookRoom(); break;
            case 2: checkOut(); break;
            case 3: displayGuests(); break;
            case 4: printf("Exiting System...\n"); saveToFile(); exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}

// Load data from file
void loadFromFile() 
{
    FILE *fp = fopen("hotel.dat", "rb");
    if (fp == NULL) return;
    while (fread(&hotel[guestCount], sizeof(struct Guest), 1, fp)) 
    {
        guestCount++;
    }
    fclose(fp);
}

// Save data to file
void saveToFile() 
{
    FILE *fp = fopen("hotel.dat", "wb");
    for (int i = 0; i < guestCount; i++) 
    {
        fwrite(&hotel[i], sizeof(struct Guest), 1, fp);
    }
    fclose(fp);
}

// Book a room
void bookRoom()
{
    struct Guest g;
    printf("\nEnter Room Number (1-%d): ", MAX_ROOMS);
    scanf("%d", &g.roomNumber);
    
    // Check if room is already booked
    for (int i = 0; i < guestCount; i++)
      {
        if (hotel[i].roomNumber == g.roomNumber) 
        {
            printf("Room is already booked!\n");
            return;
        }
    }

    getchar();  // Clear input buffer
    printf("Enter Guest Name: ");
    fgets(g.name, 50, stdin);
    g.name[strcspn(g.name, "\n")] = 0;
    printf("Enter Number of Days: ");
    scanf("%d", &g.days);

    // Calculate bill (Assuming ₹2000 per night)
    g.bill = g.days * 2000;
    
    hotel[guestCount++] = g;
    saveToFile();
    printf("Room %d Booked Successfully for %s!\n", g.roomNumber, g.name);
}

// Display guests
void displayGuests() 
{
    printf("\n===== CURRENT GUESTS =====\n");
    if (guestCount == 0) 
    {
        printf("No guests are currently staying.\n");
        return;
    }
    for (int i = 0; i < guestCount; i++) 
    {
        printf("Room: %d | Guest: %s | Days: %d | Bill: ₹%.2f\n",
               hotel[i].roomNumber, hotel[i].name, hotel[i].days, hotel[i].bill);
    }
}

// Generate Bill
void generateBill(int index) 
{
    printf("\n===== BILL RECEIPT =====\n");
    printf("Guest Name: %s\n", hotel[index].name);
    printf("Room Number: %d\n", hotel[index].roomNumber);
    printf("Days Stayed: %d\n", hotel[index].days);
    printf("Total Bill: ₹%.2f\n", hotel[index].bill);
}

// Check out a guest
void checkOut() 
{
    int room, found = 0;
    printf("\nEnter Room Number for Check-Out: ");
    scanf("%d", &room);

    for (int i = 0; i < guestCount; i++) 
    {
        if (hotel[i].roomNumber == room) 
        {
            generateBill(i);
            found = 1;
            // Shift remaining guests
            for (int j = i; j < guestCount - 1; j++) 
            {
                hotel[j] = hotel[j + 1];
            }
            guestCount--;
            printf("Guest Checked Out Successfully!\n");
            break;
        }
    }

    if (!found)
    {
        printf("Room not found!\n");
    }
    saveToFile();
}
