/*
** EPITECH PROJECT, 2025
** bsraytracer
** File description:
** Rectangle3D
*/

#include "../includes/RayTracer.hpp"

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

bool RayTracer::Rectangle3D::hits(const RayTracer::Ray &ray, double &t)
{
    return (_triangle1->hits(ray, t) || _triangle2->hits(ray, t));
}

Math::Vector3D RayTracer::Rectangle3D::normalAt(const Math::Point3D &point)
{
    Math::Vector3D normal = _bottom_side.cross(_left_side);
    return normal / normal.length();
}
