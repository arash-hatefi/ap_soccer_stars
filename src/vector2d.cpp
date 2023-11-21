#include "../include/vector2d.hpp"

using namespace std;

template <typename T> 
Vector2d<T>::Vector2d() {}

template <typename T> 
Vector2d<T>::Vector2d(T _x, T _y) : x(_x), y(_y) {}

template <typename T> 
Vector2d<T> Vector2d<T>::operator+ (const Vector2d & v) {return Vector2d(x+v.x,y+v.y);}

template <typename T> 
Vector2d<T> Vector2d<T>::operator- (const Vector2d & v) {return Vector2d(x-v.x,y-v.y);}

template <typename T> 
Vector2d<T> Vector2d<T>::operator* (const Vector2d & v) {return Vector2d(x*v.x,y*v.y);}

template <typename T> 
Vector2d<T> Vector2d<T>::operator/ (const Vector2d & v) 
{
	if (v.x==T(0) || v.y==T(0)) {throw(ZERO_DEVISION_ERROR);}
	return Vector2d(x/v.x,y/v.y);
}

template <typename T> 
Vector2d<T> Vector2d<T>::operator+ (double d) {return Vector2d(x+d,y+d);}

template <typename T> 
Vector2d<T> Vector2d<T>::operator- (double d) {return Vector2d(x-d,y-d);}

template <typename T> 
Vector2d<T> Vector2d<T>::operator* (double d) {return Vector2d(x*d,y*d);}

template <typename T> 
Vector2d<T> Vector2d<T>::operator/ (double d)
{
	if (d==T(0)) {throw(ZERO_DEVISION_ERROR);}
	return Vector2d(x/d,y/d);
}

template <typename T> 
Vector2d<T> &Vector2d<T>::operator+= (const Vector2d & v)
{
	(*this) = (*this) + v;
	return (*this);
}

template <typename T> 
Vector2d<T> &Vector2d<T>::operator-= (const Vector2d & v)
{
	(*this) = (*this) - v;
	return (*this);
}

template <typename T> 
Vector2d<T> &Vector2d<T>::operator*= (const Vector2d & v)
{
	(*this) = (*this) * v;
	return (*this);
}

template <typename T> 
Vector2d<T> &Vector2d<T>::operator/= (const Vector2d & v)
{
	if (v.x==T(0) || v.y==T(0)) {throw(ZERO_DEVISION_ERROR);}
	(*this) = (*this) / v;
	return (*this);
}

template <typename T> 
Vector2d<T> &Vector2d<T>::operator+= (double d)
{
	(*this) = (*this) + d;
	return (*this);
}

template <typename T> 
Vector2d<T> &Vector2d<T>::operator-= (double d)
{
	(*this) = (*this) - d;
	return (*this);
}

template <typename T> 
Vector2d<T> &Vector2d<T>::operator*= (double d)
{
	(*this) = (*this) * d;
	return (*this);
}

template <typename T> 
Vector2d<T> &Vector2d<T>::operator/= (double d)
{
	if (d==T(0)) {throw(ZERO_DEVISION_ERROR);}
	(*this) = (*this) / d;
	return (*this);
}

template <typename T>
double Vector2d<T>::norm(int ord) {return (double) pow(pow(x, ord)+pow(y, ord), 1.0/((double) ord));}

template <typename T>
double Vector2d<T>::angle()
{
	if (x>=0 && y>=0) {return atan((double)y/(double)x);}
	else if (x>=0 && y<=0) {return 2.*PI+atan((double)y/(double)x);}
	else {return PI+atan((double)y/(double)x);}
}


template struct Vector2d<double>;
template struct Vector2d<int>;
template struct Vector2d<unsigned int>;
template struct Vector2d<float>;