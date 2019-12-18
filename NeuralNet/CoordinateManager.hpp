#ifndef COORDINATEMANAGER_HPP
#define COORDINATEMANAGER_HPP

///Flips the inverted y axis of SFML into the cartesian system of Box2D
 float inline flipY(float coord) {return coord*-1;}
 float inline radianToDegree(float radian) {return radian* (180/3.14159265359);}
 float inline degreeToRadian(float degree) {return degree* (3.14159265359/180);}
 const float fScale=30.f;
 const int iScale=30;

#endif //COORDINATEMANAGER_HPP