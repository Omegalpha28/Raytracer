/*
** EPITECH PROJECT, 2025
** bsraytracer
** File description:
** Vector3D
*/

#include "../includes/Vector3D.hpp"

Math::Vector3D::Vector3D() : _x(0), _y(0), _z(0)
{
}

Math::Vector3D::Vector3D(double x, double y, double z) : _x(x), _y(y), _z(z)
{
}

double Math::Vector3D::length()
{
    return sqrt(_x * _x + _y * _y + _z * _z);
}

double Math::Vector3D::dot(const Math::Vector3D &vector2)
{
    return _x * vector2._x + _y * vector2._y + _z * vector2._z;
}

Math::Point3D::Point3D(double x, double y, double z) : _x(x), _y(y), _z(z)
{
}
