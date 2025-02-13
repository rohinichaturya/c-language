#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100

// Structure to store user details
struct User 
{
    char name[50];
    int accountNumber;
    int pin;
    float balance;
    char transactions[100][50];
    int transactionCount;
};

// Global variables
struct User users[MAX_USERS];
int userCount = 0;

// Function prototypes
void registerUser();
void loginUser();
void atmMenu(int index);
void depositMoney(int index);
void withdrawMoney(int index);
void checkBalance(int index);
void viewTransactions(int index);
void saveToFile();
void loadFromFile();

int main() 
{
    int choice;
    loadFromFile();

    while (1) 
    {
        printf("\n===== ATM SYSTEM SIMULATION =====\n");
        printf("1. Register\n2. Login\n3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1: registerUser(); break;
            case 2: loginUser(); break;
            case 3: printf("Exiting ATM System...\n"); saveToFile(); exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}

// Load user data from file
void loadFromFile() 
{
    FILE *fp = fopen("atm_users.dat", "rb");
    if (fp == NULL) return;
    while (fread(&users[userCount], sizeof(struct User), 1, fp))
      {
        userCount++;
    }
    fclose(fp);
}

// Save user data to file
void saveToFile() 
{
    FILE *fp = fopen("atm_users.dat", "wb");
    for (int i = 0; i < userCount; i++)
      {
        fwrite(&users[i], sizeof(struct User), 1, fp);
    }
    fclose(fp);
}

// Register a new user
void registerUser() 
{
    struct User newUser;
    printf("\nEnter Name: ");
    getchar();
    fgets(newUser.name, 50, stdin);
    newUser.name[strcspn(newUser.name, "\n")] = 0;
  
    printf("Enter Account Number: ");
    scanf("%d", &newUser.accountNumber);
    
    printf("Set a 4-digit PIN: ");
    scanf("%d", &newUser.pin);
    
    newUser.balance = 0;
    newUser.transactionCount = 0;

    users[userCount++] = newUser;
    saveToFile();
    printf("Registration Successful! Please Login.\n");
}

// User login
void loginUser() 
{
    int accNum, pin;
    printf("\nEnter Account Number: ");
    scanf("%d", &accNum);
    printf("Enter PIN: ");
    scanf("%d", &pin);

    for (int i = 0; i < userCount; i++) 
    {
        if (users[i].accountNumber == accNum && users[i].pin == pin) 
        {
            printf("Login Successful! Welcome, %s\n", users[i].name);
            atmMenu(i);
            return;
        }
    }
    printf("Invalid Account Number or PIN!\n");
}

// ATM Menu
void atmMenu(int index) 
{
    int choice;
    while (1) 
    {
        printf("\n===== ATM MENU =====\n");
        printf("1. Deposit Money\n2. Withdraw Money\n3. Check Balance\n4. View Transactions\n5. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1: depositMoney(index); break;
            case 2: withdrawMoney(index); break;
            case 3: checkBalance(index); break;
            case 4: viewTransactions(index); break;
            case 5: printf("Logging out...\n"); return;
            default: printf("Invalid choice!\n");
        }
    }
}

// Deposit Money
void depositMoney(int index) 
{
    float amount;
    printf("\nEnter Amount to Deposit: ₹");
    scanf("%f", &amount);

    if (amount <= 0) 
    {
        printf("Invalid amount!\n");
        return;
    }

    users[index].balance += amount;
    sprintf(users[index].transactions[users[index].transactionCount++], "Deposited ₹%.2f", amount);
    saveToFile();
    printf("Deposit Successful! New Balance: ₹%.2f\n", users[index].balance);
}

// Withdraw Money
void withdrawMoney(int index) 
{
    float amount;
    printf("\nEnter Amount to Withdraw: ₹");
    scanf("%f", &amount);

    if (amount <= 0 || amount > users[index].balance) 
    {
        printf("Invalid amount or Insufficient Balance!\n");
        return;
    }

    users[index].balance -= amount;
    sprintf(users[index].transactions[users[index].transactionCount++], "Withdrew ₹%.2f", amount);
    saveToFile();
    printf("Withdrawal Successful! New Balance: ₹%.2f\n", users[index].balance);
}

// Check Balance
void checkBalance(int index) 
{
    printf("\nYour Current Balance: ₹%.2f\n", users[index].balance);
}

// View Transactions
void viewTransactions(int index)
{
    printf("\n===== TRANSACTION HISTORY =====\n");
    if (users[index].transactionCount == 0) 
    {
        printf("No transactions available.\n");
        return;
    }
    for (int i = 0; i < users[index].transactionCount; i++) 
    {
        printf("%d) %s\n", i + 1, users[index].transactions[i]);
    }
}
