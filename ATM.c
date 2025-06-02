#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 100

typedef struct {
    int accountNumber;
    char name[50];
    float balance;
} Account;

void createAccount(Account *accounts, int *accountCount);
void checkBalance(Account *accounts, int accountCount);
void deposit(Account *accounts, int accountCount);
void withdraw(Account *accounts, int accountCount);
void saveAccountsToFile(Account *accounts, int accountCount);
void loadAccountsFromFile(Account *accounts, int *accountCount);

int main() {
    Account accounts[MAX_ACCOUNTS];
    int accountCount = 0;
    int choice;

    loadAccountsFromFile(accounts, &accountCount);

    do {
        printf("\nATM Simulation\n");
        printf("1. Create Account\n");
        printf("2. Check Balance\n");
        printf("3. Deposit Money\n");
        printf("4. Withdraw Money\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createAccount(accounts, &accountCount);
                break;
            case 2:
                checkBalance(accounts, accountCount);
                break;
            case 3:
                deposit(accounts, accountCount);
                break;
            case 4:
                withdraw(accounts, accountCount);
                break;
            case 5:
                saveAccountsToFile(accounts, accountCount);
                printf("Thank you for using the ATM!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

void createAccount(Account *accounts, int *accountCount) {
    if (*accountCount >= MAX_ACCOUNTS) {
        printf("Account limit reached!\n");
        return;
    }

    Account newAccount;
    newAccount.accountNumber = *accountCount + 1;
    printf("Enter name: ");
    scanf("%s", newAccount.name);
    newAccount.balance = 0.0;

    accounts[*accountCount] = newAccount;
    (*accountCount)++;

    printf("Account created successfully! Account Number: %d\n", newAccount.accountNumber);
}

void checkBalance(Account *accounts, int accountCount) {
    int accountNumber;
    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            printf("Account Number: %d\n", accounts[i].accountNumber);
            printf("Name: %s\n", accounts[i].name);
            printf("Balance: %.2f\n", accounts[i].balance);
            return;
        }
    }

    printf("Account not found!\n");
}

void deposit(Account *accounts, int accountCount) {
    int accountNumber;
    float amount;
    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            printf("Enter amount to deposit: ");
            scanf("%f", &amount);
            accounts[i].balance += amount;
            printf("Amount deposited successfully!\n");
            return;
        }
    }

    printf("Account not found!\n");
}

void withdraw(Account *accounts, int accountCount) {
    int accountNumber;
    float amount;
    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            printf("Enter amount to withdraw: ");
            scanf("%f", &amount);
            if (amount > accounts[i].balance) {
                printf("Insufficient balance!\n");
            } else {
                accounts[i].balance -= amount;
                printf("Amount withdrawn successfully!\n");
            }
            return;
        }
    }

    printf("Account not found!\n");
}

void saveAccountsToFile(Account *accounts, int accountCount) {
    FILE *file = fopen("accounts.txt", "w");
    if (file == NULL) {
        printf("Error saving accounts to file!\n");
        return;
    }for (int i = 0; i < accountCount; i++) {
        fprintf(file, "%d %s %.2f\n", accounts[i].accountNumber, accounts[i].name, accounts[i].balance);
    }

    fclose(file);
    printf("Accounts saved to file successfully!\n");
}

void loadAccountsFromFile(Account *accounts, int *accountCount) {
    FILE *file = fopen("accounts.txt", "r");
    if (file == NULL) {
        printf("No existing accounts to load.\n");
        return;
    }

    while (fscanf(file, "%d %s %f", &accounts[*accountCount].accountNumber, accounts[*accountCount].name, &accounts[*accountCount].balance) != EOF) {
        (*accountCount)++;
    }

    fclose(file);
    printf("Accounts loaded from file successfully!\n");
}
