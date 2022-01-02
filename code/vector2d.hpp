#ifndef __VECTOR2D__
#define __VECTOR2D__

#include "./src/rsdl.hpp"
#include <math.h>
#include <bits/stdc++.h>

using namespace std;

const string ZERO_DEVISION_ERROR = "Zero devision occured!";
const double PI = 3.1415;

template <typename T>
struct Vector2d
{
	T x;
	T y;
	Vector2d();
	Vector2d(T _x, T _y);
	Vector2d operator+ (const Vector2d & v);
	Vector2d operator- (const Vector2d & v);
	Vector2d operator* (const Vector2d & v);
	Vector2d operator/ (const Vector2d & v);
	Vector2d operator+ (double d);
	Vector2d operator- (double d);
	Vector2d operator* (double d);
	Vector2d operator/ (double d);
	Vector2d &operator+= (const Vector2d & v);
	Vector2d &operator-= (const Vector2d & v);
	Vector2d &operator*= (const Vector2d & v);
	Vector2d &operator/= (const Vector2d & v);
	Vector2d &operator+= (double d);
	Vector2d &operator-= (double d);
	Vector2d &operator*= (double d);
	Vector2d &operator/= (double d);
	double norm(int ord=2);
	double angle();
};

template <typename T> 
T dot(Vector2d<T> v1, Vector2d<T> v2) 
{
	Vector2d<T> product = v1*v2;
	return product.x + product.y;
}

template <typename T>
double distance(Vector2d<T> v1, Vector2d<T> v2) 
{
	return (v1-v2).norm(2);
}

template <typename T>
double get_angle(Vector2d<T> v1, Vector2d<T> v2) 
{
	if (v1.norm()==0 || v2.norm()==0) {return 0;}
	return acos(((double)dot(v1,v2))/v1.norm()/v2.norm());
}

template <typename T1, typename T2>
Vector2d<T1> cast(Vector2d<T2> v)
{
	return Vector2d<T1>(v.x, v.y);
}

template <typename T>
Vector2d<T> point2vector(Point point) {return Vector2d<T>(point.x, point.y);}

#endif