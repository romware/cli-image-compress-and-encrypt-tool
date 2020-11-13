#include <stdio.h>	/*fread, fwrite, printf, scanf, fopen, fclose, getchar*/
#include <stdlib.h>	/*malloc, free*/
#include <string.h>	/*strcpy, strcat*/
#include "bitmap.h"	/*imageMap_t, prototypes*/

/*******************************************************************************
readImage
This function imports an image from a BMP file within the users file system. It
then stores this image in the imageMap struct so it can later be encrypted
Inputs:
 - imageMap_t imageList[MAX_LIST_SIZE]
 - int imageIndex
Outputs:
 - none
Authors:
 - Jack
*******************************************************************************/
void readImage(imageMap_t imageList[MAX_LIST_SIZE],int imageIndex)
{
	/* Initialise variables */
	char imagePath[100];
	FILE *fileInput;
	unsigned short int validDepth = 0;
	
	/* Prompt user for the path to the image file they want to import */
	printf(
		"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
		"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
		"╔════════════════════════════════════════╗\n"
		"║ Select a BMP image by typing its name: ║\n"
		"║                                        ║\n"
		"║ eg. forest.bmp                         ║\n"
		"║ eg. face.bmp                           ║\n"
		"║ eg. tux.bmp                            ║\n"
		"╠════════════════════════════════════════╝\n"
		"╚ ► ");
	scanf("%s", imagePath);
	fileInput = fopen (imagePath, "rb");
	
	/* Check if the selected file exists and is readable */
	if(fileInput != NULL)
	{
		/* Read the BMP File Header */
		fread(&imageList[imageIndex].fileHeader, 
		sizeof(bmpFileHeader_t), 1, fileInput);
		
		/* Read to BMP Info Header */
		fread(&imageList[imageIndex].infoHeader, 
		sizeof(bmpInfoHeader_t), 1, fileInput);
		
		/* Find the value of the colour depth from the header n*/
		validDepth = imageList[imageIndex].infoHeader.depth;
	}
	
	/* Check if the file is unreadable or not 24-bit colour */
	while(fileInput == NULL || validDepth != 24)
	{
		/* Print error message and re-ask for the file path */
		printf(
			"╔════════════════════════════════════════╗\n"
			"║ Error:                                 ║\n"
			"╠════════════════════════════════════════╣\n"
			"║   Please select a valid 24-bit bitmap  ║\n"
			"╠════════════════════════════════════════╝\n"
			"╚ ► ");
		scanf("%s", imagePath);
		fileInput = fopen (imagePath, "rb");
		
		/* Check if the selected file exists and is readable */
		if(fileInput != NULL)
		{
			/* Read the BMP File Header */
			fread(&imageList[imageIndex].fileHeader, 
			sizeof(bmpFileHeader_t), 1, fileInput);
			
			/* Read to BMP Info Header */
			fread(&imageList[imageIndex].infoHeader, 
			sizeof(bmpInfoHeader_t), 1, fileInput);
			
			/* Find the value of the colour depth n*/
			validDepth = imageList[imageIndex].infoHeader.depth;
			
			/* Check if the colour depth is 24-bit n*/
			if(validDepth != 24)
			{
				/* Close the file becuase it is not valid n*/
				fclose(fileInput);
				fileInput = NULL;
			}
		}
	}
	
	/* Set the imageMap width and height from the BMP info header n*/
	imageList[imageIndex].width = imageList[imageIndex].infoHeader.width;
	imageList[imageIndex].height = imageList[imageIndex].infoHeader.height;
	
	/* Set the imageMap name from the entered path n*/
	strncpy(imageList[imageIndex].name, imagePath, sizeof(imagePath));
	imageList[imageIndex].name[sizeof(imagePath)-1] = '\0';
	
	/* Print the metadata header info from what was read n*/
	printf(
		"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
		"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
		"╔════════════════════════════════════════╗\n"
		"║ Reading File ...................... 0%% ║\n"
		"║ Reading Bitmap File Header ...... 100%% ║\n"
		"║ Reading Bitmap Info Header ...... 100%% ║\n"
		"║ Reading Bitmap Width ......... %4d px ║\n"
		"║ Reading Bitmap Height ........ %4d px ║\n"
		"║ Reading Colour Depth ............ %4d ║\n"
		"╚════════════════════════════════════════╝\n", 
		imageList[imageIndex].width, 
		imageList[imageIndex].height, 
		imageList[imageIndex].infoHeader.depth);
	
	/* Initialise variables */
	int y = 0;
	int x = 0;
	int padding = 0;
	char temp[4];
	
	/* Find the padding based on the remainder */
	padding = imageList[imageIndex].width % 4;
	if(padding != 0) 
	{
		/* Calculate the remainding pixels are the division */
		padding = 4 - padding;
	}
	
	/* Loop through the pixel map vertically */
	for(y = 0; y < imageList[imageIndex].height; y++) 
	{
		/* Loop through the pixel map horizonally */
		for(x = 0; x < imageList[imageIndex].width; x++) 
		{
			/* Read colours from the selected pixel in the loop */
			fread(&imageList[imageIndex].blue[x][y],1,1, fileInput); 
			fread(&imageList[imageIndex].green[x][y],1,1,fileInput); 
			fread(&imageList[imageIndex].red[x][y],1,1, fileInput); 
		}
		
		if(padding != 0) 
		{
			/* Read the padding to a temporary variable */
			fread(&temp, padding, 1, fileInput);            
		}
	}
	
	/* Close the file */
	fclose(fileInput);
}

/*******************************************************************************
writeImage
This function writes an image to a BMP file in the users file system. It reads
the selected image from its struct and encodes it into the standard BMP file
format
Inputs:
 - imageMap_t imageList[MAX_LIST_SIZE]
 - int imageIndex
Outputs:
 - none
Authors:
 - Jack
*******************************************************************************/
void writeImage(imageMap_t imageList[MAX_LIST_SIZE],int imageIndex)
{
	/* Initialise variables */
	int width = imageList[imageIndex].width;
	int height = imageList[imageIndex].height;
	int y,x;
	
	/* Allocate memory */
	FILE *fileOutput;
	unsigned char *bmpPixels = NULL;
	bmpPixels = (unsigned char *)malloc(3*width*height);
	memset(bmpPixels,0,3*width*height);
	
	/* Loop through the pixel map vertically */
	for(y = 0; y < height; y++)
	{
		/* Loop through the pixel map horizonally */
		for(x = 0; x < width; x++)
		{
			/* Determine colour values at that point in the loop */
			int red = imageList[imageIndex].red[x][y];
			int green = imageList[imageIndex].green[x][y];
			int blue = imageList[imageIndex].blue[x][y];
			
			/* Determine the pixel location at that point */
			int address = (x + (height - 1 - y) * width) * 3;
			
			/* Write each colour to the pixel array */
			bmpPixels[address + 2] = (unsigned char)(red);
			bmpPixels[address + 1] = (unsigned char)(green);
			bmpPixels[address + 0] = (unsigned char)(blue);
		}
	}
	
	/* Initialise variables */
	unsigned char padding[3] = {0,0,0};	
	char *name = imageList[imageIndex].name;
	char fileName[100];
	
	/* Prepend _out to the file name so it does not overwrite original */
	strcpy(fileName, "out_");
	strcat(fileName, name);
	
	/* Open the file */
	fileOutput = fopen(fileName,"wb");
	
	/* Check if the selected file exists and is readable */
	if(fileOutput == NULL)
	{
		/* print error message */
		printf(
			"╔════════════════════════════════════════╗\n"
			"║ Error:                                 ║\n"
			"╠════════════════════════════════════════╣\n"
			"║         Unable to write to file        ║\n"
			"╚════════════════════════════════════════╝\n");
	}
	else
	{
		/* Write the BMP File Header */
		fwrite(&imageList[imageIndex].fileHeader, 
		sizeof(bmpFileHeader_t), 1, fileOutput);
		
		/* Write the BMP Info Header */
		fwrite(&imageList[imageIndex].infoHeader, 
		sizeof(bmpInfoHeader_t), 1, fileOutput);
		
		/* Loop through the pixel map vertically */
		for(y = 0; y < height; y++)
		{
			/* Write each pixel to the pixel map */
			fwrite(bmpPixels + ((height - y - 1) * width * 3)
						, 3, width, fileOutput);
			
			/* Write padding if required */
			fwrite(padding, 1, (4 - (width * 3) %4) %4, fileOutput);
		}
		
		/* Close the file */
		free(bmpPixels);
		fclose(fileOutput);
		
		/* Ask the user if they want to open the file */
		char open;
		printf(
			"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
			"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
			"╔════════════════════════════════════════╗\n"
			"║ Image has been exported successfully   ║\n"
			"║ Output name: %25s ║\n"
			"║                                        ║\n"
			"║ Type 'y' to open in default viewer or  ║\n"
			"║ enter key to continue                  ║\n"
			"╠════════════════════════════════════════╝\n"
			"╚ ► ", fileName);
			
		/* Clear Buffer */
		char c;
		while((c = getchar()) != '\n' && c != EOF){}
		scanf("%c", &open);
		
		if(open == 'y')
		{
			/* Execute the new file in the operating system */
			char fileOpen[100];
			strcpy(fileOpen, "xdg-open ");
			strcat(fileOpen, fileName);		
			int status = system(fileOpen);
		}
		
		/* Print header data if in debug */
		#ifdef DEBUG
		printf("Type %d\n",imageList[imageIndex].fileHeader.type);
		printf("Size %d\n",imageList[imageIndex].fileHeader.size);
		printf("Reserved1 %d\n",imageList[imageIndex]
					.fileHeader.reserved1);
		printf("Reserved2 %d\n",imageList[imageIndex]
					.fileHeader.reserved2);
		printf("Address %d\n",imageList[imageIndex].fileHeader.address);		
		printf("Size %d\n",imageList[imageIndex].infoHeader.size);
		printf("Width %d\n",imageList[imageIndex].infoHeader.width);
		printf("Height %d\n",imageList[imageIndex].infoHeader.height);
		printf("Planes %d\n",imageList[imageIndex].infoHeader.planes);
		printf("Depth %d\n",imageList[imageIndex].infoHeader.depth);
		printf("Compression %d\n",imageList[imageIndex]
					.infoHeader.compression);
		printf("BitmapSize %d\n",imageList[imageIndex]
					.infoHeader.bitmapSize);
		printf("x %d\n",imageList[imageIndex].infoHeader.x);
		printf("y %d\n",imageList[imageIndex].infoHeader.y);
		printf("Colors %d\n",imageList[imageIndex].infoHeader.colors);
		printf("Important %d\n",imageList[imageIndex]
					.infoHeader.important);
		#endif
	}
}
