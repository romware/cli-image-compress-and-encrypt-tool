#include "bitmap.h"	/*imageMap_t*/
#include "user.h"	/*user_t*/
#include "print.h"	/*fucntion prototypes*/
#include <stdio.h> 	/*printf, scanf, getchar,*/
#include <stdlib.h>	/*strcpy, strcat*/
#include <string.h>	/*malloc, free*/

/*******************************************************************************
printMenu
This function prints the initial menu with all instructions on how to use this
program. It will allow users to choose from a range of options.
Inputs:
 - const user_t userList[MAX_USERS]
 - int user
Outputs:
 - none
Authors:
 - Liam
 - Jack
*******************************************************************************/
void printMenu(const user_t userList[MAX_USERS], int user)
{
	printf(
		"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
		"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
		"╔════════════════════════════════════════╗\n"
		"║                        %15s ║\n"
		"║ Select an option:                      ║\n"
		"╠═══╤════════════════════════════════════╣\n", 
		userList[user].name);
	/*administrator print menu*/
	if(user == 0)
	{
		printf(
		"║ 0 │ Add a new user                     ║\n");
	}
	printf(		
		"║ 1 │ View saved images                  ║\n"
		"║ 2 │ Import an image                    ║\n"
		"║ 3 │ Export an image                    ║\n"
		"║ 4 │ Delete an image                    ║\n"
		"║ 5 │ Logout                             ║\n"
		"║ 6 │ Exit                               ║\n"
		"╠═══╧════════════════════════════════════╝\n"
		"╚ ► ");
}
/*******************************************************************************
printThubnail
This function compresses the image, looks at the colour levels of each pixel 
and choses an ASCII character and colour, which it then prints into the 
terminal to allow the user to preview the image.
Inputs:
 - const imageMap_t imageList[MAX_LIST_SIZE]
 - int imageIndex
Outputs:
- none
Author:
- Jack
*******************************************************************************/
void printThumbnail(const imageMap_t imageList[MAX_LIST_SIZE], int imageIndex)
{
	/* Initialise variables */
	int x,y;
	static imageMap_t image;
	image = imageList[imageIndex];
	
	/* Loop until image is small enough */
	while(image.width >= 38 || image.height >= 38)
	{
		/* Loop through the pixel map vertically */
		for(y=0; y < image.height; y++)
		{
			/* Loop through the pixel map horizontally */
			for(x=0; x < image.width; x++)
			{
				/* Average groups of 4 pixels into 1 */
				image.red[x][y] = (image.red[x*2][y*2]
					+image.red[(x*2)+1][y*2]
					+image.red[x*2][(y*2)+1]
					+image.red[(x*2)+1][(y*2)+1])/4;
				image.blue[x][y] = (image.blue[x*2][y*2]
					+image.blue[(x*2)+1][y*2]
					+image.blue[x*2][(y*2)+1]
					+image.blue[(x*2)+1][(y*2)+1])/4;
				image.green[x][y] = (image.green[x*2][y*2]
					+image.green[(x*2)+1][y*2]
					+image.green[x*2][(y*2)+1]
					+image.green[(x*2)+1][(y*2)+1])/4;
			}
		}
		
		/* Change to the new size */
		image.height = image.height /2;
		image.width = image.width /2;
	}
	
	/* Print border */
	printf(
			"╔════════════════════════════════════════════════════"
			"══════════════════════════╗\n"
			"║ Image Imported Successfully                "
			"                                  ║\n"
			"║                                             "
			"                                 ║\n");
	
	/* Use a buffer for whitespace */
	int buffer = 76 - image.width*2;
	if(buffer <= 0)
	{
		buffer = 0;
	}
	
	/* Loop through the pixel map vertically */
	for(y = image.height; y >=0; y--) 
	{
		printf("║ ");
		
		/* Loop through the pixel map horizontally */
		for(x = 0; x < image.width; x++) 
		{
			/* Change colour based on ratio to other channels */
			if(image.red[x][y] * 2 - 20 > image.green[x][y] 
						+ image.blue[x][y])
			{
				printf("\x1B[31m");
			}
			else if(image.blue[x][y] * 2 - 20 > image.green[x][y] 
						+ image.red[x][y])
			{
				printf("\x1B[34m");
			}
			else if(image.green[x][y] * 2 - 20 > image.blue[x][y] 
						+ image.red[x][y])
			{
				printf("\x1B[32m");
			}
			
			/* Change texture based on solidness of colour */
			if(image.blue[x][y] + image.green[x][y] 
						+ image.red[x][y] > 600)
			{
				printf("██");
			}
			else if(image.blue[x][y] + image.green[x][y] 
						+ image.red[x][y] > 450)
			{
				printf("▓▓");
			}
			else if(image.blue[x][y] + image.green[x][y] 
						+ image.red[x][y] > 300)
			{
				printf("▒▒");
			}
			else if(image.blue[x][y] + image.green[x][y] 
						+ image.red[x][y] > 150)
			{
				printf("░░");
			}
			else
			{
				printf("  ");
			}
			
			printf("\x1B[0m");
		}
		
		/* Print buffer of whitespace */
		int i;
		for(i = 0; i < buffer; i++) 
		{
			printf(" ");
		}
		
		printf(" ║\n");
	}
	printf("╚══════════════════════════════════════════════════════════"
						"════════════════════╝\n");
	
	printf("Press Enter to Continue");
	/* Ensure that the input buffer is cleared */
	char c;
	while ((c = getchar()) != '\n' && c != EOF) { }
	while( getchar() != '\n' );
}

/*******************************************************************************
displayImages
This function prints the name of each stored image in a numbered list.
Inputs:
 - const imageMap_t imageList[MAX_LIST_SIZE]
 - int imageIndex
Outputs:
- none
Authors:
 - Liam
 - Jack
*******************************************************************************/
void displayImages(const imageMap_t imageList[MAX_LIST_SIZE], int imageIndex)
{
	/*declare variables*/
	int i;
	printf(
		"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
		"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
		"╔════════════════════════════════════════╗\n"
		"║ Image Library:                         ║\n");
	
	/*print menu for empty library*/
	if(imageIndex == 0)
	{
		printf(
		"╠════════════════════════════════════════╣\n"
		"║       Your image library is empty      ║\n"
		"╚════════════════════════════════════════╝\n");
	}
	/*print char string of name for all images*/
	else
	{
		#ifdef DEBUG
		printf("image index is%d\n", imageIndex);
		#endif
		printf(
		"╠════╤═══════════════════════════════════╣\n");
		for(i=0; i < imageIndex; i++)
		{
			if(i < MAX_LIST_SIZE)
			{
				printf("║ %2d │ %33s ║\n", i+1,
					 imageList[i].name);
			}
		}		
		printf(
		"╚════╧═══════════════════════════════════╝\n");
	}
	
}
