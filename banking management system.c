#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for bank account details
struct Account
{
    int accountNumber;
    char name[50];
    float balance;
};

// Function prototypes
void createAccount();
void displayAccounts();
void depositMoney();
void withdrawMoney();
void checkBalance();
void deleteAccount();
void saveAccount(struct Account);
void loadAccounts();

FILE *fp;
struct Account accounts[100];  // Maximum 100 accounts
int accountCount = 0;          // Track number of accounts

// Main Menu
int main()
{
    int choice;
    loadAccounts();

    while (1) 
{
        printf("\n===== Banking Management System =====\n");
        printf("1. Create Account\n");
        printf("2. Display All Accounts\n");
        printf("3. Deposit Money\n");
        printf("4. Withdraw Money\n");
        printf("5. Check Balance\n");
        printf("6. Delete Account\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
{
            case 1: createAccount(); break;
            case 2: displayAccounts(); break;
            case 3: depositMoney(); break;
            case 4: withdrawMoney(); break;
            case 5: checkBalance(); break;
            case 6: deleteAccount(); break;
            case 7: 
                printf("Exiting Banking System...\n");
                exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}

// Load accounts from file
void loadAccounts() 
{
    fp = fopen("bank.dat", "rb");
    if (fp == NULL) return;

    while (fread(&accounts[accountCount], sizeof(struct Account), 1, fp)) {
        accountCount++;
    }
    fclose(fp);
}

// Save account to file
void saveAccount(struct Account account)
{
    fp = fopen("bank.dat", "ab");
    fwrite(&account, sizeof(struct Account), 1, fp);
    fclose(fp);
}

// Create a new account
void createAccount() 
{
    struct Account account;
    printf("\nEnter Account Number: ");
    scanf("%d", &account.accountNumber);
    getchar();
    printf("Enter Account Holder Name: ");
    fgets(account.name, 50, stdin);
    account.name[strcspn(account.name, "\n")] = 0; // Remove newline
    printf("Enter Initial Deposit: ");
    scanf("%f", &account.balance);

    accounts[accountCount++] = account;
    saveAccount(account);

    printf("Account Created Successfully!\n");
}

// Display all accounts
void displayAccounts() {
    printf("\n===== Account List =====\n");
    for (int i = 0; i < accountCount; i++)
{
        printf("Account No: %d | Name: %s | Balance: %.2f\n",
               accounts[i].accountNumber, accounts[i].name, accounts[i].balance);
    }
}

// Deposit money
void depositMoney()
{
    int accNo, found = 0;
    float amount;
    printf("\nEnter Account Number to Deposit Money: ");
    scanf("%d", &accNo);
    printf("Enter Amount to Deposit: ");
    scanf("%f", &amount);

    for (int i = 0; i < accountCount; i++) 
{
        if (accounts[i].accountNumber == accNo) 
{
            accounts[i].balance += amount;
            found = 1;
            printf("Deposit Successful! New Balance: %.2f\n", accounts[i].balance);
            break;
        }
    }

    if (!found) printf("Account not found!\n");

    // Save updated data to file
    fp = fopen("bank.dat", "wb");
    for (int i = 0; i < accountCount; i++) 
{
        fwrite(&accounts[i], sizeof(struct Account), 1, fp);
    }
    fclose(fp);
}

// Withdraw money
void withdrawMoney() 
{
    int accNo, found = 0;
    float amount;
    printf("\nEnter Account Number to Withdraw Money: ");
    scanf("%d", &accNo);
    printf("Enter Amount to Withdraw: ");
    scanf("%f", &amount);

    for (int i = 0; i < accountCount; i++) 
{
        if (accounts[i].accountNumber == accNo)
{
            if (accounts[i].balance >= amount) 
{
                accounts[i].balance -= amount;
                printf("Withdrawal Successful! New Balance: %.2f\n", accounts[i].balance);
            } else {
                printf("Insufficient Balance!\n");
            }
            found = 1;
            break;
        }
    }

    if (!found) printf("Account not found!\n");

    // Save updated data to file
    fp = fopen("bank.dat", "wb");
    for (int i = 0; i < accountCount; i++) 
    {
        fwrite(&accounts[i], sizeof(struct Account), 1, fp);
    }
    fclose(fp);
}

// Check account balance
void checkBalance()
{
    int accNo, found = 0;
    printf("\nEnter Account Number to Check Balance: ");
    scanf("%d", &accNo);

    for (int i = 0; i < accountCount; i++)
      {
        if (accounts[i].accountNumber == accNo) 
        {
            printf("Account No: %d | Name: %s | Balance: %.2f\n",
                   accounts[i].accountNumber, accounts[i].name, accounts[i].balance);
            found = 1;
            break;
        }
    }
    if (!found) printf("Account not found!\n");
}

// Delete an account
void deleteAccount() 
{
    int accNo, found = 0;
    printf("\nEnter Account Number to Delete: ");
    scanf("%d", &accNo);

    for (int i = 0; i < accountCount; i++) 
    {
        if (accounts[i].accountNumber == accNo)
        {
            found = 1;
            for (int j = i; j < accountCount - 1; j++)
              {
                accounts[j] = accounts[j + 1];
            }
            accountCount--;
            printf("Account Deleted Successfully!\n");
            break;
        }
    }

    if (!found) printf("Account not found!\n");

    // Save updated data to file
    fp = fopen("bank.dat", "wb");
    for (int i = 0; i < accountCount; i++) 
    {
        fwrite(&accounts[i], sizeof(struct Account), 1, fp);
    }
    fclose(fp);
}
