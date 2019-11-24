#include<conio.h>
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include <stdlib.h>
#include<windows.h>
#include<ctype.h>

struct Item
{
    char name[50];
    float rate;
    struct Node *next;
}*start;

struct FoodItem
{
    char username[20];
	int qty;
	float price;
	struct FoodItem *next;
	struct Item *item;
}*top=NULL;

struct Order
{
    float total;
    char username[20];
    struct Node *next;
}*rear,*front;


void ccolor(int clr){

	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, clr);
}

void spacing(char name[50], float price,int space)
{
    int x=0,intpart,i;
    while(name[x]!='\0')
    {
        space--;
        x++;
    }
    intpart = (int)price;
    while(intpart!=0)
    {
        space--;
        intpart /= 10;
    }
    for(i=1;i<=space;i++)
    {
        printf(" ");
    }
}


void loadingbar(void){

//Sleep(7000);
	for (int i=15;i<=100;i+=5){

		system("cls");
		ccolor(15);

		printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\t");
		printf("     Food Ordering System\n\n\t");
		printf("\t\t\t\t\t");
		printf("%d %% Loading...\n\n\t\t\t\t",i);

		printf("");

		for (int j=0; j<i;j+=2){

			ccolor(160);
			printf(" ");
			ccolor(15);

		}
		Sleep(50);
		if(i==90 || i==50 || i==96 || i==83){
			Sleep(50);
		}

	}
        ccolor(15);
}

void stringify(char name[100])
{
    int x=0;
    while(name[x]!='\0')
    {
        if(isalpha(name[x]))
            printf("%c",toupper(name[x]));
        else
            printf("%c",name[x]);
        printf(" ");
        x++;
    }
}

/* Menu Item Functions */
void createMenuItem()
{
    struct Item *newnode, *temp;
    char name[50];
    float rate;
    int i, n,x;
    system("cls");
    printf("\n\t\t\t\t\t============================================\n\t\t\t\t\t\t\tA D D   I T E M S\n\t\t\t\t\t============================================");
    printf("\n\n\t\t\tNo. of item to be created: ");
    scanf("%d", &n);
    for(i=1;i<=n;i++)
    {
        system("cls");
        printf("\n\t\t\t\t\t============================================\n\t\t\t\t\t\t\tI T E M # %d\n\t\t\t\t\t============================================",i);
       newnode = (struct Item *)malloc(sizeof(struct Item));
       printf("\n\n\t\t\t\t\t\tName of item: ");
       fflush(stdin);
       gets(name);
       x = 0;
       while(name[x]!='\0')
       {
           newnode -> name[x] = name[x];
           x++;
       }
       newnode->name[x]='\0';
       newnode->next = '\0';
       printf("\n\t\t\t\t\t\tRate: ");
       scanf("%f", &rate);
       newnode -> rate = rate;
       if(start == NULL)
            start = newnode;
       else
       {
           temp = start;
           while(temp->next!=NULL)
           {
                temp = temp -> next;
           }
            temp -> next = newnode;
       }
       displayMenu();
       ccolor(47);
       printf("\n\n\t\t\t\t\t\t\t%s added to menu!", name);
        ccolor(15);
        getch();
    }
}

void displayMenu()
{
    struct Item *temp;
    int i=1;
    temp = start;
    system("cls");
    printf("\n\t\t\t\t\t============================================\n\t\t\t\t\t\t\tM E N U\n\t\t\t\t\t============================================");
    printf("\n\t______________________________________________________________________________________________________");
    printf("\n\tSr. No.\t\tName\t\t\t\t\t\t\t\t\t\t  Rate");
    printf("\n\t______________________________________________________________________________________________________");
    while(temp!=NULL)
    {
        Sleep(20);
        printf("\n\t%d\t\t%s",i++,temp->name);
        spacing(temp->name,temp->rate,83);
        printf("%0.2f", temp->rate);
        temp = temp->next;
    }
    printf("\n\t______________________________________________________________________________________________________");
}

struct Item *searchItem(int n)
{
    int i=1,x;
    struct Item *temp;
    temp = start;
    while(temp!=NULL && i<n)
    {
        temp = temp->next;
        i++;
    }
    return temp;
}

void editItem()
{
    char name[50];
    int choice,x,flag=1,n;
    float rate;
    struct Item *temp;
    again:
    system("cls");
    displayMenu();
    if(flag==0)
    {
        ccolor(12);
        printf("\n\n\t\t\t\t\tPlease enter a valid choice\n");
        ccolor(15);
    }
    else
    {
        printf("\n");
    }
    printf("\n\t\t\t\t\t0. Cancel\n\n\t\t\t\t\tEnter sr. no. of item: ");
    scanf("%d",&n);
    if(n!=0)
    {
        temp = searchItem(n);
        if(temp!=NULL)
        {
            flag=1;
            printf("\n\t\t\t\t\t\tCurrently editing: ");
            ccolor(11);
            printf("%s",temp->name);
            ccolor(15);printf("\n\n\t\t\t\t\t\tWhich field do you want to edit?\n\t\t\t\t\t\t1. Name\n\t\t\t\t\t\t2. Rate\n\t\t\t\t\t\t0. Back\n\t\t\t\t\t\tEnter choice: ");
            scanf("%d",&choice);
            if(choice==1)
            {
                printf("\n\t\t\t\t\t\tEnter name:");
                fflush(stdin);
                gets(name);
                x = 0;
                while(name[x]!='\0')
                {
                   temp -> name[x] = name[x];
                   x++;
                }
                temp->name[x] = '\0';
            }
            else if(choice==2)
            {
                printf("\n\t\t\t\t\t\tEnter rate:");
                scanf("%f",&rate);
                temp -> rate = rate;
            }

            if(choice!=0)
            {
                goto again;
            }

        }
        else
        {
            flag=0;
            printf("\a");
            goto again;
        }
    }
}

void autoCreateMenu()
{
    int i,x;
    char names[10][20] = {"Salad","Soup","Fries","Pizza","Noodles","Cheesecake","Blackforest","Tea","Coffee","Water"};
    float rates[10] = {10,20,30,40,50,60,70,80,90,100};
    struct Item *newnode,*temp;
    for(i=0;i<10;i++)
    {
       newnode = (struct Item *)malloc(sizeof(struct Item));
       x = 0;
       while(names[i][x]!='\0')
       {
            newnode->name[x] = names[i][x];
           x++;
       }
       newnode->name[x]='\0';
       newnode->next='\0';
       newnode->rate = rates[i];
       if(start == NULL)
            start = newnode;
       else
       {
           temp = start;
           while(temp->next!=NULL)
           {
                temp = temp -> next;
           }
            temp -> next = newnode;
       }
    }
}


/* Cart Functions */

void pushFoodItem(char username[20])
{
    int p,n,q,x,flag=1;
    float r,s;
    struct FoodItem *temp, *newnode;
    again: system("cls");
    displayMenu();
    if(flag==0)
    {
        ccolor(12);
        printf("\n\n\t\t\t\t\tPlease enter a valid choice\n");
        ccolor(15);
    }
    else
    {
        printf("\n");
    }
    printf("\n\t\t\t\t\t0. Cancel\n\n\t\t\t\t\tEnter sr. no. of item: ");
    scanf("%d",&n);
    if(n!=0)
    {
        flag=1;
        newnode=(struct FoodItem*)malloc(sizeof(struct FoodItem));
        if (searchItem(n)!=NULL)
        {
            newnode -> item = searchItem(n);
            system("cls");
            printf("\n\t\t\t\t\t============================================\n\t\t\t\t\t\t\tO R D E R\n\t\t\t\t\t============================================");
            printf("\n\n\t\t\t\t\t\tCurrently ordering: ");
            ccolor(11);
            printf("%s",newnode->item);
            ccolor(15);
            x = 0;
            while(username[x]!='\0')
            {
               newnode->username[x] = username[x];
               x++;
            }
            newnode->username[x]='\0';
            printf("\n\n\t\t\t\t\t\t\tQuantity: ");
            scanf("%d",&q);

            newnode->qty=q;
            r=newnode -> item -> rate;
            //printf("\nr=%f",r);
            s=q*r;
            //printf("\ns=%f",s);
            newnode->price=s;
            //printf("\ns=%f",temp->price);
            if(top==NULL)
            {
                newnode->next=NULL;
                top=newnode;
            }
            else
            {
                newnode->next=top;
                top=newnode;
            }
            displayCart(username);
            printf("\n\n\t\t\t\t\t  Press any button to return to menu");
            getch();
        }
        else
        {
            flag=0;
            printf("\a");
            goto again;
        }
    }
}
void displayCart(char username[20])
{
    int i=1;
    float sum=0;
    struct FoodItem *temp;
    char str[50]="\0";
    temp=top;
    system("cls");
    printf("\n\t\t\t\t\t============================================\n\t\t\t\t\t\t\tC A R T\n\t\t\t\t\t============================================");
    printf("\n\t______________________________________________________________________________________________________");
    printf("\n\tSr. No.\t\tName\t\t\t\t\tQty\t\t\t\t\t Price");
    printf("\n\t______________________________________________________________________________________________________");
    if(top==NULL)
        printf("\n\n\t\t\t\t\t\t\tCart is empty\n");

    else
    {
        while(temp!=NULL && !(strcmp(temp->username, username)))
        {
            Sleep(20);
            printf("\n\t%d\t\t%s",i++,temp->item->name);
            spacing(temp->item->name,temp->qty,42);
            printf("%d",temp->qty);
            spacing(str,temp->price,40);
            printf("%0.2f", temp->price);
            sum=sum+temp->price;
            temp=temp->next;

        }
         printf("\n\t______________________________________________________________________________________________________");
            printf("\n\tTOTAL");
            spacing("TOTAL",sum,95);
            ccolor(10);
            printf("Rs. %0.2f",sum);
            ccolor(15);
    }
    printf("\n\t______________________________________________________________________________________________________");
}
/* Order-list Functions */

void enqueueOrder(char username[20])
{
    int x;
    struct Order *newnode;
    struct FoodItem *temp;
    newnode = (struct Order *)malloc(sizeof(struct Order));
    newnode->total=0;
    strcpy(newnode->username,username);
    temp = top;
    while(temp!=NULL && !(strcmp(temp->username, username)))
    {
        newnode -> total += temp -> price;
        temp = temp->next;
    }
    newnode->next='\0';
    if(rear==NULL)
    {
        front=newnode;
        rear=newnode;
    }
    else
    {
        rear->next=newnode;
        rear=newnode;
    }
}

void dequeueOrder()
{
    struct Order *temp;
    char val[20];
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t");
    if(front==NULL)
        printf("NO PENDING ORDERS.");
    else
    {
        temp=front;
        strcpy(val,temp->username);
        printf("%s, your order is ready to collect!",val);
        front=front->next;
        free(temp);
    }
}

void displayOrder()
{
    struct Order *temp1;
    char str1[100]="Name: ";
    char str[2]="\0";
    struct FoodItem*temp2;
    temp1=front;
    printf("\n\t\t\t\t\t============================================\n\t\t\t\t\t\t\tO R D E R S\n\t\t\t\t\t============================================");
    while(temp1!=NULL)
    {
        Sleep(20);
        printf("\n\n\t\t\t\t\t\tName: %s",temp1->username);
        spacing(strcat(str1,temp1->username), temp1->total,20);
        printf(" Total: ");
        ccolor(10);
        printf("%0.2f",temp1->total);
        ccolor(15);
        printf("\n\t\t\t_____________________________________________________________________________");
        printf("\n\t\t\tItem\t\t\t\t\tQty\t\t\t\tPrice");
        printf("\n\t\t\t_____________________________________________________________________________");
        temp2 = top;
        while(temp2!=NULL)
        {
            if(!(strcmp(temp2->username, temp1->username)))
            {
                printf("\n\t\t\t%s",temp2->item->name);
                spacing(temp2->item->name,temp2->qty,42);
                printf("%d",temp2->qty);
                spacing(str,temp2->price,32);
                printf("%0.2f", temp2->price);
            }
            temp2=temp2->next;
        }
        printf("\n\t\t\t_____________________________________________________________________________\n\n");
        temp1=temp1->next;
    }
    if(front==NULL)
    {
        printf("\n\n\t\t\t_____________________________________________________________________________\n\n");
        printf("\n\t\t\t\t\t\t\tNo orders");
        printf("\n\n\t\t\t_____________________________________________________________________________\n\n");
    }
}

void main()
{
    int choice1,choice2,n;
    char username[20];
    loadingbar();
    autoCreateMenu();
    do
    {
		system("cls");
        printf("\n\t\t\t\t\t============================================\n\t\t\t\t\t\t\tL O G I N\n\t\t\t\t\t============================================\n\n\t\t\t\t\t\t\t1. User\n\n\t\t\t\t\t\t\t2. Admin\n\t\t\t\t\t\t\n\n\n\t\t\t\t\t\tEnter choice: ");
        scanf("%d",&choice1);
        switch(choice1)
        {
            case 2: system("cls");
                    do{
                    printf("\n\t\t\t\t\t============================================\n\t\t\t\t\t\t    A D M I N   P A N E L\n\t\t\t\t\t============================================\n\n\t\t\t\t\t\t1. Edit Menu\n\n\t\t\t\t\t\t2. Orders\n\n\t\t\t\t\t\t3. Back\n\n\n\t\t\t\t\t\tEnter choice: ");
                    scanf("%d",&choice2);
                    switch(choice2)
                    {
                            case 1:
                                do
                                {
                                    system("cls");
                                    printf("\n\t\t\t\t\t============================================\n\t\t\t\t\t\t\tE D I T   M E N U\n\t\t\t\t\t============================================\n\n\t\t\t\t\t\t1. Add Items\n\n\t\t\t\t\t\t2. Edit Item\n\n\t\t\t\t\t\t3. View Menu\n\n\t\t\t\t\t\t4. Back\n\n\t\t\t\t\t\tEnter choice: ");
                                    scanf("%d", &choice2);
                                    switch(choice2)
                                    {
                                        case 1:
                                            system("cls");
                                            createMenuItem();
                                            getch();
                                            break;
                                        case 2:
                                            editItem();
                                            break;
                                        case 3:
                                            system("cls");
                                            displayMenu();
                                            printf("\n\n\t\t\t\t\t  Press any button to return to previous screen");
                                            getch();
                                            break;
                                    }
                                }while(choice2!=4);
                                system("cls");
                                break;

                            case 2:

                                do
                                {
                                    system("cls");
                                    printf("\n\t\t\t\t\t============================================\n\t\t\t\t\t\t\tO R D E R S\n\t\t\t\t\t============================================\n\n\t\t\t\t\t\t1. Serve order\n\n\t\t\t\t\t\t2. View Orders\n\n\t\t\t\t\t\t3. Back\n\n\t\t\t\t\t\tEnter choice: ");
                                    scanf("%d", &choice2);
                                    switch(choice2)
                                    {
                                        case 1:
                                            system("cls");
                                            dequeueOrder();
                                            getch();
                                            break;

                                        case 2:
                                            system("cls");
                                            displayOrder();
                                            getch();
                                            break;
                                    }
                                }while(choice2!=3);
                                break;
                        }
                    }while(choice2!=3);
                    break;


            case 1: system("cls");
                    printf("\n\n\n\n\n\n\t\t\t\t\t\tEnter username: ");
                    ccolor(10);
                    fflush(stdin);
                    gets(username);
                    ccolor(15);
                    do
                    {
                        system("cls");
                        printf("\n\t\t\t\t\t============================================\n\t\t\t\t\t\tW E L C O M E , ");
                        stringify(username);
                        printf("\n\t\t\t\t\t============================================\n\n\t\t\t\t\t\t1. Order\n\n\t\t\t\t\t\t2. View Cart\n\n\t\t\t\t\t\t3. Proceed to Checkout\n\n\t\t\t\t\t\t0. <- Back\n\n\n\t\t\t\t\t\tEnter choice:");
                        scanf("%d",&choice2);
                        switch(choice2)
                        {
                            case 1: pushFoodItem(username);
                                    break;

                            case 2: displayCart(username);
                                    printf("\n\n\t\t\t\t\t  Press any button to return to previous screen");
                                    getch();
                                    break;

                            case 3: enqueueOrder(username);
                                    displayCart(username);
                                    ccolor(47);
                                    printf("\n\n\t\t\t\t\t\t  Order placed successfully ");
                                    ccolor(15);
                                    printf("\n\n\t\t\t\t\t  Press any button to return to main screen");
                                    getch();
                                    Sleep(50);
                                    break;
                        }
                    }while (choice2!=0 && choice2!=3);
                    break;

        }
    }while(choice1!=4);
}
