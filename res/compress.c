#include "bitmap.h"
#include "compress.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*******************************************************************************
compressImage
This function reduces the size of the image until it is within the user's 
specification. It averages 4 red, blue and green pixel colour elements at a 
time and forms them into one.
Inputs:
 - imageMap_t imageList[MAX_LIST_SIZE]
 - int imageIndex
Outputs:
 - none
Authors:
 - Liam
 - Jack
*******************************************************************************/
void compressImage(imageMap_t imageList[MAX_LIST_SIZE], int imageIndex)
{
	/* Prompt the user to enter a maximum width */
	int width;	
	printf(
		"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
		"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
		"╔════════════════════════════════════════╗\n"
		"║ If you would like to compress the      ║\n"
		"║ image, please enter the maximum width: ║\n"
		"║                                        ║\n"
		"║ Otherwise, enter '-1' to keep the      ║\n"
		"║ original size                          ║\n"
		"╠════════════════════════════════════════╝\n"
		"╚ ► ");
	scanf("%d", &width);
	
	/* Check if valid width */
	if(width != -1 && width > 0)
	{
		int x,y;
		
		/* Loop until width is within value */
		while(imageList[imageIndex].width >= width)
		{
			/* Loop through the pixel map vertically */
			for(y=0; y < imageList[imageIndex].height; y++)
			{
				/* Loop through the pixel map horizontally */
				for(x=0; x < imageList[imageIndex].width; x++)
				{
					/* Group 4 pixels into 1 */
					imageList[imageIndex].red[x][y] 
				= (imageList[imageIndex].red[x*2][y*2]
				+imageList[imageIndex].red[(x*2)+1][y*2]
				+imageList[imageIndex].red[x*2][(y*2)+1]
				+imageList[imageIndex].red[(x*2)+1][(y*2)+1])/4;
					
					imageList[imageIndex].blue[x][y] 
				= (imageList[imageIndex].blue[x*2][y*2]
				+imageList[imageIndex].blue[(x*2)+1][y*2]
				+imageList[imageIndex].blue[x*2][(y*2)+1]
				+imageList[imageIndex]
				.blue[(x*2)+1][(y*2)+1])/4;
					
					imageList[imageIndex].green[x][y] 
				= (imageList[imageIndex].green[x*2][y*2]
				+imageList[imageIndex].green[(x*2)+1][y*2]
				+imageList[imageIndex].green[x*2][(y*2)+1]
				+imageList[imageIndex]
				.green[(x*2)+1][(y*2)+1])/4;
				}
			}
			
			/* Change to new height and width */
			imageList[imageIndex].height 
			= imageList[imageIndex].height /2;
			imageList[imageIndex].width 
			= imageList[imageIndex].width /2;
			
			/* Change to new size */
			imageList[imageIndex].fileHeader.size = 54 + 3*imageList
			[imageIndex].width*imageList[imageIndex].height;
			imageList[imageIndex].infoHeader.width 
			= imageList[imageIndex].infoHeader.width /2;
			imageList[imageIndex].infoHeader.height 
			= imageList[imageIndex].infoHeader.height /2;
		}
	}
}
/*******************************************************************************
deleteImage
This function deletes the selected image from the image list by moving all 
images to the right of it in the array across by one and then decrementing 
the imageIndex
Inputs:
 - imageMap_t imageList[MAX_LIST_SIZE]
 - int imageIndex
 - int selectIndex
Outputs:
- int imageIndex
Author:
- Liam
*******************************************************************************/
int deleteImage(imageMap_t imageList[MAX_LIST_SIZE], int imageIndex,
						 int selectIndex)
{
	/*declare variables*/
	int i;
	/*move each image down one element, starting from selected element*/
	for(i=selectIndex; i<=imageIndex; i++)
	{
		imageList[i-1] = imageList[i];
	}
	/*decrement the imageIndex*/
	imageIndex--;
	/*return the imageIndex*/
	return imageIndex;
}
