#pragma pack(1)
#define MAX_LIST_SIZE 10
#define MAX_IMG_WIDTH 4096
#define MAX_IMG_HEIGHT 2160

/*******************************************************************************
First 14 bits of a bitmap file to determine the type and size of the bitmap.
*******************************************************************************/
struct bmpFileHeader
{
   unsigned short int type;
   unsigned int size;
   unsigned short int reserved1;
   unsigned short int reserved2;
   unsigned int address;
};
typedef struct bmpFileHeader bmpFileHeader_t;

/*******************************************************************************
Next 40 bits of a bitmap file to determine the width, height, colour depth,
and various other attributes.
*******************************************************************************/
struct bmpInfoHeader
{
   unsigned int size;
   int width;
   int height;
   unsigned short int planes;
   unsigned short int depth;
   unsigned int compression;
   unsigned int bitmapSize;
   int x;
   int y;
   unsigned int colors;
   unsigned int important;
} ;
typedef struct bmpInfoHeader bmpInfoHeader_t;

/*******************************************************************************
Structure to hold both bitmap headers and the three colour channels in
two-dimensional arrays. Other metadata includes the file name, width and 
height.
*******************************************************************************/
struct imageMap
{	
	bmpFileHeader_t fileHeader;
	bmpInfoHeader_t infoHeader;
	
	char name[100];
	
	int width;
	int height;
	int red[MAX_IMG_WIDTH][MAX_IMG_HEIGHT];
	int green[MAX_IMG_WIDTH][MAX_IMG_HEIGHT];
	int blue[MAX_IMG_WIDTH][MAX_IMG_HEIGHT];
};
typedef struct imageMap imageMap_t;

/*******************************************************************************
List of function prototypes in this file
*******************************************************************************/
void readImage(imageMap_t imageList[MAX_LIST_SIZE],int imageIndex);
void writeImage(imageMap_t imageList[MAX_LIST_SIZE],int imageIndex);