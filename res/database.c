#include <stdio.h> 	/*printf, scanf, getchar, rewind, ftell, fseek*/
#include <stdlib.h>	/*strcpy, strcat*/
#include <string.h>	/*malloc, free*/
#include "bitmap.h"	/*uses the struct imageMap_t*/
#include "user.h"	/*uses the struct user_t, all user defines*/
#include "database.h"	/*function prototypes for saveToDatabase,
			 readFromDatabase*/
/*******************************************************************************
saveToDatabase
This function will write the imageList to a binary file.
The function checks if there are any write errors.
A file called 'userList[user].name' will be created or overwritten if it exists.
Inputs:
 - imageMap_t imageList[MAX_LIST_SIZE]
 - int imageIndex
 - int user
 - user_t userList[MAX_USERS]
Outputs:
 - none
Authors:
 - Liam
*******************************************************************************/
void saveToDatabase(const imageMap_t imageList[MAX_LIST_SIZE], int imageIndex, 
					int user, user_t userList[MAX_USERS])
{
	/*declare a file pointer*/
	FILE * filep;
	/*open the file declaring its name and type (write binary)*/
	filep = fopen (userList[user].name, "wb");
	/*check if the file was opened correctly. Warn user if not*/	
	if(filep == NULL)
	{
		printf("File read error\n");
	}
	/*write the array of imageList to the file taking the element size from 
	the sizeof function and the element number from 'imageIndex'*/
	fwrite(imageList, sizeof(imageMap_t), imageIndex, filep);
	/*close the file*/
	fclose(filep);
}
/*******************************************************************************
readFromDatabase
This function will read the imageIndex and imageList from a binary file.
The function checks if there are any read errors.
The imageList will be replaced with the one stored in the 'database' file.
The updated imageIndex is returned.
Inputs:
 - imageMap_t imageList[MAX_LIST_SIZE]
 - int imageIndex
Outputs:
 - int imageIndex
 - int user
 - user_t userList[MAX_USERS]
Authors:
- Liam
*******************************************************************************/
int readFromDatabase(imageMap_t imageList[MAX_LIST_SIZE], int imageIndex,
					 int user, user_t userList[MAX_USERS])
{
	/*declare a file pointer*/
	FILE * filep;
	/*store the calculated number of photos here (bytes/sizeof element*/
	long lSize;
	/*store the returned value of elements from fread here*/
	size_t result;
	/*open the binary file*/
	filep = fopen(userList[user].name, "rb");
	/*check if open was successful, return 13 from function if not*/
	if(filep==NULL)
	{
		printf("Read error- No database found\n");
		/*return value out of range to indicate error*/
		return 0;	
	}
	/*get file size in bytes and convert to elements 
	by diving by sizeof elements*/
	fseek (filep , 0 ,SEEK_END);
	lSize = (ftell (filep))/(sizeof(imageMap_t));
	rewind (filep);
	/*read the binary file and put the amount of elements into result*/
	result = fread (imageList, sizeof(imageMap_t), lSize, filep);
	/*check that the read elements == the amount of elements in file*/
	if(result != lSize)
	{
		printf("Read error\n");
	}
	/*close the file*/
	fclose(filep);
	/*store the loaded number of photos to the imageIndex*/
	imageIndex = (int)lSize;
	/*return the new list value*/
	#ifdef DEBUG
	printf("Image index is %d\n", imageIndex);
	#endif
	return imageIndex;

}
