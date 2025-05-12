/*
** EPITECH PROJECT, 2025
** bsraytracer
** File description:
** RayTracer
*/

#include "includes/RayTracer.hpp"

RayTracer::Ray::Ray()
{
    _vector = Math::Vector3D();
    _sp = Math::Point3D();
}

RayTracer::Ray::Ray(Math::Vector3D &vector, Math::Point3D &sp) : _vector(vector), _sp(sp)
{
}

RayTracer::Ray::~Ray()
{
}

RayTracer::Sphere::Sphere()
{
}

RayTracer::Sphere::~Sphere()
{
}

bool RayTracer::Sphere::hits(const RayTracer::Ray &ray)
{
    Math::Vector3D oc = ray._sp - _center;
    double a = oc.dot(ray._vector);
    double b = 2.0 * oc.dot(ray._vector);
    double c = oc.dot(oc) - _radius * _radius;
    double discriminant = b * b - 4 * a * c;
    return (discriminant >= 0);
}
