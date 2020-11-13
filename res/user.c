#include <stdio.h> 	/*printf, scanf, getchar, rewind, ftell, fseek*/
#include <stdlib.h>	/*malloc, free*/
#include <string.h>	/*strcpy, strcat*/
#include "user.h" 	/*user_t, user based defines, prototypes*/

/*******************************************************************************
login
This function asks the user to enter a password. It will validate it then return
an integer if correct and -1 if incorrect. A return value of 0 indicates the 
user is the admin. All other users are allocated an int which identifys their 
user. 
Inputs:
 - user_t userList[MAX_USERS]
 - int userIndex
Outputs:
 - int user;
Authors:
- Liam
*******************************************************************************/
int login(user_t userList[MAX_USERS], int userIndex)
{
	/*declare variables*/
	user_t temp;
	int i;
	int j = -1; 	/*to varify/identify username*/
	int k = -1;	/*to varify password*/
	/*Add admin as user 0, set password*/
	strcpy(temp.name, "admin\0");
	strcpy(temp.password, "password123\0");
	userList[0] = temp;
	/*display welcome menu*/
	printf(
		"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
		"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
		"╔════════════════════════════════════════╗\n"
		"║ Welcome to...                          ║\n"
		"╠════════════════════════════════════════╣\n"
		"║ ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░ ║\n"
		"║ ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░ ║\n"
		"║ ░░░░░░░░ ┌─────────────────┐ ░░░░░░░░░ ║\n"
		"║ ░░░░░░░░ │ SizeyMcSizeFace │ ░░░░░░░░░ ║\n"
		"║ ░░░░░░░░ └─────────────────┘ ░░░░░░░░░ ║\n"
		"║ ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░ ║\n"
		"║ ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░ ║\n"
		"║ ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░ ║\n"
		"║ ░░░░░ ┌────────┐ ░░░░░░░░░░░░░░░░░░░░░ ║\n"
		"║ ░░░░░ │  ●  ●  │ ░░ ► ░░░ ┌───┐ ░░░░░░ ║\n"
		"║ ░░░░░ │        │ ░░░  ► ░ │ ☻ │ ░░░░░░ ║\n"
		"║ ░░░░░ │  ▬▬▬▬  │ ░░ ► ░░░ └───┘ ░░░░░░ ║\n"
		"║ ░░░░░ └────────┘ ░░░░░░░░░░░░░░░░░░░░░ ║\n"
		"║ ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░ ║\n"
		"║ ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░ ║\n"
		"║ ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░ ║\n"
		"╚════════════════════════════════════════╝\n");
	/*promt for username until a valid entry*/
	while(j==-1)
	{
		printf(
			"╔════════════════════════════════════════╗\n"
			"║ Username:                              ║\n"
			"╠════════════════════════════════════════╝\n"
			"╚ ► ");
		scanf("%s", temp.name);
		
		/*always set null character incase of large entry*/
		temp.name[MAX_USERNAME_SIZE-1] = '\0';

		/*validate username*/
		for(i=0; i <= MAX_USERS; i++)
		{
			/*search for username*/
			if(strcmp(temp.name, userList[i].name)==0)
			{
				/*if this is the user set j to i for tracking*/
				j=i;
				#ifdef DEBUG
				printf("user element %d\n", j);
				#endif
			}
		}
		/*if there are no username matches*/
		if(j==-1)
		{
			printf(
				"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
				"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
				"╔════════════════════════════════════════╗\n"
				"║ Error:                                 ║\n"
				"╠════════════════════════════════════════╣\n"
				"║            Invalid Username            ║\n"
				"╚════════════════════════════════════════╝\n");
		}
	}
	/*validate password*/
	while(k==-1)
	{
		printf(
			"╔════════════════════════════════════════╗\n"
			"║ Password:                              ║\n"
			"╠════════════════════════════════════════╝\n"
			"╚ ► ");
		scanf("%s", temp.password);
		
		/*always set null character incase of long entry*/
		temp.password[MAX_PASSWORD_LENGTH-1] = '\0';
		
		if(strcmp(temp.password, userList[j].password)==0)
		{
			#ifdef DEBUG
			printf("Welcome %s\n", temp.name);
			#endif
			k = 1;
			/*return user number*/
			return j;
		}
		/*if the password is incorrect*/
		else
		{
			printf(
				"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
				"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
				"╔════════════════════════════════════════╗\n"
				"║ Error:                                 ║\n"
				"╠════════════════════════════════════════╣\n"
				"║           Incorrect Password           ║\n"
				"╚════════════════════════════════════════╝\n");
		}
	}
	/*return no valid user*/
	return -1;
}

/*******************************************************************************
addUser
This function allows the adminstrator to add users to the userList.
Inputs:
 - user_t userList[MAX_USERS]
 - int userIndex
Outputs:
- int userIndex
Authors:
- Liam
*******************************************************************************/
int addUser(user_t userList[MAX_USERS], int userIndex)
{
	/*declare variables*/
	user_t temp;
	char confirm[MAX_PASSWORD_LENGTH];
	int i;
	int test =0;
	/*prompt admin for entry*/
	printf(
			"╔════════════════════════════════════════╗\n"
			"║ New Username:                          ║\n"
			"╠════════════════════════════════════════╝\n"
			"╚ ► ");
	/*scan string into temporaty user_t*/
	scanf("%s", temp.name);
	while(test == 0)
	{
		/*prompt for password*/
		printf(
			"╔════════════════════════════════════════╗\n"
			"║ New Password:                          ║\n"
			"╠════════════════════════════════════════╝\n"
			"╚ ► ");
		/*scan into temporary user_t*/
		scanf("%s", temp.password);
		/*prompt for re-entry*/
		printf(
			"╔════════════════════════════════════════╗\n"
			"║ Confirm New Password:                  ║\n"
			"╠════════════════════════════════════════╝\n"
			"╚ ► ");
		/*scan into confirm*/
		scanf("%s", confirm);
		/*verify both are equal*/
		if(strcmp(temp.password, confirm) == 0)
		{
			test = 1;
		}
		/*if incorrect warn admin*/
		else
		{
			printf(
				"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
				"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
				"╔════════════════════════════════════════╗\n"
				"║ Error:                                 ║\n"
				"╠════════════════════════════════════════╣\n"
				"║         Passwords do not match         ║\n"
				"╚════════════════════════════════════════╝\n");
		}
	}
	/*increment the user index*/
	userIndex++;
	/*move new user into the list*/
	userList[userIndex] = temp;
	/*display the current user list to admin*/
	printf("The userlist is as follows:\n");
	for(i=0; i<=userIndex; i++)
	{
		printf("%d. %s\n", i, userList[i].name);
	}
	/*save new userlist to database*/
	saveUserData(userList, userIndex);
	/*return new user index*/
	return userIndex;
}

/*******************************************************************************
saveUserData
This function saves the userList to a binary file called 'USER_DB_NAME'
Inputs:
- const user_t userList[MAX_USERS]
- int userIndex
Outputs-
- int userIndex
Authors:
- Liam
*******************************************************************************/
void saveUserData(const user_t userList[MAX_USERS], int userIndex)
{
	/*declare a file pointer*/
	FILE * filep;
	/*open the file declaring its name and type(write binary)*/
	filep = fopen (USER_DB_NAME, "wb");
	/*check if the file was opened correctly. Warn user if not*/	
	if(filep == NULL)
	{
		printf("Read error\n");
	}
	/*write the array of userList to the file taking the element size from 
	the sizeof function and the element number from 'userIndex'*/
	fwrite(userList, sizeof(user_t), (userIndex+1), filep);
	/*close the file*/
	fclose(filep);
}
/*******************************************************************************
readUserData
This function reads the userList that is saved in a binary file 'USER_DB_NAME'.
If no database is available it warns to user. The program will still have an
admin user that can then add other users and save them.
Inputs:
- user_t userList[MAX_USERS]
Outputs-
- int userIndex
Authors:
- Liam
*******************************************************************************/
int readUserData(user_t userList[MAX_USERS])
{
	/*declare variables*/
	int index = 0;
	/*declare a file pointer*/
	FILE * filep;
	/*store the calculated number of photos here (bytes/sizeof element*/
	long lSize;
	/*store the returned value of elements from fread here*/
	size_t result;
	/*open the binary file*/
	filep = fopen(USER_DB_NAME, "rb");
	/*check if open was successful, return 0 from function if not, which
		indicates there is only the admin in the user list*/
	if(filep==NULL)
	{
		printf("Read error - no database found\n");
		/*return value out of range to indicate error*/
		return 0;	
	}
	/*get file size in bytes and convert to elements 
	by diving by sizeof elements*/
	fseek (filep , 0 ,SEEK_END);
	lSize = (ftell (filep))/(sizeof(user_t));
	rewind (filep);
	/*read the binary file and put the amount of elements into result*/
	result = fread (userList, sizeof(user_t), lSize, filep);
	/*check that the read elements == the amount of elements in file*/
	if(result != lSize)
	{
		printf("Read error\n");
	}
	/*close the file*/
	fclose(filep);
	/*store the loaded number of photos to the index*/
	index = (((int)lSize)-1);
	/*return the new list value*/
	#ifdef DEBUG
	printf(" The user index is %d\n", index);
	#endif
	return index;
}
