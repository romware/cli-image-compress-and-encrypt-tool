#include <stdio.h>	/*printf, scanf, getchar,*/
#include <stdlib.h>	/*malloc, free*/
#include <string.h>	/*strcpy, strcat*/
#include "bitmap.h"	/*imageMap_t*/
#include "filter.h"	/*function prototypes*/
/*******************************************************************************
colourFilter
This function allows the user to apply a red, blue of green filter to an image.
The user is prompted for a colour which is represented by 'r', 'b', 'g', or, if
no filter is required 'x'.
The function warns the user if the input is invalid. Depending on the selection,
the function reads the colour element of all the pixels and increases the value
by 50%, unless this causes it to be greater than 255, where it will set it to 
255. 
Inputs:
 - imageMap_t imageList[MAX_LIST_SIZE]
 - int imageIndex
Outputs:
 - none
Authors:
 - Liam 
*******************************************************************************/
void colourFilter(imageMap_t imageList[MAX_LIST_SIZE], int imageIndex)
{
	/*define variables*/
	char colour;
	char c;
	int r, g, b, i;
	/*print instructions*/
	printf(
	"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
	"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
	"╔════════════════════════════════════════╗\n"
	"║ If you would like to apply an output   ║\n"
	"║ filter to the image, please enter the  ║\n"
	"║ colour of the desired filter.          ║\n"
	"║ Type:                                  ║\n"
	"║  'r' for a red filter                  ║\n"
	"║  'b' for a blue filter                 ║\n"
	"║  'g' for a green filter                ║\n"
	"║ Otherwise, enter 'x' to keep the       ║\n"
	"║ original brightness                    ║\n"
	"╠════════════════════════════════════════╝\n"
	"╚ ► ");
	/*clear buffer*/
	while((c = getchar()) != '\n' && c!=EOF){}
	/*scan input*/
	scanf("%c", &colour);
	#ifdef DEBUG
	printf("%c\n", colour);
	#endif
	/*validate input, re-promt if invalid*/
	while(colour !='r' && colour != 'b' && colour !='g' && colour != 'x')
	{
		printf(
			"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
			"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
			"╔════════════════════════════════════════╗\n"
			"║ Error:                                 ║\n"
			"╠════════════════════════════════════════╣\n"
			"║             Invalid Choice             ║\n"
			"╚════════════════════════════════════════╝\n"
			"╔════════════════════════════════════════╗\n"
			"║ If you would like to apply an output   ║\n"
			"║ filter to the image, please enter the  ║\n"
			"║ colour of the desired filter.          ║\n"
			"║ Type:                                  ║\n"
			"║  'r' for a red filter                  ║\n"
			"║  'b' for a blue filter                 ║\n"
			"║  'g' for a green filter                ║\n"
			"║ Otherwise, enter 'x ' to keep the      ║\n"
			"║ original brightness                    ║\n"
			"╠════════════════════════════════════════╝\n"
			"╚ ► ");
		/*clear buffer*/
		while((c = getchar()) != '\n' && c!=EOF){}
		/*scan input*/
		scanf("%c", &colour);
		#ifdef DEBUG
		printf("%c\n", colour);
		#endif
	}
	/*apply filter if chosen*/
	if(colour != 'x')
	{
		/*apply to all x axis pixels*/
		for(i=0;i<imageList[imageIndex].width;i++)
		{
			/*declare a variable for the y axis count*/
			int j;
			/*apply to all y axis pixels*/
			for (j=0;j<imageList[imageIndex].height;j++)
			{
				/*apply red filter*/
				if(colour == 'r')
				{
					#ifdef DEBUG
					printf("applying red filter\n");
					#endif
					r = imageList[imageIndex].red[i][j];
					imageList[imageIndex].red[i][j] = r*1.5;
					if(imageList[imageIndex].red[i][j]>255)
					{
						imageList[imageIndex]
							.red[i][j]=255;
					}
				}
				/*apply blue filter*/
				if(colour == 'b')
				{
					#ifdef DEBUG
					printf("applying blue filter\n");
					#endif
					b = imageList[imageIndex].blue[i][j];
					imageList[imageIndex].blue[i][j]=b*1.5;
					if(imageList[imageIndex].blue[i][j]>255)
					{
						imageList[imageIndex]
							.blue[i][j] = 255;
					}
				}
				/*apply green filter*/
				if(colour == 'g')
				{
					#ifdef DEBUG
					printf("applying green filter\n");
					#endif
					g=imageList[imageIndex].green[i][j]; 
					imageList[imageIndex].green[i][j]=g*1.5;
					if(imageList[imageIndex]
							.green[i][j]>255)
					{
						imageList[imageIndex]
							.green[i][j] = 255;
					} 
				}
			}
		}
	}
}
/*******************************************************************************
changeBrightness
This function allows the user to modify the brightness of the image from 50%
brightness to 150% brightness. The function does this by increasing the colour 
elements (red, blue and green) of each pixel by the entered amount. It checks
if the new value is greater than 255, if it is it sets it to 255.
Inputs:
 - imageMap_t imageList[MAX_LIST_SIZE]
 - int imageIndex
Outputs:
 - none
Authors:
 - Liam 
*******************************************************************************/
void changeBrightness(imageMap_t imageList[MAX_LIST_SIZE], int imageIndex)
{
	/*declare variables*/
	int brightness;
	int r, g, b, i;
	/*print instruction menu*/
	printf(
	"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
	"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
	"╔════════════════════════════════════════╗\n"
	"║ If you would like to adjust the        ║\n"
	"║ brightness of the image, please enter  ║\n"
	"║ a value between 50%% and 150%%           ║\n"
	"║                                        ║\n"
	"║ Otherwise, enter '-1' to keep the      ║\n"
	"║ original brightness                    ║\n"
	"╠════════════════════════════════════════╝\n"
	"╚ ► ");
	/*scan the entered value*/
	scanf("%d", &brightness);
		#ifdef DEBUG
		printf("%d\n", brightness);
		#endif
	/*validate the entry, warn and re-promp if incorrect*/
	while((brightness > 150 || brightness < 50) && brightness != -1)
	{
		printf(
			"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
			"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
			"╔════════════════════════════════════════╗\n"
			"║ Error:                                 ║\n"
			"╠════════════════════════════════════════╣\n"
			"║             Invalid Amount             ║\n"
			"╚════════════════════════════════════════╝\n"
			"╔════════════════════════════════════════╗\n"
			"║ If you would like to adjust the        ║\n"
			"║ brightness of the image, please enter  ║\n"
			"║ a value between 50%% and 150%%           ║\n"
			"║                                        ║\n"
			"║ Otherwise, enter '-1' to keep the      ║\n"
			"║ original brightness                    ║\n"
			"╠════════════════════════════════════════╝\n"
			"╚ ► ");
		/*scan the entered value*/
		scanf("%d", &brightness);
		#ifdef DEBUG
		printf("%d\n", brightness);
		#endif
	}
	/*apply change if selected*/
	if(brightness != -1)
	{
		/*apply to all x axis pixels*/
		for(i=0;i<imageList[imageIndex].width;i++)
		{
			/*declare a variable for y axis count*/
			int j;
			/*apply to all y axis pixels*/
			for (j=0;j<imageList[imageIndex].height;j++)
			{
				/*modify the red element*/
				r = imageList[imageIndex].red[i][j];
				imageList[imageIndex].red[i][j] 
							= r*brightness/100;
				/*check max value, limit if required*/
				if(imageList[imageIndex].red[i][j] > 255)
				{
					imageList[imageIndex].red[i][j] = 255;
				}
				/*modify the blue element*/
				b = imageList[imageIndex].blue[i][j];
				imageList[imageIndex].blue[i][j]
							 = b*brightness/100;
				/*check max value, limit if required*/
				if(imageList[imageIndex].blue[i][j] > 255)
				{
					imageList[imageIndex].blue[i][j] = 255;
				}
				/*modify the green element*/
				g = imageList[imageIndex].green[i][j]; 
				imageList[imageIndex].green[i][j] 
							= g*brightness/100;
				/*check max value, limit if required*/
				if(imageList[imageIndex].green[i][j] > 255)
				{
					imageList[imageIndex].green[i][j]=255;
				} 
			}
		}
	}
}
