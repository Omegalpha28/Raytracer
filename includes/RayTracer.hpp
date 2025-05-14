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

    class Primitives {
        public:
            Primitives() = default;
            virtual ~Primitives() = default;
            virtual bool hits(const Ray &ray) = 0;
            virtual Math::Vector3D normalAt(const Math::Point3D &point) = 0;
    };

    class Color {
        public:
            Color(int r = 0, int g = 0, int b = 0, int a = 255)
                : _r(r), _g(g), _b(b), _a(a) {}
            ~Color() = default;
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

    class Light {
        public:
            Light();
            ~Light();
            Math::Vector3D getDirectionTo(const Math::Point3D &point) const {
                Math::Vector3D dir = _position - point;
                return dir / dir.length();
            };
        private:
            Math::Point3D _position;
            Math::Vector3D _direction;
            Color _color;
    };

    class Raytracer {
        public:
            Raytracer();
            ~Raytracer();
            void init();
            void run();
            RayTracer::Color computeLighting(const Math::Point3D &point, std::shared_ptr<Primitives> prim, const Light &light);
        private:
            int _width;
            int _height;
            int _fieldOfView;
            Math::Point3D _cameraPosition;
    };

    class Sphere : public Primitives {
        public:
            Sphere();
            ~Sphere();
            bool hits(const Ray &ray) override;
            Math::Vector3D normalAt(const Math::Point3D &point) override {
                Math::Vector3D n = point - _center;
                return n / n.length();
            }
        protected:
        private:
            Math::Point3D _center;
            double _radius;
            Color _color;
    };

    class Rectangle3D : public Primitives {
        public:
            Rectangle3D();
            ~Rectangle3D();
            bool hits(const Ray &ray) override;
            Math::Vector3D normalAt(const Math::Point3D &point) override {
                Math::Vector3D n(0, 1, 0);
                return n;
            }

        protected:
        private:
            Math::Point3D _origin;
            Math::Vector3D _bottom_side;
            Math::Vector3D _left_side;
            Color _color;
    };
};
