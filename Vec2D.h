#ifndef VEC2D
#define VEC2D
#include <iostream>
#include <algorithm>
#include <math.h>
#include <random>
#include <chrono>

using namespace std;

template <class Type> class Vec {
    // Data
    public:
        Type x,y;

    //Methods
    public:
        // Constructors
        Vec() { }

        Vec(const Type a, const Type b) {
            x=a;
            y=b;
        }

        void set_values(const Type a, const Type b) {
            x=a;
            y=b;
        }

        void scale_with(const Vec<double> v) {
            x *= v.x;
            y *= v.y;
        }

        void VDiv(const Vec<Type>v, const int a, const int b) {
            x = v.x/a;
            y = v.y/b;
        }

        double DistFrom(const Vec<Type>v){
            return sqrt(pow(x-v.x,2)+pow((y-v.y),2));
        }

        Type VProd() {
            return (x*y);
        }

        Type VLen() {
            return sqrt(x*x+y*y);
        }

        Type VLenSQ() {
            return (x*x+y*y);
        }

        Type VCsum() {
            return (x+y);
        }

        Vec<Type> operator+(const Vec<Type> &v) {
            Type a = x+v.x;
            Type b = y+v.y;
            return Vec(a,b);
        }

        Vec<Type> operator-(const Vec<Type> &v) {
            Type a = x-v.x;
            Type b = y-v.y;
            return Vec(a,b);
        }

        double operator*(const Vec<Type> v) {
            return (x*v.x+y*v.y);
        }

        Vec<Type> operator*(Type s) {
            Type a = x*s;
            Type b = y*s;
            return Vec(a,b);
        }

        friend Vec<Type> operator*(Type s,Vec<Type> v) {
            return Vec<Type>(s*v.x,s*v.y);
    }
};
#endif
