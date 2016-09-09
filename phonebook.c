#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//a structure of a single entry in the phonebook defined as a contact
typedef struct {
	//each contact is defined with a name limited to 20 characters
	char name[20];
	//and a telephone number
	//using char because printing of an integer starting with a 0 is not possible
	//treating as a string instead will enable printing
	char telephone[20];
}Contact;

//a function that prints the information on a contact on position "position"
//takes a pointer to the array of contacts later created in the main
void printContact (Contact *contacts,int position)
{	printf("Name:");
	printf("%s\n",contacts[position].name);
	printf("  Telephone number:");
	printf("%s\n",contacts[position].telephone);
}

//a function that prints out all the contacts in the phonebook
//takes a pointer pointing to the phonebook array and a number showing the number of contacts already entered in the phonebook
void printPhonebook(Contact *contacts,int number)
{
	if(number==0)
	{
		printf("The phone book is empty!");
	}
	else{
		//counter
		int i;
		//starting from 0th index to index number-1 do in a cycle
		for (i=0;i<number;i++)
		{
			//print each contact information...
			//through calling the function printContact and taking i as the wanted position each time
			printf("%d.",i+1);
			printContact(contacts,i);
		}
	}
}

//a function that adds a new contact in the phonebook on index "index" where number is the number of contacts already existing in the phonebook
void addContact(Contact *contacts, int index)
{
	printf("Add a new contact:\n");
	printf("Name:");
	scanf("%s",contacts[index].name);
	printf("Telephone number:");
	scanf("%s",contacts[index].telephone);
}

//a void function that deletes a certain contact in the phonebook whose name we specify
//takes a pointer of the phonebook and a integer "number" representing the number of contacts already entered in the phonebook
void deleteContact(Contact *contacts, int number)
{
	if(number==0)
	{
	printf("The phone book is empty!");
	}
	else
	{
	//define a counter
	int i;
	//define an array for storing the name of the contact to be deleted
	char searchName[20];
	printf("Enter name of the contact you want to delete:");
	//store the entered name by the user in a char array
	scanf("%s",searchName);
	for(i=0;i<number;i++)
	{
		if(strcmp(contacts[i].name,searchName)==0)
		{number=number-1;
        while(i<number)
        	{
        	//a bug, the element of last position wont get deleted even tho
        	//it will get copied to the position of the previous element
        	//why?
        	//because we re dealing with an array of 100 contacts
        	contacts[i]=contacts[i+1];
        	i++;
        	}
		}
		else printf("The contact you're trying to delete does not exist!");
		break;
	}
	}
}

//a function that prints out the telephone number of the contact in the phonebook whose name we specify
//takes a pointer to the array contacts and a total number of contacts until this point in the phonebook
void printTelephoneNumber(Contact *contacts,int number)
{
	if(number==0)
	{
		printf("The phonebook is empty!");
	}
	else{
	//define a counter
	int i;
	//a char variable in which the name of the contact whose number we want to print is stored
	char searchName[20];
	printf("Enter name:");
	//user inputs name of contact
	scanf("%s",searchName);
		for(i=0;i<number;i++)
		{
			//if the return value of the function strcmp==0,  meaning the strings are equal, then:
			if(strcmp(contacts[i].name,searchName)==0)
			{
			//print out the telephone number of the searched contact
			printf("The telephone number of %s is %s\n",searchName,contacts[i].telephone);
			}
			else
			{
			printf("The contact does not exist!");
			break;
			}
		}
	}
}


int main()
{
printf("************PHONEBOOK************");
//initializing size of counter
size_t contactCounter=0;
//define a counter of type Contact
Contact *contactsPtr;
//allocate memory using calloc
//check difference between calloc and malloc?
contactsPtr=(Contact*)calloc(0,sizeof(Contact));
//define an integer variable select in which the wanted option of the menu is entered by the user
int select;
//do in a cycle while
do{
printf("\nChoose\n"
		"1- ADD A CONTACT\n"
		"2- SHOW A CONTACT\n"
		"3- DELETE A CONTACT\n"
		"4- SHOW THE PHONEBOOK\n"
		"5- EXIT\n");
printf("\nSelect option:");
//store user intput in variable select
scanf("%d",&select);
//clear the input buffer?
getchar();
//set up menu options matching corresponding functions
	switch(select)
	{case 1: //Add a contact
		 //increase variable contactCounter as the user chose to add a contact
		 contactCounter++;
		 //reallocate memory of the contacts ptr by increasing size by 1
		 contactsPtr=(Contact*)realloc(contactsPtr, contactCounter*sizeof(Contact));
		 //call the function addContact
		 addContact(contactsPtr,contactCounter-1);
		 break;
	case 2: //Show a contact
	 	 //call the function printTelephoneNumber
	 	 printTelephoneNumber(contactsPtr,contactCounter);
	 	 break;
	case 3: //Delete a contact
	 	 //call function deleteContact
	 	 deleteContact(contactsPtr,contactCounter);
	 	 contactCounter--;
	 	 contactsPtr=realloc(contactsPtr,contactCounter*sizeof(Contact));
	 	 break;
	case 4: //Show the phone book
	 	 //calling the function printPhonebook
	 	 printPhonebook(contactsPtr,contactCounter);
	 	 break;
	case 5: //Exit
	 	 break;
	default: printf("You entered an invalid selection. Please try again\n");
 	 	 break;
	}
}while(select!=5);
printf("Goodbye!");
//pause the program until user inputs any character
getchar();
//return value
return 0;
}
