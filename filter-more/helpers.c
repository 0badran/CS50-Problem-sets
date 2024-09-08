#include "helpers.h"
#include "math.h"
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int redDegree = image[i][j].rgbtRed;
            int greenDegree = image[i][j].rgbtGreen;
            int blueDegree = image[i][j].rgbtBlue;
            int grayscaleDegree = round((redDegree + greenDegree + blueDegree) / 3.0);
            image[i][j].rgbtRed = grayscaleDegree;
            image[i][j].rgbtGreen = grayscaleDegree;
            image[i][j].rgbtBlue = grayscaleDegree;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        int startIndex = 0;
        int endIndex = width - 1;
        while (startIndex < endIndex)
        {
            RGBTRIPLE startPixel = image[i][startIndex];
            RGBTRIPLE endPixel = image[i][endIndex];
            image[i][startIndex] = endPixel;
            image[i][endIndex] = startPixel;
            startIndex++;
            endIndex--;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmpImage[height][width];
    const int RGB = 3;

    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            int rgbDegrees[RGB] = {0, 0, 0};
            float count = 0.0;

            for (int dx = -1; dx <= 1; dx++)
            {
                for (int dy = -1; dy <= 1; dy++)
                {
                    int nx = x + dx;
                    int ny = y + dy;

                    if (nx >= 0 && nx < height && ny >= 0 && ny < width)
                    {
                        rgbDegrees[0] += image[nx][ny].rgbtRed;
                        rgbDegrees[1] += image[nx][ny].rgbtGreen;
                        rgbDegrees[2] += image[nx][ny].rgbtBlue;
                        count++;
                    }
                }
            }

            tmpImage[x][y].rgbtRed = round(rgbDegrees[0] / count);
            tmpImage[x][y].rgbtGreen = round(rgbDegrees[1] / count);
            tmpImage[x][y].rgbtBlue = round(rgbDegrees[2] / count);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tmpImage[i][j];
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmpImage[height][width];
    const int RGB = 3;
    int Gx[RGB][RGB] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[RGB][RGB] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            int redX = 0, redY = 0, greenX = 0, greenY = 0, blueX = 0, blueY = 0;

            for (int dx = -1; dx <= 1; dx++)
            {
                for (int dy = -1; dy <= 1; dy++)
                {
                    int nx = x + dx;
                    int ny = y + dy;

                    if (nx >= 0 && nx < height && ny >= 0 && ny < width)
                    {
                        redX += image[nx][ny].rgbtRed * Gx[dx + 1][dy + 1];
                        redY += image[nx][ny].rgbtRed * Gy[dx + 1][dy + 1];
                        greenX += image[nx][ny].rgbtGreen * Gx[dx + 1][dy + 1];
                        greenY += image[nx][ny].rgbtGreen * Gy[dx + 1][dy + 1];
                        blueX += image[nx][ny].rgbtBlue * Gx[dx + 1][dy + 1];
                        blueY += image[nx][ny].rgbtBlue * Gy[dx + 1][dy + 1];
                    }
                }
            }

            int red = round(sqrt((redX * redX) + (redY * redY)));
            int green = round(sqrt((greenX * greenX) + (greenY * greenY)));
            int blue = round(sqrt((blueX * blueX) + (blueY * blueY)));

            if (red > 255)
                red = 255;
            if (green > 255)
                green = 255;
            if (blue > 255)
                blue = 255;

            tmpImage[x][y].rgbtRed = red;
            tmpImage[x][y].rgbtGreen = green;
            tmpImage[x][y].rgbtBlue = blue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tmpImage[i][j];
        }
    }
}
