/*
** EPITECH PROJECT, 2025
** bsraytracer
** File description:
** RayTracer
*/

#include "../includes/RayTracer.hpp"

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

RayTracer::Sphere::Sphere(Math::Point3D center, double radius, Color color)
    : _center(center), _radius(radius), _color(color)
{
}

RayTracer::Sphere::~Sphere()
{
}

bool RayTracer::Sphere::hits(const RayTracer::Ray &ray)
{
    Math::Vector3D oc = ray._sp - _center;
    double a = ray._vector.dot(ray._vector);
    double b = 2.0 * oc.dot(ray._vector);
    double c = oc.dot(oc) - _radius * _radius;
    double discriminant = b * b - 4 * a * c;
    return (discriminant >= 0);
}

RayTracer::Plane::Plane(char axis, double position, Color color)
    : _axis(axis), _position(position), _color(color)
{
}

RayTracer::Plane::~Plane()
{
}

bool RayTracer::Plane::hits(const RayTracer::Ray &ray)
{
    double component;

    if      (_axis == 'X') component = ray._vector._x;
    else if (_axis == 'Y') component = ray._vector._y;
    else if (_axis == 'Z') component = ray._vector._z;

    if (std::fabs(component) < 1e-8) return false;
    double t;

    if      (_axis == 'X') t = (_position - ray._sp._x) / ray._vector._x;
    else if (_axis == 'Y') t = (_position - ray._sp._y) / ray._vector._y;
    else if (_axis == 'Z') t = (_position - ray._sp._z) / ray._vector._z;

    return (t >= 0);
}

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

bool RayTracer::Triangle::hits(const RayTracer::Ray &ray)
{
    Math::Vector3D edge1 = _v1 - _v0;
    Math::Vector3D edge2 = _v2 - _v0;
    Math::Vector3D h = ray._vector.cross(edge2);
    double a = edge1.dot(h);

    if (std::fabs(a) < 1e-8) return false;

    double f = 1.0 / a;
    Math::Vector3D s = ray._sp - _v0;
    double u = f * s.dot(h);
    if (u < 0.0 || u > 1.0) return false;

    Math::Vector3D q = s.cross(edge1);
    double v = f * ray._vector.dot(q);
    if (v < 0.0 || u + v > 1.0) return false;

    double t = f * edge2.dot(q);
    return (t >= 0.0);
}

RayTracer::Rectangle3D::Rectangle3D(const Math::Point3D &origin,
                                    const Math::Vector3D &bottom_side,
                                    const Math::Vector3D &left_side,
                                    const Color &color)
    : _origin(origin), _bottom_side(bottom_side),
        _left_side(left_side), _color(color)
{
    Math::Point3D v0 = _origin;
    Math::Point3D v1 = _origin + _bottom_side;
    Math::Point3D v2 = _origin + _left_side;
    Math::Point3D v3 = _origin + _bottom_side + _left_side;

    _triangle1 = std::make_shared<Triangle>(v0, v1, v2, _color);
    _triangle2 = std::make_shared<Triangle>(v1, v3, v2, _color);
}

RayTracer::Rectangle3D::~Rectangle3D()
{
}

bool RayTracer::Rectangle3D::hits(const RayTracer::Ray &ray)
{
    return (_triangle1->hits(ray) || _triangle2->hits(ray));
}

Math::Vector3D RayTracer::Rectangle3D::normalAt(const Math::Point3D &point)
{
    Math::Vector3D normal = _bottom_side.cross(_left_side);
    return normal / normal.length();
}
