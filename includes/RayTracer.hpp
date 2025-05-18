/*
** EPITECH PROJECT, 2025
** bsRay
** File description:
** Ray
*/

#pragma once
#include "Vector3D.hpp"
#include "Parser.hpp"

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

    class Color {
        public:
            Color(int r = 0, int g = 0, int b = 0, int a = 255)
                : _r(r), _g(g), _b(b), _a(a) {}
            ~Color() = default;
            int getR(void) const {
                return _r;
            }
            int getG(void) const {
                return _g;
            }
            int getB(void) const {
                return _b;
            }
            int getA(void) const {
                return _a;
            }
            void setR(int r) {
                _r = r;
            }
            void setG(int g) {
                _g = g;
            }
            void setB(int b) {
                _b = b;
            }
            void setA(int a) {
                _a = a;
            };
        private:
            int _r;
            int _g;
            int _b;
            int _a;
    };

    class Primitives {
        public:
            Primitives() = default;
            virtual ~Primitives() = default;
            virtual bool hits(const Ray &ray, double &t) = 0;
            virtual Color getColor() const = 0;
            virtual Math::Vector3D normalAt(const Math::Point3D &point) = 0;
    };

    class Light {
        public:
            Light(const Math::Point3D &pos, const Color &col)
            : _position(pos), _direction(0.0, 0.0, 0.0), _color(col) {};
            ~Light() = default;
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
            Raytracer(RayTracer::Parser &Parser);
            Raytracer();
            ~Raytracer() = default;
            void render(RayTracer::Parser &Parser);
            RayTracer::Color computeLighting(const Math::Point3D &point, std::shared_ptr<Primitives> prim, const Light &light);
        private:
            int _width;
            int _height;
            int _fieldOfView;
            Math::Point3D _cameraPosition;
    };

    class Sphere : public Primitives {
        public:
            Sphere(Math::Point3D center, double radius, Color color);
            ~Sphere();
            bool hits(const Ray &ray, double &t) override;
            Math::Vector3D normalAt(const Math::Point3D &point) override {
                Math::Vector3D n = point - _center;
                return n / n.length();
            };
            Color getColor() const override { return _color; };
        protected:
        private:
            Math::Point3D _center;
            double _radius;
            Color _color;
    };

    class Plane : public Primitives {
        public:
            Plane();
            Plane(char axis, double position, Color color);
            ~Plane();
            bool hits(const Ray &ray, double &t) override;
            Math::Vector3D normalAt(const Math::Point3D &point) override {
                if (_axis == 'X') return Math::Vector3D(1, 0, 0);
                else if (_axis == 'Y') return Math::Vector3D(0, 1, 0);
                else return Math::Vector3D(0, 0, 1);
            }

        private:
            char _axis;
            double _position;
            Color _color;
    };

    class Triangle : public Primitives {
        public:
            Triangle();
            Triangle(const Math::Point3D &v0, const Math::Point3D &v1, const Math::Point3D &v2, const Color &color);
            ~Triangle();
            bool hits(const Ray &ray, double &t) override;
            Math::Vector3D normalAt(const Math::Point3D &point) override {
                return _normal;
            }
            Color getColor() const override { return _color; }

        private:
            Math::Point3D _v0;
            Math::Point3D _v1;
            Math::Point3D _v2;
            Math::Vector3D _normal;
            Color _color;
    };

    class Rectangle3D : public Primitives {
        public:
            Rectangle3D();
            Rectangle3D(const Math::Point3D &origin, const Math::Vector3D &bottom_side, 
                        const Math::Vector3D &left_side, const Color &color);
            ~Rectangle3D();
            bool hits(const Ray &ray, double &t) override;
            Math::Vector3D normalAt(const Math::Point3D &point) override;
            Color getColor() const override { return _color; };

        protected:
        private:
            Math::Point3D _origin;
            Math::Vector3D _bottom_side;
            Math::Vector3D _left_side;
            Color _color;
            std::shared_ptr<Triangle> _triangle1;
            std::shared_ptr<Triangle> _triangle2;
    };
};
