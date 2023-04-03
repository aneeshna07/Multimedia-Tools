#include "filter.h"
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i=0; i<height; i++)
    {
        for(int j=0;j<width;j++)
        {
            int avg=ceil((image[i][j].rgbtBlue+image[i][j].rgbtGreen+image[i][j].rgbtRed)/3);
            image[i][j].rgbtBlue=avg;
            image[i][j].rgbtGreen=avg;
            image[i][j].rgbtRed=avg;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i=0; i<height; i++)
    {
        int x=width-1;
        RGBTRIPLE temp;
        for(int j=0; j<width/2; j++)
        {
            temp=image[i][j];
            image[i][j]=image[i][x];
            image[i][x]=temp;
            x--;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
	RGBTRIPLE imgCopy[height][width];
	float avgRed;
	float avgGreen;
	float avgBlue;

	//create a copy of original image to save original pixel values
	for (int row = 0; row < height; row++)
	{
		for (int w = 0; w < width; w++)
		{
			imgCopy[row][w].rgbtRed = image[row][w].rgbtRed;
			imgCopy[row][w].rgbtGreen = image[row][w].rgbtGreen;
			imgCopy[row][w].rgbtBlue = image[row][w].rgbtBlue;


		}
	}

	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			//if the pixel is on the top left edge
			if (w == 0 && h == 0)
			{
				image[h][w].rgbtRed = round((float)(imgCopy[h][w].rgbtRed + imgCopy[h][w+1].rgbtRed + imgCopy[h+1][w].rgbtRed + imgCopy[h+1][w+1].rgbtRed) / 4);

				image[h][w].rgbtGreen = round((float)(imgCopy[h][w].rgbtGreen + imgCopy[h][w+1].rgbtGreen + imgCopy[h+1][w].rgbtGreen + imgCopy[h+1][w+1].rgbtGreen) / 4);

				image[h][w].rgbtBlue= round((float)(imgCopy[h][w].rgbtBlue + imgCopy[h][w+1].rgbtBlue + imgCopy[h+1][w].rgbtBlue + imgCopy[h+1][w+1].rgbtBlue) / 4);

			}

			//if the pixel is on the lower left edge
			else if (w == 0 && h == (height - 1))
			{
				image[h][w].rgbtRed =round((float)(imgCopy[h-1][w].rgbtRed + imgCopy[h-1][w+1].rgbtRed + imgCopy[h][w].rgbtRed + imgCopy[h][w+1].rgbtRed) / 4);

				image[h][w].rgbtGreen= round((float)(imgCopy[h-1][w].rgbtGreen + imgCopy[h-1][w+1].rgbtGreen + imgCopy[h][w].rgbtGreen + imgCopy[h][w+1].rgbtGreen) / 4);

				image[h][w].rgbtBlue = round((float)(imgCopy[h-1][w].rgbtBlue + imgCopy[h-1][w+1].rgbtBlue + imgCopy[h][w].rgbtBlue + imgCopy[h][w+1].rgbtBlue) / 4);

			}

			//if the pixel is on top Right
			else if (h == 0 && w == (width - 1))
			{
			    image[h][w].rgbtRed = round((float)(imgCopy[h][w-1].rgbtRed + imgCopy[h][w].rgbtRed + imgCopy[h+1][w-1].rgbtRed + imgCopy[h+1][w].rgbtRed)/ 4);

				image[h][w].rgbtGreen= round((float)(imgCopy[h][w-1].rgbtGreen + imgCopy[h][w].rgbtGreen + imgCopy[h+1][w-1].rgbtGreen + imgCopy[h+1][w].rgbtGreen) / 4);

				image[h][w].rgbtBlue= round((float)(imgCopy[h][w-1].rgbtBlue + imgCopy[h][w].rgbtBlue + imgCopy[h+1][w-1].rgbtBlue + imgCopy[h+1][w].rgbtBlue) / 4);


			}

			//if the pixel is on lower right
			else if(h == (height - 1) && w == (width - 1))
			{
				image[h][w].rgbtRed = round((float)(imgCopy[h-1][w-1].rgbtRed + imgCopy[h-1][w].rgbtRed + imgCopy[h][w-1].rgbtRed + imgCopy[h][w].rgbtRed) / 4);

		 		image[h][w].rgbtBlue = round((float)(imgCopy[h-1][w-1].rgbtBlue + imgCopy[h-1][w].rgbtBlue + imgCopy[h][w-1].rgbtBlue + imgCopy[h][w].rgbtBlue) / 4);

				image[h][w].rgbtGreen = round((float)(imgCopy[h-1][w-1].rgbtGreen + imgCopy[h-1][w].rgbtGreen + imgCopy[h][w-1].rgbtGreen + imgCopy[h][w].rgbtGreen) / 4);

			}
    		//if the pixel is on left side
			else if (w == 0 && (h > 0 && h < height - 1))
			{
				image[h][w].rgbtRed  = round((float)(imgCopy[h-1][w].rgbtRed + imgCopy[h-1][w+1].rgbtRed + imgCopy[h][w].rgbtRed + imgCopy[h][w+1].rgbtRed + imgCopy[h+1][w].rgbtRed + imgCopy[h+1][w+1].rgbtRed) / 6);

		    	image[h][w].rgbtGreen = round((float)(imgCopy[h-1][w].rgbtGreen + imgCopy[h-1][w+1].rgbtGreen + imgCopy[h][w].rgbtGreen + imgCopy[h][w+1].rgbtGreen + imgCopy[h+1][w].rgbtGreen + imgCopy[h+1][w+1].rgbtGreen) / 6);

			    image[h][w].rgbtGreen = round((float)(imgCopy[h-1][w].rgbtBlue + imgCopy[h-1][w+1].rgbtBlue + imgCopy[h][w].rgbtBlue + imgCopy[h][w+1].rgbtBlue + imgCopy[h+1][w].rgbtBlue + imgCopy[h+1][w+1].rgbtBlue) / 6);


			}
      //if the pixel is on right side
			else if (w == (width - 1) && (h > 0 && h < height - 1))
			{
				image[h][w].rgbtRed= round((float)(imgCopy[h-1][w-1].rgbtRed + imgCopy[h-1][w].rgbtRed + imgCopy[h][w-1].rgbtRed + imgCopy[h][w].rgbtRed + imgCopy[h+1][w-1].rgbtRed + imgCopy[h+1][w].rgbtRed) / 6);

				image[h][w].rgbtGreen= round((float)(imgCopy[h-1][w-1].rgbtGreen + imgCopy[h-1][w].rgbtGreen + imgCopy[h][w-1].rgbtGreen + imgCopy[h][w].rgbtGreen + imgCopy[h+1][w-1].rgbtGreen + imgCopy[h+1][w].rgbtGreen) / 6);

				image[h][w].rgbtBlue  = round((float)(imgCopy[h-1][w-1].rgbtBlue + imgCopy[h-1][w].rgbtBlue + imgCopy[h][w-1].rgbtBlue + imgCopy[h][w].rgbtBlue + imgCopy[h+1][w-1].rgbtBlue + imgCopy[h+1][w].rgbtBlue) / 6);


			}
       //if the pixel is on upper side
			else if (h == 0 && (w > 0 &&  w < width - 1))
			{
				image[h][w].rgbtRed  = round((float)(imgCopy[h][w-1].rgbtRed + imgCopy[h][w].rgbtRed + imgCopy[h][w+1].rgbtRed + imgCopy[h+1][w-1].rgbtRed + imgCopy[h+1][w].rgbtRed + imgCopy[h+1][w+1].rgbtRed) / 6);

				image[h][w].rgbtGreen = round((float)(imgCopy[h][w-1].rgbtGreen + imgCopy[h][w].rgbtGreen + imgCopy[h][w+1].rgbtGreen + imgCopy[h+1][w-1].rgbtGreen + imgCopy[h+1][w].rgbtGreen + imgCopy[h+1][w+1].rgbtGreen) / 6);

				image[h][w].rgbtBlue= round((float)(imgCopy[h][w-1].rgbtBlue + imgCopy[h][w].rgbtBlue + imgCopy[h][w+1].rgbtBlue + imgCopy[h+1][w-1].rgbtBlue + imgCopy[h+1][w].rgbtBlue + imgCopy[h+1][w+1].rgbtBlue) / 6);

			}
       //if the pixel is on lower side
			else if  (h == height - 1 && (w > 0 && w < width - 1))
			{
				image[h][w].rgbtRed= round((float)(imgCopy[h-1][w-1].rgbtRed + imgCopy[h-1][w].rgbtRed + imgCopy[h-1][w+1].rgbtRed + imgCopy[h][w-1].rgbtRed + imgCopy[h][w].rgbtRed + imgCopy[h][w+1].rgbtRed) / 6);

				image[h][w].rgbtGreen =round((float)(imgCopy[h-1][w-1].rgbtGreen + imgCopy[h-1][w].rgbtGreen + imgCopy[h-1][w+1].rgbtGreen + imgCopy[h][w-1].rgbtGreen + imgCopy[h][w].rgbtGreen + imgCopy[h][w+1].rgbtGreen) / 6);
				image[h][w].rgbtBlue  = round((float)(imgCopy[h-1][w-1].rgbtBlue + imgCopy[h-1][w].rgbtBlue + imgCopy[h-1][w+1].rgbtBlue + imgCopy[h][w-1].rgbtBlue + imgCopy[h][w].rgbtBlue + imgCopy[h][w+1].rgbtBlue) / 6);
			}
      //if the pixel is on the middle and can form a 3x3 grid
			else
			{
				image[h][w].rgbtRed= round((float)(imgCopy[h-1][w-1].rgbtRed + imgCopy[h-1][w].rgbtRed + imgCopy[h-1][w+1].rgbtRed + imgCopy[h][w-1].rgbtRed + imgCopy[h][w].rgbtRed + imgCopy[h][w+1].rgbtRed + imgCopy[h+1][w-1].rgbtRed + imgCopy[h+1][w].rgbtRed + imgCopy[h+1][w+1].rgbtRed) / 9);
				image[h][w].rgbtGreen = round((float)(imgCopy[h-1][w-1].rgbtGreen + imgCopy[h-1][w].rgbtGreen + imgCopy[h-1][w+1].rgbtGreen + imgCopy[h][w-1].rgbtGreen + imgCopy[h][w].rgbtGreen + imgCopy[h][w+1].rgbtGreen + imgCopy[h+1][w-1].rgbtGreen + imgCopy[h+1][w].rgbtGreen + imgCopy[h+1][w+1].rgbtGreen) / 9);

				image[h][w].rgbtBlue  = round((float)(imgCopy[h-1][w-1].rgbtBlue + imgCopy[h-1][w].rgbtBlue + imgCopy[h-1][w+1].rgbtBlue + imgCopy[h][w-1].rgbtBlue + imgCopy[h][w].rgbtBlue + imgCopy[h][w+1].rgbtBlue + imgCopy[h+1][w-1].rgbtBlue + imgCopy[h+1][w].rgbtBlue + imgCopy[h+1][w+1].rgbtBlue) / 9);

			}

		}
	}
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
	RGBTRIPLE imgCopy[height][width];
	float avgRed;
	float avgGreen;
	float avgBlue;

	//create a copy of original image to save original pixel values
	for (int row = 0; row < height; row++)
	{
		for (int w = 0; w < width; w++)
		{
			imgCopy[row][w].rgbtRed = image[row][w].rgbtRed;
			imgCopy[row][w].rgbtGreen = image[row][w].rgbtGreen;
			imgCopy[row][w].rgbtBlue = image[row][w].rgbtBlue;


		}
	}
int rGx,rGy,gGx,gGy,bGx,bGy;
	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{

			//if the pixel is on the top left edge
			if (w == 0 && h == 0)
			{
				 rGx= 0+(2*imgCopy[h][w+1].rgbtRed)+0+0+(1*imgCopy[h+1][w+1].rgbtRed);
				 rGy= 0+0+0+0+0+0+imgCopy[h][w+1].rgbtRed+(2*imgCopy[h+1][w].rgbtRed)+(1*imgCopy[h+1][w+1].rgbtRed);
				 gGx=0+(2*imgCopy[h][w+1].rgbtGreen)+0+0+(1*imgCopy[h+1][w+1].rgbtGreen);
				 gGy= (0+0+0+0+0+0+imgCopy[h][w+1].rgbtGreen+(2*imgCopy[h+1][w].rgbtGreen)+(1*imgCopy[h+1][w+1].rgbtGreen));
				 bGx= (0+(2*imgCopy[h][w+1].rgbtBlue)+0+0+(1*imgCopy[h+1][w+1].rgbtBlue));
				 bGy= (0+0+0+0+0+0+imgCopy[h][w+1].rgbtBlue+(2*imgCopy[h+1][w].rgbtBlue)+(1*imgCopy[h+1][w+1].rgbtBlue));

			}
			//if the pixel is on the lower left edge
			else if (w == 0 && h == (height - 1))
			{
				rGx=(0+(0*imgCopy[h][w].rgbtRed)+(imgCopy[h][w+1].rgbtRed)+0+(0*imgCopy[h+1][w].rgbtRed)+(2*imgCopy[h+1][w+1].rgbtRed)+0+0+0);
				rGy=(0+(-1*2*imgCopy[h][w].rgbtRed)+(-1*imgCopy[h][w+1].rgbtRed)+0+(0*imgCopy[h+1][w].rgbtRed)+(0*imgCopy[h+1][w+1].rgbtRed)+0+0+0);
				gGx=(0+(0*imgCopy[h][w].rgbtGreen)+(imgCopy[h][w+1].rgbtGreen)+0+(0*imgCopy[h+1][w].rgbtGreen)+(2*imgCopy[h+1][w+1].rgbtGreen)+0+0+0);
				gGy=(0+(-1*2*imgCopy[h][w].rgbtGreen)+(-1*imgCopy[h][w+1].rgbtGreen)+0+(0*imgCopy[h+1][w].rgbtGreen)+(0*imgCopy[h+1][w+1].rgbtGreen)+0+0+0);
				bGx=(0+(0*imgCopy[h][w].rgbtBlue)+(imgCopy[h][w+1].rgbtBlue)+0+(0*imgCopy[h+1][w].rgbtBlue)+(2*imgCopy[h+1][w+1].rgbtBlue)+0+0+0);
				bGy=(0+(-1*2*imgCopy[h][w].rgbtBlue)+(-1*imgCopy[h][w+1].rgbtBlue)+0+(0*imgCopy[h+1][w].rgbtBlue)+(0*imgCopy[h+1][w+1].rgbtBlue)+0+0+0);
			}
			//if the pixel is on top Right
			else if (h == 0 && w == (width - 1))
			{
				rGx=0+0+0+(-1*2*imgCopy[h][w].rgbtRed)+(0*imgCopy[h][w+1].rgbtRed)+0+(-1*imgCopy[h+1][w-1].rgbtRed)+(0*imgCopy[h+1][w].rgbtRed)+0;
				rGy=0+0+0+(0*imgCopy[h][w].rgbtRed)+(0*imgCopy[h][w+1].rgbtRed)+0+imgCopy[h+1][w-1].rgbtRed+(2*imgCopy[h+1][w].rgbtRed)+0;
				gGx=0+0+0+(-1*2*imgCopy[h][w].rgbtGreen)+(0*imgCopy[h][w+1].rgbtGreen)+0+(-1*imgCopy[h+1][w-1].rgbtGreen)+(0*imgCopy[h+1][w].rgbtGreen)+0;
				gGy=0+0+0+(0*imgCopy[h][w].rgbtGreen)+(0*imgCopy[h][w+1].rgbtGreen)+0+imgCopy[h+1][w-1].rgbtGreen+(2*imgCopy[h+1][w].rgbtGreen)+0;
				bGx=0+0+0+(-1*2*imgCopy[h][w].rgbtBlue)+(0*imgCopy[h][w+1].rgbtBlue)+0+(-1*imgCopy[h+1][w-1].rgbtBlue)+(0*imgCopy[h+1][w].rgbtBlue)+0;
				bGy=0+0+0+(0*imgCopy[h][w].rgbtBlue)+(0*imgCopy[h][w+1].rgbtBlue)+0+imgCopy[h+1][w-1].rgbtBlue+(2*imgCopy[h+1][w].rgbtBlue)+0;
			}


			//if the pixel is on lower right
			else if(h == (height - 1) && w == (width - 1))
			{
				rGx=(-1*imgCopy[h-1][w-1].rgbtRed)+(0*imgCopy[h-1][w].rgbtRed)+0+(-1*2*imgCopy[h][w-1].rgbtRed)+(0*imgCopy[h][w].rgbtRed)+0+0+0+0;
				rGy=(-1*imgCopy[h-1][w-1].rgbtRed)+(-1*2*imgCopy[h-1][w].rgbtRed)+0+(0*imgCopy[h][w-1].rgbtRed)+(0*imgCopy[h][w].rgbtRed)+0+0+0+0;
				gGx=(-1*imgCopy[h-1][w-1].rgbtGreen)+(0*imgCopy[h-1][w].rgbtGreen)+0+(-1*2*imgCopy[h][w-1].rgbtGreen)+(0*imgCopy[h][w].rgbtGreen)+0+0+0+0;
				gGy=(-1*imgCopy[h-1][w-1].rgbtGreen)+(-1*2*imgCopy[h-1][w].rgbtGreen)+0+(0*imgCopy[h][w-1].rgbtGreen)+(0*imgCopy[h][w].rgbtGreen)+0+0+0+0;
				bGx=(-1*imgCopy[h-1][w-1].rgbtBlue)+(0*imgCopy[h-1][w].rgbtBlue)+0+(-1*2*imgCopy[h][w-1].rgbtBlue)+(0*imgCopy[h][w].rgbtBlue)+0+0+0+0;
				bGy=(-1*imgCopy[h-1][w-1].rgbtBlue)+(-1*2*imgCopy[h-1][w].rgbtBlue)+0+(0*imgCopy[h][w-1].rgbtBlue)+(0*imgCopy[h][w].rgbtBlue)+0+0+0+0;
			}
			//if the pixel is on left side
			else if (w == 0 && (h > 0 && h < height - 1))
			{
				rGx=0+(0*imgCopy[h-1][w].rgbtRed)+imgCopy[h-1][w+1].rgbtRed+0+(0*imgCopy[h][w].rgbtRed)+(2*imgCopy[h][w+1].rgbtRed)+0+(-1*imgCopy[h+1][w].rgbtRed)+(0*imgCopy[h+1][w+1].rgbtRed);
				rGy=0+(-1*2*imgCopy[h-1][w].rgbtRed)+(-1*imgCopy[h-1][w-1].rgbtRed)+0+0+0+0+(2*imgCopy[h+1][w].rgbtRed)+imgCopy[h+1][w+1].rgbtRed;
				gGx=0+(0*imgCopy[h-1][w].rgbtGreen)+imgCopy[h-1][w+1].rgbtGreen+0+(0*imgCopy[h][w].rgbtGreen)+(2*imgCopy[h][w+1].rgbtGreen)+0+(-1*imgCopy[h+1][w].rgbtGreen)+(0*imgCopy[h+1][w+1].rgbtGreen);
				gGy=0+(-1*2*imgCopy[h-1][w].rgbtGreen)+(-1*imgCopy[h-1][w-1].rgbtGreen)+0+0+0+0+(2*imgCopy[h+1][w].rgbtGreen)+imgCopy[h+1][w+1].rgbtGreen;
				bGx=0+(0*imgCopy[h-1][w].rgbtBlue)+imgCopy[h-1][w+1].rgbtBlue+0+(0*imgCopy[h][w].rgbtBlue)+(2*imgCopy[h][w+1].rgbtBlue)+0+(-1*imgCopy[h+1][w].rgbtBlue)+(0*imgCopy[h+1][w+1].rgbtRed);
				bGy=0+(-1*2*imgCopy[h-1][w].rgbtBlue)+(-1*imgCopy[h-1][w-1].rgbtBlue)+0+0+0+0+(2*imgCopy[h+1][w].rgbtBlue)+imgCopy[h+1][w+1].rgbtBlue;

			}
			//if the pixel is on right side
			else if (w == (width - 1) && (h > 0 && h < height - 1))
			{
				rGx=(-1*imgCopy[h-1][w-1].rgbtRed)+(0*imgCopy[h-1][w].rgbtRed)+0+(-2*imgCopy[h][w-1].rgbtRed)+(0*imgCopy[h][w].rgbtRed)+0+(-1*imgCopy[h+1][w-1].rgbtRed)+(0*imgCopy[h+1][w].rgbtRed)+0;
				rGy=(-1*imgCopy[h-1][w-1].rgbtRed)+(-2*imgCopy[h-1][w].rgbtRed)+0+(0*imgCopy[h][w-1].rgbtRed)+(0*imgCopy[h][w].rgbtRed)+0+(imgCopy[h+1][w-1].rgbtRed)+(2*imgCopy[h+1][w].rgbtRed)+0;
				gGx=(-1*imgCopy[h-1][w-1].rgbtGreen)+(0*imgCopy[h-1][w].rgbtGreen)+0+(-2*imgCopy[h][w-1].rgbtGreen)+(0*imgCopy[h][w].rgbtGreen)+0+(-1*imgCopy[h+1][w-1].rgbtGreen)+(0*imgCopy[h+1][w].rgbtGreen)+0;
				gGy=(-1*imgCopy[h-1][w-1].rgbtGreen)+(-2*imgCopy[h-1][w].rgbtGreen)+0+(0*imgCopy[h][w-1].rgbtGreen)+(0*imgCopy[h][w].rgbtGreen)+0+(imgCopy[h+1][w-1].rgbtGreen)+(2*imgCopy[h+1][w].rgbtGreen)+0;
				bGx=(-1*imgCopy[h-1][w-1].rgbtBlue)+(0*imgCopy[h-1][w].rgbtBlue)+0+(-2*imgCopy[h][w-1].rgbtBlue)+(0*imgCopy[h][w].rgbtBlue)+0+(-1*imgCopy[h+1][w-1].rgbtBlue)+(0*imgCopy[h+1][w].rgbtBlue)+0;
				bGy=(-1*imgCopy[h-1][w-1].rgbtBlue)+(-2*imgCopy[h-1][w].rgbtBlue)+0+(0*imgCopy[h][w-1].rgbtBlue)+(0*imgCopy[h][w].rgbtBlue)+0+(imgCopy[h+1][w-1].rgbtBlue)+(2*imgCopy[h+1][w].rgbtBlue)+0;
			}
			 //if the pixel is on upper side
			else if (h == 0 && (w > 0 &&  w < width - 1))
			{
				rGx=0+0+0+(-2*imgCopy[h][w-1].rgbtRed)+(0*imgCopy[h][w].rgbtRed)+(2*imgCopy[h][w+1].rgbtRed)+(-1*imgCopy[h+1][w-1].rgbtRed)+(0*imgCopy[h+1][w].rgbtRed)+(imgCopy[h+1][w+1].rgbtRed);
				rGy=0+0+0+0+0+0+(imgCopy[h+1][w-1].rgbtRed)+(2*imgCopy[h+1][w].rgbtRed)+(imgCopy[h+1][w+1].rgbtRed);
				gGx=0+0+0+(-2*imgCopy[h][w-1].rgbtGreen)+(0*imgCopy[h][w].rgbtGreen)+(2*imgCopy[h][w+1].rgbtGreen)+(-1*imgCopy[h+1][w-1].rgbtGreen)+(0*imgCopy[h+1][w].rgbtGreen)+(imgCopy[h+1][w+1].rgbtGreen);
				gGy=0+0+0+0+0+0+(imgCopy[h+1][w-1].rgbtGreen)+(2*imgCopy[h+1][w].rgbtGreen)+(imgCopy[h+1][w+1].rgbtGreen);
				bGx=0+0+0+(-2*imgCopy[h][w-1].rgbtBlue)+(0*imgCopy[h][w].rgbtBlue)+(2*imgCopy[h][w+1].rgbtBlue)+(-1*imgCopy[h+1][w-1].rgbtBlue)+(0*imgCopy[h+1][w].rgbtBlue)+(imgCopy[h+1][w+1].rgbtBlue);
				bGy=0+0+0+0+0+0+(imgCopy[h+1][w-1].rgbtBlue)+(2*imgCopy[h+1][w].rgbtBlue)+(imgCopy[h+1][w+1].rgbtBlue);
			}
			//if the pixel is on lower side
			else if  (h == height - 1 && (w > 0 && w < width - 1))
			{
				rGx=(-1*imgCopy[h-1][w-1].rgbtRed)+0+(imgCopy[h][w+1].rgbtRed)+(-2*imgCopy[h][w-1].rgbtRed)+0+(2*imgCopy[h][w+1].rgbtRed)+0+0+0;
				rGy=(-1*imgCopy[h-1][w-1].rgbtRed)+(-2*imgCopy[h-1][w].rgbtRed)+(-1*imgCopy[h][w+1].rgbtRed)+0+0+0+0+0+0;
				gGx=(-1*imgCopy[h-1][w-1].rgbtGreen)+0+(imgCopy[h][w+1].rgbtGreen)+(-2*imgCopy[h][w-1].rgbtGreen)+0+(2*imgCopy[h][w+1].rgbtGreen)+0+0+0;
				gGy=(-1*imgCopy[h-1][w-1].rgbtGreen)+(-2*imgCopy[h-1][w].rgbtGreen)+(-1*imgCopy[h][w+1].rgbtGreen)+0+0+0+0+0+0;
				bGx=(-1*imgCopy[h-1][w-1].rgbtBlue)+0+(imgCopy[h][w+1].rgbtBlue)+(-2*imgCopy[h][w-1].rgbtBlue)+0+(2*imgCopy[h][w+1].rgbtBlue)+0+0+0;
				bGy=(-1*imgCopy[h-1][w-1].rgbtBlue)+(-2*imgCopy[h-1][w].rgbtBlue)+(-1*imgCopy[h][w+1].rgbtBlue)+0+0+0+0+0+0;



			}
			else
			{
				rGx=(-1*imgCopy[h-1][w-1].rgbtRed)+0+(imgCopy[h-1][w+1].rgbtRed)+(-2*imgCopy[h][w-1].rgbtRed)+0+(2*imgCopy[h][w+1].rgbtRed)+(-1*imgCopy[h+1][w-1].rgbtRed)+0+imgCopy[h+1][w+1].rgbtRed;
				rGy=(-1*imgCopy[h-1][w-1].rgbtRed)+(-2*imgCopy[h-1][w].rgbtRed)+(-1*imgCopy[h-1][w+1].rgbtRed)+imgCopy[h+1][w-1].rgbtRed+(2*imgCopy[h+1][w].rgbtRed)+imgCopy[h+1][w+1].rgbtRed;
				gGx=(-1*imgCopy[h-1][w-1].rgbtGreen)+0+(imgCopy[h-1][w+1].rgbtGreen)+(-2*imgCopy[h][w-1].rgbtGreen)+0+(2*imgCopy[h][w+1].rgbtGreen)+(-1*imgCopy[h+1][w-1].rgbtGreen)+0+imgCopy[h+1][w+1].rgbtGreen;
				gGy=(-1*imgCopy[h-1][w-1].rgbtGreen)+(-2*imgCopy[h-1][w].rgbtGreen)+(-1*imgCopy[h-1][w+1].rgbtGreen)+imgCopy[h+1][w-1].rgbtGreen+(2*imgCopy[h+1][w].rgbtGreen)+imgCopy[h+1][w+1].rgbtGreen;
				bGx=(-1*imgCopy[h-1][w-1].rgbtBlue)+0+(imgCopy[h-1][w+1].rgbtBlue)+(-2*imgCopy[h][w-1].rgbtBlue)+0+(2*imgCopy[h][w+1].rgbtBlue)+(-1*imgCopy[h+1][w-1].rgbtBlue)+0+imgCopy[h+1][w+1].rgbtBlue;
				bGy=(-1*imgCopy[h-1][w-1].rgbtBlue)+(-2*imgCopy[h-1][w].rgbtBlue)+(-1*imgCopy[h-1][w+1].rgbtBlue)+imgCopy[h+1][w-1].rgbtBlue+(2*imgCopy[h+1][w].rgbtBlue)+imgCopy[h+1][w+1].rgbtBlue;
			}
				image[h][w].rgbtRed=round(sqrt((rGx*rGx)+(rGy*rGy)));
				image[h][w].rgbtBlue=round(sqrt((bGx*bGx)+(bGy*bGy)));
				image[h][w].rgbtGreen=round(sqrt((gGx*gGx)+(gGy*gGy)));
		}
	}
    return;
}



