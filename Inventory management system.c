#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for inventory item
struct Item 
{
    int id;
    char name[50];
    int quantity;
    float price;
};

// Function prototypes
void addItem();
void displayItems();
void searchItem();
void updateItem();
void deleteItem();
void loadItems();
void saveItems();

FILE *fp;
struct Item items[100];  // Maximum 100 items
int itemCount = 0;       // Track number of items

// Main Menu
int main() 
{
    int choice;
    loadItems();

    while (1) {
        printf("\n===== Inventory Management System =====\n");
        printf("1. Add Item\n");
        printf("2. Display Items\n");
        printf("3. Search Item\n");
        printf("4. Update Item\n");
        printf("5. Delete Item\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1: addItem(); break;
            case 2: displayItems(); break;
            case 3: searchItem(); break;
            case 4: updateItem(); break;
            case 5: deleteItem(); break;
            case 6:
                printf("Exiting Inventory System...\n");
                exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}

// Load items from file
void loadItems() 
{
    fp = fopen("inventory.dat", "rb");
    if (fp == NULL) return;

    while (fread(&items[itemCount], sizeof(struct Item), 1, fp)) 
    {
        itemCount++;
    }
    fclose(fp);
}

// Save items to file
void saveItems()
{
    fp = fopen("inventory.dat", "wb");
    for (int i = 0; i < itemCount; i++) {
        fwrite(&items[i], sizeof(struct Item), 1, fp);
    }
    fclose(fp);
}

// Add a new item
void addItem()
{
    struct Item item;
    printf("\nEnter Item ID: ");
    scanf("%d", &item.id);
    getchar();
    printf("Enter Item Name: ");
    fgets(item.name, 50, stdin);
    item.name[strcspn(item.name, "\n")] = 0;
    printf("Enter Quantity: ");
    scanf("%d", &item.quantity);
    printf("Enter Price: ");
    scanf("%f", &item.price);

    items[itemCount++] = item;
    saveItems();

    printf("Item Added Successfully!\n");
}

// Display all items
void displayItems()
{
    printf("\n===== Inventory Items =====\n");
    for (int i = 0; i < itemCount; i++) {
        printf("ID: %d | Name: %s | Quantity: %d | Price: %.2f\n",
               items[i].id, items[i].name, items[i].quantity, items[i].price);
    }
}

// Search for an item by ID
void searchItem() 
{
    int id, found = 0;
    printf("\nEnter Item ID to Search: ");
    scanf("%d", &id);

    for (int i = 0; i < itemCount; i++) 
    {
        if (items[i].id == id) 
        {
            printf("Item Found!\nID: %d | Name: %s | Quantity: %d | Price: %.2f\n",
                   items[i].id, items[i].name, items[i].quantity, items[i].price);
            found = 1;
            break;
        }
    }
    if (!found) printf("Item not found!\n");
}

// Update item details
void updateItem() {
    int id, found = 0;
    printf("\nEnter Item ID to Update: ");
    scanf("%d", &id);

    for (int i = 0; i < itemCount; i++) 
    {
        if (items[i].id == id) {
            getchar();
            printf("Enter New Name: ");
            fgets(items[i].name, 50, stdin);
            items[i].name[strcspn(items[i].name, "\n")] = 0;
            printf("Enter New Quantity: ");
            scanf("%d", &items[i].quantity);
            printf("Enter New Price: ");
            scanf("%f", &items[i].price);
            found = 1;
            printf("Item Updated Successfully!\n");
            break;
        }
    }

    if (!found) printf("Item not found!\n");
    saveItems();
}

// Delete an item
void deleteItem() 
{
    int id, found = 0;
    printf("\nEnter Item ID to Delete: ");
    scanf("%d", &id);

    for (int i = 0; i < itemCount; i++) 
    {
        if (items[i].id == id)
        {
            found = 1;
            for (int j = i; j < itemCount - 1; j++) 
            {
                items[j] = items[j + 1];
            }
            itemCount--;
            printf("Item Deleted Successfully!\n");
            break;
        }
    }

    if (!found) printf("Item not found!\n");
    saveItems();
}
