/*
** EPITECH PROJECT, 2025
** bsraytracer
** File description:
** Cube
*/

#include "../includes/RayTracer.hpp"

RayTracer::Cube::Cube(const Math::Point3D &max_point, const Math::Point3D &min_point, const Color &color)
    : _max_point(max_point), _min_point(min_point), _color(color)
{
    // Face avant (front) - plan Z minimum
    _rectangle1 = std::make_shared<Rectangle3D>(
        Math::Point3D(_max_point._x, _max_point._y, _max_point._z),       // origine
        Math::Vector3D(_min_point._x - _max_point._x, 0, 0),              // côté horizontal
        Math::Vector3D(0, _min_point._y - _max_point._y, 0),              // côté vertical
        _color
    );

    // Face arrière (back) - plan Z maximum
    _rectangle2 = std::make_shared<Rectangle3D>(
        Math::Point3D(_max_point._x, _max_point._y, _min_point._z),
        Math::Vector3D(0, _min_point._y - _max_point._y, 0),
        Math::Vector3D(_min_point._x - _max_point._x, 0, 0),
        _color
    );

    // Face gauche (left) - plan X minimum
    _rectangle3 = std::make_shared<Rectangle3D>(
        Math::Point3D(_max_point._x, _max_point._y, _max_point._z),
        Math::Vector3D(0, _min_point._y - _max_point._y, 0),
        Math::Vector3D(0, 0, _min_point._z - _max_point._z),
        _color
    );

    // Face droite (right) - plan X maximum
    _rectangle4 = std::make_shared<Rectangle3D>(
        Math::Point3D(_min_point._x, _max_point._y, _max_point._z),
        Math::Vector3D(0, 0, _min_point._z - _max_point._z),
        Math::Vector3D(0, _min_point._y - _max_point._y, 0),
        _color
    );

    // Face bas (bottom) - plan Y minimum
    _rectangle5 = std::make_shared<Rectangle3D>(
        Math::Point3D(_max_point._x, _max_point._y, _max_point._z),
        Math::Vector3D(0, 0, _min_point._z - _max_point._z),
        Math::Vector3D(_min_point._x - _max_point._x, 0, 0),
        _color
    );

    // Face haut (top) - plan Y maximum
    _rectangle6 = std::make_shared<Rectangle3D>(
        Math::Point3D(_max_point._x, _min_point._y, _max_point._z),
        Math::Vector3D(_min_point._x - _max_point._x, 0, 0),
        Math::Vector3D(0, 0, _min_point._z - _max_point._z),
        _color
    );
}

RayTracer::Cube::~Cube()
{
}

bool RayTracer::Cube::hits(const Ray &ray, double &t)
{
    double closest_t = std::numeric_limits<double>::max();
    bool hit_anything = false;

    std::vector<std::shared_ptr<Rectangle3D>> rectangles = {
        _rectangle1, _rectangle2, _rectangle3,
        _rectangle4, _rectangle5, _rectangle6
    };

    for (auto &rect : rectangles) {
        double temp_t;
        if (rect->hits(ray, temp_t) && temp_t < closest_t) {
            closest_t = temp_t;
            hit_anything = true;
        }
    }

    if (hit_anything) t = closest_t;

    return hit_anything;
}

Math::Vector3D RayTracer::Cube::normalAt(const Math::Point3D &point)
{
    std::vector<std::shared_ptr<Rectangle3D>> rectangles = {
        _rectangle1, _rectangle2, _rectangle3,
        _rectangle4, _rectangle5, _rectangle6
    };

    double min_distance = std::numeric_limits<double>::max();
    Math::Vector3D best_normal;

    for (auto &rect : rectangles) {
        Math::Vector3D normal = rect->normalAt(point);

        // Project the point onto the plane of the rectangle
        // Check how close the point is to the rectangle's plane
        double distance = std::abs((point - rect->getOrigin()).dot(normal));
        if (distance < min_distance) {
            min_distance = distance;
            best_normal = normal;
        }
    }

    return best_normal;
}
