/*
** EPITECH PROJECT, 2025
** bsraytracer
** File description:
** Triangle
*/

#include "../includes/RayTracer.hpp"

RayTracer::Triangle::Triangle(const Math::Point3D &v0, const Math::Point3D &v1, const Math::Point3D &v2, const Color &color)
    : _v0(v0), _v1(v1), _v2(v2), _color(color)
{
    Math::Vector3D edge1 = _v1 - _v0;
    Math::Vector3D edge2 = _v2 - _v0;
    _normal = edge1.cross(edge2);
    _normal = _normal / _normal.length();
}

RayTracer::Triangle::~Triangle()
{
}

bool RayTracer::Triangle::hits(const RayTracer::Ray &ray, double &t)
{
    const double EPSILON = 1e-5;

    Math::Vector3D edge1 = _v1 - _v0;
    Math::Vector3D edge2 = _v2 - _v0;
    Math::Vector3D h = ray._vector.cross(edge2);
    double a = edge1.dot(h);
    if (std::fabs(a) < EPSILON) return false;

    double f = 1.0 / a;
    Math::Vector3D s = ray._sp - _v0;
    double u = f * s.dot(h);
    if (u < -EPSILON || u > 1.0 + EPSILON) return false;

    Math::Vector3D q = s.cross(edge1);
    double v = f * ray._vector.dot(q);
    if (v < -EPSILON || u + v > 1.0 + EPSILON) return false;

    double t2 = f * edge2.dot(q);
    if (t2 >= EPSILON) { t = t2; return true; }

    return false;
}
