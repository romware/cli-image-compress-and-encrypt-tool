/*******************************************************************************
48430 Embedded C - Assignment 3

Name: Group 26

Date of submission: 2017-10-13

Version: V1.0

The super awesome, greatest image compresser, encrypter and editor in the world.
Probably better than Photoshop
*******************************************************************************/

/*******************************************************************************
List of header files
*******************************************************************************/
#include <stdio.h> 	/*printf, scanf, getchar,*/
#include <stdlib.h>	/*strcpy, strcat*/
#include <string.h>	/*malloc, free*/

#include "bitmap.h" 	/*readImage, writeImage, imageMap_t*/
#include "user.h" 	/*login, addUser, saveUserData, readUserData, user_t*/
#include "print.h"	/*printMenu, printThumbnail, displayImages*/ 
#include "encrypt.h"	/*encryptImage, decryptImage*/
#include "compress.h"	/*compressImage, deleteImage*/
#include "filter.h"	/*colourFilter, changeBrightness*/
#include "database.h"	/*saveToDatabase, readFromDatabase*/
/*
#define DEBUG
*/
/*******************************************************************************
List of function prototypes in this file
*******************************************************************************/
void caseAddUser(int user, user_t userList[MAX_USERS], int userIndex);

void caseViewImages(const imageMap_t imageList[MAX_LIST_SIZE], int imageIndex);

int caseAddImage(imageMap_t imageList[MAX_LIST_SIZE], int imageIndex, 
int user, user_t userList[MAX_USERS]);
	
void caseExportImage(imageMap_t imageList[MAX_LIST_SIZE], int imageIndex, 
int user, user_t userList[MAX_USERS]);

int caseDeleteImage(imageMap_t imageList[MAX_LIST_SIZE], int imageIndex, 
int user, user_t userList[MAX_USERS]);

void caseInvalid(void);

/*main*/
int main(void)
{
	/* Define variables */	
	static imageMap_t imageList[MAX_LIST_SIZE];	
	user_t userList[MAX_USERS];
	
	int imageIndex = 0;		
	int userIndex = 0;
	
	int user = -1;	
	int userChoice;
	
	/* Load users from database */	
	userIndex = readUserData(userList);
	
	/* Authenticate user and load user data from database */	
	user = login(userList, userIndex);
	imageIndex = readFromDatabase(imageList, imageIndex, user, userList);
	
	#ifdef DEBUG
	printf("Image index: %d\n", imageIndex);
	#endif
	
	/* Check if user has access */
	if(user != -1)
	{
		/* Loop until the user enters '6' to exit */
		while (userChoice != 6)
		{
			/* Print a list of options to the user/administrator */
			printMenu(userList, user);
			
			/* Scan the users input */
			scanf("%d", &userChoice);
			
			/* Check to see which option the user has entered */
			switch (userChoice)
			{
				case 0:
				{
					/* Create a new user */
					#ifdef DEBUG
					printf("Case %d", userChoice);
					#endif
					caseAddUser(user, userList, userIndex);				
					break;
				}
				case 1:
				{
					/* Display each of the users images*/
					#ifdef DEBUG
					printf("Case %d", userChoice);
					#endif
					caseViewImages(imageList, imageIndex);					
					break;
				}
				case 2:
				{
					/* Add a new image to the library */
					#ifdef DEBUG
					printf("Case %d", userChoice);
					#endif
					imageIndex = caseAddImage(imageList,
						imageIndex, user, userList);					
					break;
				}
				case 3:
				{
					/* Export an image from the library */
					#ifdef DEBUG
					printf("Case %d", userChoice);
					#endif
					caseExportImage(imageList, imageIndex,
							 user, userList);					
					break;
				}
				case 4:
				{
					/* Delete an image from the library */
					#ifdef DEBUG
					printf("Case %d", userChoice);
					#endif
					imageIndex = caseDeleteImage(imageList,
						imageIndex, user, userList);	
					break;
				}
				case 5:
				{
					#ifdef DEBUG
					printf("Case %d", userChoice);
					#endif
					/* Logout the current user */
					user = -1;
					
					/* Return to the login screen*/
					user = login(userList, userIndex);
					
					/* Load the new user's data from the 
							that user's database */
					imageIndex=readFromDatabase(imageList,
						 imageIndex, user, userList);
					break;
				}
				case 6:
				{
					/* Exit from the loop and program */
					#ifdef DEBUG
					printf("Case %d", userChoice);
					#endif
					break;
				}
				default:
				{
					/* Respond with error message if 
						the choice is invalid */
					#ifdef DEBUG
					printf("Case Invalid");
					#endif
					caseInvalid();					
					break;
				}
			}
		}
	}
	/* End of main */
	return 0;
}

/*******************************************************************************
Main case functions
These functions call up the required functions for the selected options in
the main loop.
*******************************************************************************/

/*******************************************************************************
caseAddUser
This function calls up the required functions to add a user to the program.
This function needs administrator privileges. 
Inputs:
 - int user
 - user_t userList[MAX_USERS]
 - int imageIndex
Outputs:
 - none
Author:
 - Jack
*******************************************************************************/
void caseAddUser(int user, user_t userList[MAX_USERS], int userIndex)
{
	/* Check if the user is admin to create a new user */
	if(user == 0)
	{
		userIndex = addUser(userList, userIndex);
	}
	else
	{
		printf("Permision denied\n");
	}
}
/*******************************************************************************
caseViewImages
This function calls up the required functions to view the imageList of the 
current user.
Inputs:
 - const imageMap_t imageList[MAX_LIST_SIZE]
 - int imageIndex
Outputs:
 - none
Author:
 - Jack
*******************************************************************************/
void caseViewImages(const imageMap_t imageList[MAX_LIST_SIZE], int imageIndex)
{
	/* Display each of the users images in a table */
	#ifdef DEBUG
	printf("Image index is %d\n", imageIndex);
	#endif
	displayImages(imageList, imageIndex);

	/* Wait for user to hit Enter key to return */
	printf("Press Enter to Continue");
	
	/* Clear buffer */					
	char c;
	while ((c = getchar()) != '\n' && c != EOF) { }
	while( getchar() != '\n' );
}
/*******************************************************************************
caseAddImage
This function calls up the required functions to add an image.
Inputs:
 - imageMap_t imageList[MAX_LIST_SIZE]
 - int imageIndex
 - int user
 - user_t userList[MAX_USERS]
Outputs:
 - int imageIndex
Author:
 - Jack
*******************************************************************************/
int caseAddImage(imageMap_t imageList[MAX_LIST_SIZE], int imageIndex, 
int user, user_t userList[MAX_USERS])
{
	/* Check if library has space to add a new image */
	if(imageIndex <= MAX_LIST_SIZE)
	{
		/* Read bitmap data from a BMP file */
		readImage(imageList,imageIndex);
		
		/* Generate an ASCII thumbnail in the terminal */
		printThumbnail(imageList,imageIndex);
		
		/* Encrypt the pixels in the bitmap */
		encryptImage(imageList, imageIndex);
		
		/* Imcrement the image index of the users library */
		imageIndex++;
		
		/* Save the new image to the database */
		saveToDatabase(imageList, imageIndex, user, userList);
	}
	else
	{
		/* Print the error if image list is full */
		printf(
		"╔════════════════════════════════════════╗\n"
		"║            Library is full             ║\n"
		"╚════════════════════════════════════════╝\n"
		"Press Enter to Continue");
		
		/* Clear Buffer */
		char c;
		while ((c = getchar()) != '\n' && c != EOF) { }
		while( getchar() != '\n' );
	}
	
	return imageIndex;
}
/*******************************************************************************
caseExportImage
This function calls up the required functions to export an image.
Inputs:
 - imageMap_t imageList[MAX_LIST_SIZE]
 - int imageIndex
 - int user
 - user_t userList[MAX_USERS]
Outputs:
 - none
Author:
 - Jack
*******************************************************************************/	
void caseExportImage(imageMap_t imageList[MAX_LIST_SIZE], int imageIndex, 
int user, user_t userList[MAX_USERS])
{
	int selectIndex;					
	
	/* Display each of the users images in a table */
	displayImages(imageList, imageIndex);
	
	/* Ask the user which image to export */
	printf(
	"Enter the image number to export "
	"or type '-1' to cancel\n");					
	scanf("%d", &selectIndex);	
	
	/* Check if the user has selected a valid image */
	while((selectIndex-1 < 0 || imageIndex <= selectIndex-1) 
	&& selectIndex != -1)
	{
		/* Display each of the users images in a table */
		displayImages(imageList, imageIndex);
		
		/* Print error if invalid image selected */
		printf(
		"╔════════════════════════════════════════╗\n"
		"║ Error:                                 ║\n"
		"╠════════════════════════════════════════╣\n"
		"║             Invalid Image              ║\n"
		"╚════════════════════════════════════════╝\n"
		"Enter the image number to export "
		"or type '-1' to cancel\n");
		scanf("%d", &selectIndex);
	}
	
	/* Check if user has cancelled the selection */
	if(selectIndex == -1)
	{
		printf("Returned to menu\n");
	}
	else
	{
		/* Decrement the select index (to start at 0) */
		selectIndex--;
		
		/* Decrypt the pixels in the selected image */
		decryptImage(imageList, selectIndex);
		
		/* Change the brightness of the selected image */
		changeBrightness(imageList, selectIndex);
		
		/* Apply a filter to the selected image */
		colourFilter(imageList, selectIndex);
		
		/* Reduce the size of the selected image */
		compressImage(imageList, selectIndex);
		
		/* Write the selected image to a BMP file */
		writeImage(imageList, selectIndex);
		
		/* Reload the images from the database */
		imageIndex=readFromDatabase(imageList,imageIndex,user,userList);
	}
}
/*******************************************************************************
caseDeleteImage
This function calls up the required functions to delete an image.
Inputs:
 - imageMap_t imageList[MAX_LIST_SIZE]
 - int imageIndex
 - int user
 - user_t userList[MAX_USERS]
Outputs:
 - int imageIndex
Author:
 - Jack
*******************************************************************************/
int caseDeleteImage(imageMap_t imageList[MAX_LIST_SIZE], int imageIndex, 
int user, user_t userList[MAX_USERS])
{
	int selectIndex;
	/* Display each of the users images in a table */
	displayImages(imageList, imageIndex);
	
	/* Ask the user to select an image or cancel */
	printf(
	"Select an image by entering its number or "
	"type '-1' to cancel\n");
	scanf("%d", &selectIndex);
	
	/* Check if a valid image is selected or cancelled */
	while((selectIndex-1 < 0 || imageIndex <= selectIndex-1)
	&& selectIndex != -1)
	{
		/* Display each of the users images in a table */
		displayImages(imageList, imageIndex);
		
		/* Print error if invalid image is selected */
		printf(
		"╔════════════════════════════════════════╗\n"
		"║ Error:                                 ║\n"
		"╠════════════════════════════════════════╣\n"
		"║             Invalid Image              ║\n"
		"╚════════════════════════════════════════╝\n"
		"Select an image by entering its number or "
		"type '-1' to cancel\n");
		scanf("%d", &selectIndex);
	}
	
	if(selectIndex == -1)
	{
		/* Cancel the selection */
		printf("Returned to menu\n");
	}
	else
	{
		/* Delete the selected image */
		imageIndex = deleteImage(imageList, imageIndex, selectIndex);
		
		/* Save changes to the database */
		saveToDatabase(imageList, imageIndex, user, userList);
	}
	
	return imageIndex;
}
/*******************************************************************************
caseInvalid
This function warns the user if an invalid choice has been made.
Inputs:
 - none
Outputs:
 - none
Author:
 - Jack
*******************************************************************************/
void caseInvalid(void)
{
	/* Respond with error message if the choice is invalid */
	printf(
	"╔════════════════════════════════════════╗\n"
	"║             Invalid Choice             ║\n"
	"╚════════════════════════════════════════╝\n"
	"Press Enter to Continue");
	
	/* Clear Buffer */
	char c;
	while ((c = getchar()) != '\n' && c != EOF) { }
	while( getchar() != '\n' );
}
