#include <stdio.h>	/*printf, scanf*/
#include <stdlib.h>	/*malloc, free*/
#include <string.h>	/*strlen*/
#include "bitmap.h"	/*imageMap_t*/
#include "encrypt.h"	/*function prototypes, defines*/

/*******************************************************************************
encryptImage
This function encrypts an image by modifying the colours of each pixel according
to a user provided string and also the pixels position in the array.
Inputs:
 - imageMap_t imageList[MAX_LIST_SIZE]
 - int imageIndex
Outputs:
 - none
Authors:
 - Hongkit
*******************************************************************************/
void encryptImage(imageMap_t imageList[MAX_LIST_SIZE], int imageIndex)
{
    
	/*Prompt user for encryption information*/
    	char keyword[MAX_KEYWORDSIZE];
	do
	{   /*ask for a minimum 6 characters for secure encryption*/
		printf(
		"╔════════════════════════════════════════╗\n"
		"║ Please enter a secret key to encrypt   ║\n"
		"║ the image (minumum 6 characters)       ║\n"
		"╠════════════════════════════════════════╝\n"
		"╚ ► ");
    	scanf("%s",keyword);

	}
	while(strlen(keyword)<6);
    	int keycounter;
    	int total=0;
    	for(keycounter=0; keycounter<strlen(keyword);keycounter++)
    	{
        	/*in this part I use the (array+1) to access every characters*/
        	total = total+*(keyword+keycounter);
        	#ifdef DEBUG
    		    	printf("Total from ASCII counterpart: %d", total);
    		#endif
    	}
	/*declare variables*/
   	long int i,r,b,g;
    	for(i=0;i<imageList[imageIndex].width;i++)
    	{
       		int j;
        	for (j=0;j<imageList[imageIndex].height;j++)
       	 	{
            		/*This if statement is used to handle black pixels of 
			value 0 as we lose a very small amount of information 
			during encrption/decryption and 0 values return as 255*/
	        	if(imageList[imageIndex].red[i][j] == 0)
		    	{
			    	imageList[imageIndex].red[i][j] =1;
		    	}
            	/* The value of the denominator has one added to it 
		to prevent division of 0 */
            	/*Characters at different positions are included 
		in this for complex encryption*/
            	r = imageList[imageIndex].red[i][j] 
			+ (total+i*i*keyword[0]/(keyword[3]+1));

            	if(r > 255)
            	{
                	r = r % 255;
            	}
            
	        if(imageList[imageIndex].blue[i][j] == 0)
		    {
    			imageList[imageIndex].blue[i][j] =1;
    		}
            /* The value of the denominator has one added to it 
		to prevent division of 0 */
            	/*Characters at different positions are included 
		in this for complex encryption*/
            b = imageList[imageIndex].blue[i][j] 
		+ (total+j*i*keyword[1]/(keyword[4]+1));

            if(b > 255)
            {
                b = b % 255;
            }
            
    	    if(imageList[imageIndex].green[i][j] == 0)
    		{
    			imageList[imageIndex].green[i][j] =1;
    		}
    		/* The value of the denominator has one added to it 
		to prevent division of 0 */
            	/*Characters at different positions are included 
		in this for complex encryption*/
            g = imageList[imageIndex].green[i][j] 
		+ (total+j*j*keyword[2]/(keyword[5]+1));
            
            if(g > 255)
            {
                g = g % 255;
            }
            
	imageList[imageIndex].red[i][j] = r;
	imageList[imageIndex].blue[i][j] = b;
	imageList[imageIndex].green[i][j] = g;
        }
    }
    printf("Image encrypted\n");
}

/*******************************************************************************
decryptImage
This function decrypts the image by subtracting from the colour elements in 
reverse order from encryption. If the exact secret key is not entered the 
decryped image will stay in an encrypted form. In order the keep the values
in the correct range, a large multiple of 255 is added the the value initially
and the modulus of 255 is taken at the end.
Inputs:
 - imageMap_t imageList[MAX_LIST_SIZE]
 - int imageIndex
Outputs:
 - none
Authors:
 - Hongkit
*******************************************************************************/
void decryptImage(imageMap_t imageList[MAX_LIST_SIZE], int imageIndex)
{
    /*Prompt user for decryption information*/
	char dkeyword[MAX_KEYWORDSIZE];
    	printf(
		"╔════════════════════════════════════════╗\n"
		"║ Please enter the secret key to decrypt ║\n"
		"║ the image                              ║\n"
		"╠════════════════════════════════════════╝\n"
		"╚ ► ");
    	scanf("%s",dkeyword);
    	
    int keycounter;
    int total=0;
    for(keycounter=0; keycounter<strlen(dkeyword);keycounter++)
    {
        /*array loop to access every word*/
        total = total+*(dkeyword+keycounter);
        #ifdef DEBUG
    		    printf("Total from ASCII counterpart: %d", total);
    	#endif
    }
   /*declare variables*/	
   long int i,r,b,g;
    for(i=0;i<imageList[imageIndex].width;i++)
    {
        int j;
        for (j=0;j<imageList[imageIndex].height;j++)
        {   
            /*Characters at different positions are included in this part 
			to make sure exact match of character sequence*/
            r = (imageList[imageIndex].red[i][j] + 1024*1024*255 
		- (total + i*i*dkeyword[0]/(dkeyword[3]+1)))%255 +255;
            if(r > 255)
            {
                r = r % 255;
            }
	        imageList[imageIndex].red[i][j] = r;
	        
            /*Characters at different positions are included in this part 
			to make sure exact match of character sequence*/
            b = (imageList[imageIndex].blue[i][j] + 1024*1024*255 
		- (total + j*i*dkeyword[1]/(dkeyword[4]+1)))%255 +255;
            if(b > 255)
            {
                b = b % 255;
            }
	        imageList[imageIndex].blue[i][j] = b;
	        
            /*Characters at different positions are included in this part 
			to make sure exact match of character sequence*/
            g = (imageList[imageIndex].green[i][j] + 1024*1024*255 
		- (total + j*j*dkeyword[2]/(dkeyword[5]+1)))%255 +255;
            if(g > 255)
            {
                g = g % 255;
            }
	        imageList[imageIndex].green[i][j] = g;

        }
    }

}


