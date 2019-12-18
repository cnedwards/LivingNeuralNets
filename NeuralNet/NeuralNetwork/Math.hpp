#ifndef MATH_HPP
#define MATH_HPP

#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <sstream>
#include <iostream>
#include <vector>

double sigmoidValue(double x);

bool randBool();

bool randDecimal();

///returns 1 or -1
int sign();

bool XOR(bool arg0, bool arg1);

//Returns a decimal int
int base10ToBinary(int value);

//Take a binary value as an base 10 integer
std::vector<bool> binaryInBase10ToVector(int value);

///Normalizes between 0 and 1
double normalize(double arg, double min, double max); //Untested

///Distance Formula
double distance(double x1, double y1, double x2, double y2);

//Radians
double getAngleBetweenTwoVectors(double xOrigin, double yOrigin, double x1, double y1, double x2, double y2);
double getSignedAngleBetweenTwoVectors(double xOrigin, double yOrigin, double x1, double y1, double x2, double y2);

#endif //MATH_HPP