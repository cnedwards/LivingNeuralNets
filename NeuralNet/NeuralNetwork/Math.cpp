#include "Math.hpp"

double sigmoidValue(double x)
{
	return 1.0 / (1.0 + pow(M_E, -x));
}

bool randBool()
{
	return rand() % 2;
}

bool randDecimal()
{
	return rand()/RAND_MAX;
}

///returns 1 or -1
int sign()
{
	if (randBool())
		return 1;
	else
		return -1;
}

bool XOR(bool arg0, bool arg1)
{
	if (arg0 ==0 && arg1==0)
		return 0;
	if (arg0 ==1 && arg1==0)
		return 1;
	if (arg0 ==0 && arg1==1)
		return 1;
	if (arg0 ==1 && arg1==1)
		return 0;
}

//returns a decimal int that is binary
int base10ToBinary(int value)
{
	std::stringstream ss;

    for(int i=0; value > 0; i++) 
	{
		ss<<value%2;
		value /= 2;
    }
	int toReturn;
	ss>>toReturn;
	return toReturn;
}

std::vector<bool> binaryInBase10ToVector(int value)
{
	std::vector<bool> toReturn;

    for(int loop=0; value > 0; loop++) 
	{
		toReturn.push_back(value%10);
		value /= 10;
    }
	return toReturn;
}

double normalize(double arg, double min, double max)
{
	return (arg-min)/(max-min);
}

///Distance Formula
double distance(double x1, double y1, double x2, double y2)
{
	return sqrt(pow(x1-x2,2) + pow(y1-y2,2));
}

double getAngleBetweenTwoVectors(double xOrigin, double yOrigin, double x1, double y1, double x2, double y2)
{
	//Angle=arccos(abs(dot product/(magnitude*magnitude)))
	double vectorX1=x1-xOrigin, vectorY1=y1-yOrigin;
	double vectorX2=x2-xOrigin, vectorY2=y2-yOrigin;
	double dotProduct=vectorX1*vectorX2+vectorY1*vectorY2;
	double vector1Magnitude=sqrt(pow(vectorX1, 2)+ pow(vectorY1, 2)), vector2Magnitude=sqrt(pow(vectorX2, 2)+ pow(vectorY2, 2));
	return acos(dotProduct/(vector1Magnitude*vector2Magnitude));
}

double getSignedAngleBetweenTwoVectors(double xOrigin, double yOrigin, double x1, double y1, double x2, double y2)
{
	double vectorX1=x1-xOrigin, vectorY1=y1-yOrigin;
	double vectorX2=x2-xOrigin, vectorY2=y2-yOrigin;
	return atan2( (vectorX1*vectorY2 - vectorY1*vectorX2) , (vectorX1*vectorX2 + vectorY1*vectorY2) );
}