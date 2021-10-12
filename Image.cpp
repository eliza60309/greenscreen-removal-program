//*****************************************************************************
//
// Image.cpp : Defines the class operations on images
//
// Author - Parag Havaldar
// Code used by students as starter code to display and modify images
//
//*****************************************************************************

#include "Image.h"
#include <iostream>
#include <vector>
using namespace std;

// Constructor and Desctructors
MyImage::MyImage() 
{
	Data = NULL;
	Width = -1;
	Height = -1;
	ImagePath[0] = 0;
}

MyImage::~MyImage()
{
	if ( Data )
		delete []Data;
}


// Copy constructor
MyImage::MyImage( MyImage *otherImage)
{
	Height = otherImage->Height;
	Width  = otherImage->Width;
	Data   = new char[Width*Height*3];
	strcpy(otherImage->ImagePath, ImagePath );

	for ( int i=0; i<(Height*Width*3); i++ )
	{
		Data[i]	= otherImage->Data[i];
	}


}



// = operator overload
MyImage & MyImage::operator= (const MyImage &otherImage)
{
	Height = otherImage.Height;
	Width  = otherImage.Width;
	if (Data)
		delete[]Data;
	Data = new char[Width*Height*3];
	strcpy( (char *)otherImage.ImagePath, ImagePath );

	for ( int i=0; i<(Height*Width*3); i++ )
	{
		Data[i]	= otherImage.Data[i];
	}
	
	return *this;

}


// MyImage::ReadImage
// Function to read the image given a path
bool MyImage::ReadImage()
{
	// Verify ImagePath
	if (ImagePath[0] == 0 || Width < 0 || Height < 0 )
	{
		fprintf(stderr, "Image or Image properties not defined");
		fprintf(stderr, "Usage is `Image.exe Imagefile w h`");
		return false;
	}

	// Create a valid output file pointer
	FILE *IN_FILE;
	IN_FILE = fopen(ImagePath, "rb");
	if ( IN_FILE == NULL ) 
	{
		fprintf(stderr, "Error Opening File for Reading");
		return false;
	}

	// Create and populate RGB buffers
	int i;
	char *Rbuf = new char[Height*Width]; 
	char *Gbuf = new char[Height*Width]; 
	char *Bbuf = new char[Height*Width]; 

	for (i = 0; i < Width*Height; i ++)
	{
		Rbuf[i] = fgetc(IN_FILE);
	}
	for (i = 0; i < Width*Height; i ++)
	{
		Gbuf[i] = fgetc(IN_FILE);
	}
	for (i = 0; i < Width*Height; i ++)
	{
		Bbuf[i] = fgetc(IN_FILE);
	}
	
	// Allocate Data structure and copy
	Data = new char[Width*Height*3];
	for (i = 0; i < Height*Width; i++)
	{
		Data[3*i]	= Bbuf[i];
		Data[3*i+1]	= Gbuf[i];
		Data[3*i+2]	= Rbuf[i];
	}

	// Clean up and return
	delete []Rbuf;
	delete []Gbuf;
	delete []Bbuf;
	fclose(IN_FILE);

	return true;

}



// MyImage functions defined here
bool MyImage::WriteImage()
{
	// Verify ImagePath
	// Verify ImagePath
	if (ImagePath[0] == 0 || Width < 0 || Height < 0 )
	{
		fprintf(stderr, "Image or Image properties not defined");
		return false;
	}
	
	// Create a valid output file pointer
	FILE *OUT_FILE;
	OUT_FILE = fopen(ImagePath, "wb");
	if ( OUT_FILE == NULL ) 
	{
		fprintf(stderr, "Error Opening File for Writing");
		return false;
	}

	// Create and populate RGB buffers
	int i;
	char *Rbuf = new char[Height*Width]; 
	char *Gbuf = new char[Height*Width]; 
	char *Bbuf = new char[Height*Width]; 

	for (i = 0; i < Height*Width; i++)
	{
		Bbuf[i] = Data[3*i];
		Gbuf[i] = Data[3*i+1];
		Rbuf[i] = Data[3*i+2];
	}

	
	// Write data to file
	for (i = 0; i < Width*Height; i ++)
	{
		fputc(Rbuf[i], OUT_FILE);
	}
	for (i = 0; i < Width*Height; i ++)
	{
		fputc(Gbuf[i], OUT_FILE);
	}
	for (i = 0; i < Width*Height; i ++)
	{
		fputc(Bbuf[i], OUT_FILE);
	}
	
	// Clean up and return
	delete []Rbuf;
	delete []Gbuf;
	delete []Bbuf;
	fclose(OUT_FILE);

	return true;

}




// Here is where you would place your code to modify an image
// eg Filtering, Transformation, Cropping, etc.
bool MyImage::Modify()
{

	// TO DO by student
	
	// sample operation
	for ( int i=0; i<Width*Height; i++ )
	{
		Data[3*i] = 0;
		Data[3*i+1] = 0;
	}

	return false;
}

int MyImage::SampleImg(int sampleid, int args)
{
	switch (sampleid)
	{
		if(!Data)
			Data = new char[Width * Height * 3];
		case 1://black white stripes, args = stripe width
		{
			if (!args)
				args = 1;
			bool white = false;
			for (int i = 0; i < getHeight(); i++)
			{
				for (int j = 0; j < getWidth(); j++)
				{
					if (j % args == 0)
						white = !white;
					if (white)
					{
						getImageData()[3 * ((i * getWidth()) + j)] = 255;
						getImageData()[3 * ((i * getWidth()) + j) + 1] = 255;
						getImageData()[3 * ((i * getWidth()) + j) + 2] = 255;
					}
					else
					{
						getImageData()[3 * ((i * getWidth()) + j)] = 0;
						getImageData()[3 * ((i * getWidth()) + j) + 1] = 0;
						getImageData()[3 * ((i * getWidth()) + j) + 2] = 0;
					}
				}
			}
			break;
		}
		case 2://white box at the corner, args = edge length;
		{
			for (int i = 0; i < getHeight(); i++)
			{
				for (int j = 0; j < getWidth(); j++)
				{
					if (i < args && j < args)
					{
						getImageData()[3 * ((i * getWidth()) + j)] = 255;
						getImageData()[3 * ((i * getWidth()) + j) + 1] = 255;
						getImageData()[3 * ((i * getWidth()) + j) + 2] = 255;
					}
					else
					{
						getImageData()[3 * ((i * getWidth()) + j)] = 0;
						getImageData()[3 * ((i * getWidth()) + j) + 1] = 0;
						getImageData()[3 * ((i * getWidth()) + j) + 2] = 0;
					}
				}
			}
			break;
		}
		case 3://red
		{
			for (int i = 0; i < getHeight(); i++)
			{
				for (int j = 0; j < getWidth(); j++)
				{

					getImageData()[3 * ((i * getWidth()) + j)] = 0;
					getImageData()[3 * ((i * getWidth()) + j) + 1] = 0;
					getImageData()[3 * ((i * getWidth()) + j) + 2] = 255;

				}
			}
			break;
		}
		case 4://green
		{
			for (int i = 0; i < getHeight(); i++)
			{
				for (int j = 0; j < getWidth(); j++)
				{

					getImageData()[3 * ((i * getWidth()) + j)] = 0;
					getImageData()[3 * ((i * getWidth()) + j) + 1] = 255;
					getImageData()[3 * ((i * getWidth()) + j) + 2] = 0;

				}
			}
			break;
		}
		case 5://blue
		{
			for (int i = 0; i < getHeight(); i++)
			{
				for (int j = 0; j < getWidth(); j++)
				{

					getImageData()[3 * ((i * getWidth()) + j)] = 255;
					getImageData()[3 * ((i * getWidth()) + j) + 1] = 0;
					getImageData()[3 * ((i * getWidth()) + j) + 2] = 0;

				}
			}
			break;
		}
		default:
			break;
	}
	return 0;
}

int MyImage::rgbToHsv(double r, double g, double b, vector<double> &hsv)
{
	r /= 255;
	g /= 255;
	b /= 255;
	hsv.resize(3);
	double max = (r > g ? r : g);
	max = (max > b ? max : b);
	double min = (r > g ? g : r);
	min = (min > b ? b : min);
	if (max == min)
		hsv[0] = 0;
	else if (max == r)
	{
		if (g >= b)
			hsv[0] = 60 * (g - b) / (max - min);
		else
			hsv[0] = 60 * (g - b) / (max - min) + 360;
	}
	else if (max == g)
		hsv[0] = 60 * (b - r) / (max - min) + 120;
	else
		hsv[0] = 60 * (r - g) / (max - min) + 240;
	if (max == 0)
		hsv[1] = 0;
	else 
		hsv[1] = 1 - min / max;
	hsv[2] = max;
	if (hsv[1] > 0.999)
		hsv[1] = 0.999;
	if (hsv[2] > 0.999)
		hsv[2] = 0.999;
	return 0;
}

int MyImage::countColor(vector<int> &h, vector<int> &s, vector<int> &v)
{
	h.resize(360, 0);
	s.resize(100, 0);
	v.resize(100, 0);
	vector<double>hsv;
	for (int i = 0; i < getHeight() * getWidth(); i++)
	{
		rgbToHsv((double)(unsigned char)Data[3 * i + 2], (double)(unsigned char)Data[3 * i + 1], (double)(unsigned char)Data[3 * i], hsv);
		h[(int)hsv[0]]++;
		s[(int)(hsv[1] * 100)]++;
		v[(int)(hsv[2] * 100)]++;
	}
	return 0;
}

int MyImage::findDominant(vector <int>& h, vector <int>& s, vector <int>& v, vector<int>& vect, double threshold1, double threshold2)
{
	int max = 0;
	int max_id = 0;
	int width = 30;
	for (int i = 0; i < h.size(); i++)
	{
		int cnt = 0;
		for (int j = i; j < i + width; j++)
		{
			cnt += h[j % 360];
			if (cnt >= max)
			{
				max = cnt;
				max_id = i;
			}
		}
	}
	//cout << "Dom " << max_id + width / 2 << endl;
	vect.push_back(max_id + width / 2);
	vect.push_back(width);
	/*width = 0;
	max = h[0];
	max_id = 0;
	for (int i = 1; i < 360; i++)
		if (h[i] > max)
		{
			max = h[i];
			max_id = i;
		}
	for (width = 0; width < 360 / 2; width++)
	{
		int sum = 0;
		for (int i = (max_id - width >= 0? max_id - width: 0); i < (max_id + width <= 360? max_id + width: 360); i++)
			sum += h[i];
		if (sum >= getWidth() * getHeight() * threshold1)
		{
			vect.push_back(max_id);
			vect.push_back(width);
			cout << "SUm" << sum << endl;
			break;
		}
	}*/

	width = 0;
	max = s[0];
	max_id = 0;
	for (int i = 1; i < 100; i++)
		if (s[i] > max)
		{
			max = s[i];
			max_id = i;
		}
	for (width = 0; width <= 100; width++)
	{
		int sum = 0;
		for (int i = (max_id - width >= 0 ? max_id - width : 0); i < (max_id + width <= 100 ? max_id + width : 100); i++)
			sum += s[i];
		if (sum >= getWidth() * getHeight() * threshold1)
		{
			vect.push_back(max_id);
			vect.push_back(width);
			break;
		}
	}

	width = 0;
	max = v[0];
	max_id = 0;
	for (int i = 1; i < 100; i++)
		if (v[i] > max)
		{
			max = v[i];
			max_id = i;
		}
	for (width = 0; width <= 100; width++)
	{
		int sum = 0;
		for (int i = (max_id - width >= 0 ? max_id - width : 0); i < (max_id + width <= 100 ? max_id + width : 100); i++)
			sum += v[i];
		if (sum >= getWidth() * getHeight() * threshold2)
		{
			vect.push_back(max_id);
			vect.push_back(width);
			break;
		}
	}
	cout << "Dom:" << vect[0] << " " << vect[1] << " " << vect[2] << " " << vect[3] << " " << vect[4] << " " << vect[5] << endl;
	return 0; 
}

/*int	MyImage::changeBackGround(bool mask[], MyImage &background)
{
	vector<double>hsv;
	cout << "Replaced H: " << dominant[0] - dominant[1] << " - " << dominant[0] + dominant[1] << endl;
	cout << "Replaced S: " << dominant[2] - dominant[3] << " - " << dominant[2] + dominant[3] << endl;
	cout << "Replaced V: " << dominant[4] - dominant[5] << " - " << dominant[4] + dominant[5] << endl;
	for (int i = 0; i < getHeight() * getWidth(); i++)
	{
		rgbToHsv((double)(unsigned char)Data[3 * i + 2], (double)(unsigned char)Data[3 * i + 1], (double)(unsigned char)Data[3 * i], hsv);
		if ((int)hsv[0] >= dominant[0] - dominant[1] && (int)hsv[0] <= dominant[0] + dominant[1] && 
			//(hsv[1] > 0.35 ||
			(int)(hsv[1] * 100) >= dominant[2] - dominant[3] && //(int)(hsv[1] * 100) <= dominant[2] + dominant[3] &&
			(hsv[2] > 0.5 ||
			(int)(hsv[2] * 100) >= dominant[4] - dominant[5])// && (int)(hsv[2] * 100) <= dominant[4] + dominant[5])
			)
		{
			Data[3 * i] = background.getImageData()[3 * i];
			Data[3 * i + 1] = background.getImageData()[3 * i + 1];
			Data[3 * i + 2] = background.getImageData()[3 * i + 2];
		}
		else if ((hsv[0] == 0 || (int)hsv[0] >= dominant[0] - dominant[1] && (int)hsv[0] <= dominant[0] + dominant[1]) && hsv[1] <= 0.65 && hsv[2] > 0.8)//filter out white pixels
		{
			Data[3 * i] = background.getImageData()[3 * i];
			Data[3 * i + 1] = background.getImageData()[3 * i + 1];
			Data[3 * i + 2] = background.getImageData()[3 * i + 2];
		}
		else if ((int)hsv[0] >= dominant[0] - dominant[1] && (int)hsv[0] <= dominant[0] + dominant[1] && hsv[1] > 0.7 && hsv[2] > 0.15)//filter out white pixels
		{
			Data[3 * i] = background.getImageData()[3 * i];            
			Data[3 * i + 1] = background.getImageData()[3 * i + 1];
			Data[3 * i + 2] = background.getImageData()[3 * i + 2];
		}
	}
	return 0;
}*/

int	MyImage::changeBackGround(bool mask[], MyImage& background)
{
	int antialias = 1;
	unsigned int* newdata = new unsigned int[3 * getHeight() * getWidth()];
	unsigned short* weight = new unsigned short[getHeight() * getWidth()];
	short* back = new short[getHeight() * getWidth()];
	short* fore = new short[getHeight() * getWidth()];

	memset(weight, 0, Height * Width * sizeof(unsigned short));
	memset(newdata, 0, 3 * Height * Width * sizeof(unsigned int));
	memset(back, 0, Height * Width * sizeof(short));
	memset(fore, 0, Height * Width * sizeof(short));
	for (int i = 0; i < getHeight(); i++)
	{
		for (int j = 0; j < getWidth(); j++)
		{
			int index = i * getWidth() + j;
			for (int k = i - antialias; k <= i + antialias; k++)
			{
				if (k < 0)continue;
				if (k >= Height)continue;
				for (int l = j - antialias; l <= j + antialias; l++)
				{
					if (l < 0)continue;
					if (l >= Width)continue;
					int aliasindex = k * getWidth() + l;
					if (mask[aliasindex])
					{
						back[index] = true;
						newdata[3 * index] += (unsigned char)background.getImageData()[3 * aliasindex];
						newdata[3 * index + 1] += (unsigned char)background.getImageData()[3 * aliasindex + 1];
						newdata[3 * index + 2] += (unsigned char)background.getImageData()[3 * aliasindex + 2];
						weight[index]++;
					}
					else
					{
						fore[index] = true;
						newdata[3 * index] += (unsigned char)Data[3 * aliasindex];
						newdata[3 * index + 1] += (unsigned char)Data[3 * aliasindex + 1];
						newdata[3 * index + 2] += (unsigned char)Data[3 * aliasindex + 2];
						weight[index]++;
					}
				}
			}
		}
	}
	for (int i = 0; i < Width * Height; i++)
	{
		newdata[3 * i] /= weight[i];
		newdata[3 * i + 1] /= weight[i];
		newdata[3 * i + 2] /= weight[i];
	}
	for (int i = 0; i < getHeight(); i++)
	{
		for (int j = 0; j < getWidth(); j++)
		{
			int index = i * getWidth() + j;
			if (fore[index] && back[index])
			{
				Data[3 * index] = newdata[3 * index];
				Data[3 * index + 1] = newdata[3 * index + 1];
				Data[3 * index + 2] = newdata[3 * index + 2];
			}
			else if(back[index])
			{
				Data[3 * index] = background.getImageData()[3 * index];
				Data[3 * index + 1] = background.getImageData()[3 * index + 1];
				Data[3 * index + 2] = background.getImageData()[3 * index + 2];
			}
		}
	}


	delete[]newdata;
	delete[]weight;
	delete[]fore;
	delete[]back;
	return 0;
}

int	MyImage::maskBackGround(vector<int>& dominant, bool mask[])
{
	vector<double>hsv;
	cout << "Replaced H: " << dominant[0] - dominant[1] << " - " << dominant[0] + dominant[1] << endl;
	cout << "Replaced S: " << dominant[2] - dominant[3] << " - " << dominant[2] + dominant[3] << endl;
	cout << "Replaced V: " << dominant[4] - dominant[5] << " - " << dominant[4] + dominant[5] << endl;
	for (int i = 0; i < getHeight() * getWidth(); i++)
	{
		rgbToHsv((double)(unsigned char)Data[3 * i + 2], (double)(unsigned char)Data[3 * i + 1], (double)(unsigned char)Data[3 * i], hsv);
		if ((int)hsv[0] >= dominant[0] - dominant[1] && (int)hsv[0] <= dominant[0] + dominant[1] &&
			//(hsv[1] > 0.35 ||
			(int)(hsv[1] * 100) >= dominant[2] - dominant[3] && //(int)(hsv[1] * 100) <= dominant[2] + dominant[3] &&
			(hsv[2] > 0.5 ||
			(int)(hsv[2] * 100) >= dominant[4] - dominant[5])// && (int)(hsv[2] * 100) <= dominant[4] + dominant[5])
			)
			mask[i] = 1;
		else if ((hsv[0] == 0 || (int)hsv[0] >= dominant[0] - dominant[1] && (int)hsv[0] <= dominant[0] + dominant[1]) && hsv[1] <= 0.65 && hsv[2] > 0.8)//filter out white pixels
			mask[i] = 1;
		else if ((int)hsv[0] >= dominant[0] - dominant[1] && (int)hsv[0] <= dominant[0] + dominant[1] && hsv[1] > 0.7 && hsv[2] > 0.15)//filter out white pixels
			mask[i] = 1;
	}
	return 0;
}

int	MyImage::changeDominantBright(MyImage &background)
{
	vector<double> hsv;
	for (int i = 0; i < getHeight() * getWidth(); i++)
	{
		rgbToHsv((double)(unsigned char)Data[3 * i + 2], (double)(unsigned char)Data[3 * i + 1], (double)(unsigned char)Data[3 * i], hsv);
		if (hsv[1] <= 0.3 && hsv[2] >= 0.5)
		{
			Data[3 * i] = background.getImageData()[3 * i];
			Data[3 * i + 1] = background.getImageData()[3 * i + 1];
			Data[3 * i + 2] = background.getImageData()[3 * i + 2];
		}
	}
	return 0;
}