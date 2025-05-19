/*
** EPITECH PROJECT, 2025
** bsraytracer
** File description:
** Plane
*/

#include "../includes/RayTracer.hpp"

RayTracer::Plane::Plane(char axis, double position, Color color)
    : _axis(axis), _position(position), _color(color)
{
}

RayTracer::Plane::~Plane()
{
}

bool RayTracer::Plane::hits(const RayTracer::Ray &ray, double &t)
{
    double component;

    if      (_axis == 'X') component = ray._vector._x;
    else if (_axis == 'Y') component = ray._vector._y;
    else if (_axis == 'Z') component = ray._vector._z;

    if (std::fabs(component) < 1e-8) return false;

    if      (_axis == 'X') t = (_position - ray._sp._x) / ray._vector._x;
    else if (_axis == 'Y') t = (_position - ray._sp._y) / ray._vector._y;
    else if (_axis == 'Z') t = (_position - ray._sp._z) / ray._vector._z;

    return (t >= 0);
}
