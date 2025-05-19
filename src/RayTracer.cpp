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
