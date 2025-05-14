/*
** EPITECH PROJECT, 2025
** bsraytracer
** File description:
** Vector3D
*/

#pragma once
#include "includes.hpp"

namespace Math {

    class Vector3D {
    public:
        double _x;
        double _y;
        double _z;
    
        Vector3D();
        Vector3D(double x, double y, double z);
        ~Vector3D() = default;
    
        Vector3D operator+(const Vector3D &other) const {
            return Vector3D(_x + other._x, _y + other._y, _z + other._z);
        }
        Vector3D operator-(const Vector3D &other) const {
            return Vector3D(_x - other._x, _y - other._y, _z - other._z);
        }
        Vector3D operator*(double scalar) const {
            return Vector3D(_x * scalar, _y * scalar, _z * scalar);
        }
        Vector3D operator/(double scalar) const {
            return Vector3D(_x / scalar, _y / scalar, _z / scalar);
        }
    
        Vector3D& operator+=(const Vector3D &other) {
            _x += other._x; _y += other._y; _z += other._z;
            return *this;
        }
        Vector3D& operator-=(const Vector3D &other) {
            _x -= other._x; _y -= other._y; _z -= other._z;
            return *this;
        }
        Vector3D& operator*=(double scalar) {
            _x *= scalar; _y *= scalar; _z *= scalar;
            return *this;
        }
        Vector3D& operator/=(double scalar) {
            _x /= scalar; _y /= scalar; _z /= scalar;
            return *this;
        }
    
        double length();
    
        double dot(const Vector3D &other) const;
    };

    class Point3D {
        public:
            double _x, _y, _z;

            Point3D() : _x(0), _y(0), _z(0) {}
            Point3D(double x, double y, double z);
            ~Point3D() = default;
    };

    inline Vector3D operator-(const Point3D &a, const Point3D &b) {
        return Vector3D(a._x - b._x, a._y - b._y, a._z - b._z);
    }
    
    inline Point3D operator+(const Point3D &p, const Vector3D &v) {
        return Point3D(p._x + v._x, p._y + v._y, p._z + v._z);
    }

}
