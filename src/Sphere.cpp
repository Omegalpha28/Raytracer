/*
** EPITECH PROJECT, 2025
** bsraytracer
** File description:
** Sphere
*/

#include "../includes/RayTracer.hpp"

RayTracer::Sphere::Sphere(Math::Point3D center, double radius, Color color)
    : _center(center), _radius(radius), _color(color)
{
}

RayTracer::Sphere::~Sphere()
{
}

bool RayTracer::Sphere::hits(const RayTracer::Ray &ray, double &t)
{
    Math::Vector3D oc = ray._sp - _center;
    double a = ray._vector.dot(ray._vector);
    double b = 2.0 * oc.dot(ray._vector);
    double c = oc.dot(oc) - _radius * _radius;
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return false;
    double sqrtD = std::sqrt(discriminant);
    double t1 = (-b - sqrtD) / (2 * a);
    double t2 = (-b + sqrtD) / (2 * a);
    if (t1 > 0.001) {
        t = t1;
        return true;
    } else if (t2 > 0.001) {
        t = t2;
        return true;
    }
    return false;
}
