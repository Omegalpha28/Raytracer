/*
** EPITECH PROJECT, 2025
** bsraytracer
** File description:
** RayTracer
*/

#include "../includes/RayTracer.hpp"

RayTracer::Color RayTracer::Raytracer::computeLighting(
    const Math::Point3D &point,
    std::shared_ptr<Primitives> prim,
    std::shared_ptr<RayTracer::ILights> light,
    std::shared_ptr<RayTracer::ILights> light2,
    RayTracer::Parser &Parser
) {
    Math::Point3D lightPos(Parser.getPointPosX(), Parser.getPointPosY(), Parser.getPointPosZ());
    Math::Vector3D normal = prim->normalAt(point);
    Math::Vector3D lightDir = (lightPos - point) / (lightPos - point).length();
    double diffuse = std::max(0.0, normal.dot(lightDir));
    RayTracer::Color base = prim->getColor();
    double ambientIntensity;
    double diffuseIntensity;

    if (light->getIntensity() > light2->getIntensity()) {
        ambientIntensity = light2->getIntensity();
        diffuseIntensity = light->getIntensity();
    } else {
        ambientIntensity = light->getIntensity();
        diffuseIntensity = light2->getIntensity();
    }

    int r = std::min(255, static_cast<int>(base.getR() * (ambientIntensity + diffuse * diffuseIntensity)));
    int g = std::min(255, static_cast<int>(base.getG() * (ambientIntensity + diffuse * diffuseIntensity)));
    int b = std::min(255, static_cast<int>(base.getB() * (ambientIntensity + diffuse * diffuseIntensity)));

    return RayTracer::Color(r, g, b, base.getA());
}

void RayTracer::Raytracer::render(RayTracer::Parser &Parser)
{
    _width = Parser.getWidth();
    _height = Parser.getHeight();
    _fieldOfView = Parser.getFov();
    _cameraPosition = Math::Point3D( Parser.getCameraPosX(), Parser.getCameraPosY(), Parser.getCameraPosZ());
    std::cout << "Camera position: " << _cameraPosition._x << ", " << _cameraPosition._y << ", " << _cameraPosition._z << "\n";
    std::vector<std::shared_ptr<Primitives>> scene = Parser.getScene();

    Math::Point3D lightPos(Parser.getPointPosX(), Parser.getPointPosY(), Parser.getPointPosZ());
    Color lightColor(255, 255, 255);
    std::shared_ptr<RayTracer::ILights> light = std::make_shared<RayTracer::Light>(lightPos, lightColor, Parser.getDiffuseLight());
    std::shared_ptr<RayTracer::ILights> light2 = std::make_shared<RayTracer::AmbientLight>(lightPos, lightColor, Parser.getAmbientLight());
    std::ofstream ppm("output.ppm");
    ppm << "P3\n" << _width << " " << _height << "\n255\n";

    for (int y = 0; y < _height; ++y) {
        for (int x = 0; x < _width; ++x) {
            double px = (2 * ((x + 0.5) / (double)_width) - 1) * tan(_fieldOfView * 0.5 * M_PI / 180.0) * _width / (double)_height;
            double py = (1 - 2 * ((y + 0.5) / (double)_height)) * tan(_fieldOfView * 0.5 * M_PI / 180.0);
            Math::Vector3D dir(px, py, -1);
            dir = dir / dir.length();
            Ray ray(dir, _cameraPosition);
            double closestT = std::numeric_limits<double>::max();
            std::shared_ptr<Primitives> closest = nullptr;
            for (auto &obj : scene) {
                double t;
                if (obj->hits(ray, t) && t < closestT) {
                    closestT = t;
                    closest = obj;
                }
            }
            Color color(0, 0, 0);
            if (closest) {
                Math::Point3D hitPoint = _cameraPosition + dir * closestT;
                color = computeLighting(hitPoint, closest, light, light2, Parser);
            }
            ppm << color.getR() << " " << color.getG() << " " << color.getB() << " ";
        }
        ppm << "\n";
    }
    ppm.close();
}

RayTracer::Raytracer::Raytracer(RayTracer::Parser &Parser)
{
    _width = Parser.getWidth();
    _height = Parser.getHeight();
    _fieldOfView = Parser.getFov();
    _cameraPosition = Math::Point3D(0.0, 0.0, 0.0);
}
