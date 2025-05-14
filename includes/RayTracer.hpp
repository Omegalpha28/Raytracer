/*
** EPITECH PROJECT, 2025
** bsRay
** File description:
** Ray
*/

#pragma once
#include "Vector3D.hpp"

namespace RayTracer {

    class Ray {
        public:
            Ray();
            ~Ray();
            Ray(Math::Vector3D &vector, Math::Point3D &sp);

            Math::Vector3D _vector;
            Math::Point3D _sp;

        protected:
        private:
    };

    class Sphere {
        public:
            Sphere();
            ~Sphere();
            bool hits(const Ray &ray);

        protected:
        private:
            Math::Point3D _center;
            double _radius;
    };

    class Rectangle3D {
        public:
            Rectangle3D();
            ~Rectangle3D();

        protected:
        private:
            Math::Point3D _origin;
            Math::Vector3D _bottom_side;
            Math::Vector3D _left_side;

    };
};
