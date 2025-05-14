/*
** EPITECH PROJECT, 2025
** bsRay
** File description:
** Ray
*/

#pragma once
#include "Vector3D.hpp"

namespace RayTracer {

    class color {
        public:
            color();
            ~color();
            color(int r, int g, int b, int a);
            int getR(void) {
                return _r;
            };
            int getG(void) {
                return _g;
            };
            int getB(void) {
                return _b;
            };
            int getA(void) {
                return _a;
            };
            void setR(int r) {
                _r = r;
            };
            void setG(int g) {
                _g = g;
            };
            void setB(int b) {
                _b = b;
            };
            void setA(int a) {
                _a = a;
            };
        private:
            int _r;
            int _g;
            int _b;
            int _a;
    };

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
            color _color;
    };

    class Light {
        public:
            Light();
            ~Light();
        private:
            Math::Point3D _position;
            color _color;
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
            color _color;
    };
};
