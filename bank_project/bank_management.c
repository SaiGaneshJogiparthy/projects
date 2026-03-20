#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct account
{
    int accNo;
    char name[50];
    float balance;
    struct account *next;
};

struct account *head = NULL;

// SEARCH FUNCTION
struct account* search(int accNo)
{
    struct account *temp = head;

    while(temp != NULL)
    {
        if(temp->accNo == accNo)
            return temp;

        temp = temp->next;
    }
    return NULL;
}

// CREATE ACCOUNT
void createAccount()
{
    struct account *newAcc = (struct account*)malloc(sizeof(struct account));

    if(newAcc == NULL)
    {
        printf("Memory Allocation Failed\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &newAcc->accNo);

    if(search(newAcc->accNo) != NULL)
    {
        printf("Account already exists\n");
        free(newAcc);
        return;
    }

    printf("Enter Name: ");
    scanf(" %[^\n]", newAcc->name);

    printf("Enter Initial Balance: ");
    scanf("%f", &newAcc->balance);

    if(newAcc->balance < 0)
    {
        printf("Invalid Balance\n");
        free(newAcc);
        return;
    }

    newAcc->next = NULL;

    // Insert at END
    if(head == NULL)
    {
        head = newAcc;
    }
    else
    {
        struct account *temp = head;
        while(temp->next != NULL)
            temp = temp->next;

        temp->next = newAcc;
    }

    printf("Account Created Successfully\n");
}

// DEPOSIT
void deposit()
{
    int accNo;
    float amt;

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    struct account *acc = search(accNo);

    if(acc == NULL)
    {
        printf("Account Not Found\n");
        return;
    }

    printf("Enter Amount to Deposit: ");
    scanf("%f", &amt);

    if(amt <= 0)
    {
        printf("Invalid Amount\n");
        return;
    }

    acc->balance += amt;

    printf("Deposit Successful\n");
}

// WITHDRAW
void withdraw()
{
    int accNo;
    float amt;

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    struct account *acc = search(accNo);

    if(acc == NULL)
    {
        printf("Account Not Found\n");
        return;
    }

    printf("Enter Amount to Withdraw: ");
    scanf("%f", &amt);

    if(amt <= 0)
    {
        printf("Invalid Amount\n");
        return;
    }

    if(acc->balance < amt)
    {
        printf("Insufficient Balance\n");
        return;
    }

    acc->balance -= amt;

    printf("Withdrawal Successful\n");
}

// DISPLAY ALL ACCOUNTS
void display()
{
    struct account *temp = head;

    if(temp == NULL)
    {
        printf("No Accounts Available\n");
        return;
    }

    printf("\n----- Account List -----\n");

    while(temp != NULL)
    {
        printf("AccNo: %d | Name: %s | Balance: %.2f\n",
               temp->accNo, temp->name, temp->balance);

        temp = temp->next;
    }
}

// DELETE ACCOUNT
void deleteAccount()
{
    int accNo;
    printf("Enter Account Number to Delete: ");
    scanf("%d", &accNo);

    struct account *temp = head, *prev = NULL;

    while(temp != NULL)
    {
        if(temp->accNo == accNo)
        {
            if(prev == NULL)
                head = temp->next;
            else
                prev->next = temp->next;

            free(temp);
            printf("Account Deleted Successfully\n");
            return;
        }

        prev = temp;
        temp = temp->next;
    }

    printf("Account Not Found\n");
}

// MAIN FUNCTION
int main()
{
    int ch;

    while(1)
    {
        printf("\n===== BANK MANAGEMENT SYSTEM =====\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Search\n");
        printf("5. Display All\n");
        printf("6. Delete Account\n");
        printf("7. Exit\n");
        printf("Enter Choice: ");

        scanf("%d", &ch);

        switch(ch)
        {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;

            case 4:
            {
                int id;
                printf("Enter Account Number: ");
                scanf("%d", &id);

                struct account *acc = search(id);

                if(acc)
                    printf("Name: %s | Balance: %.2f\n", acc->name, acc->balance);
                else
                    printf("Account Not Found\n");

                break;
            }

            case 5: display(); break;
            case 6: deleteAccount(); break;
            case 7: 
                printf("Thank You\n");
                exit(0);

            default: printf("Invalid Choice\n");
        }
    }
}
