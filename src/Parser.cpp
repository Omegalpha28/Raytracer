/*
** EPITECH PROJECT, 2025
** bsraytracer
** File description:
** Parser
*/
#include "../includes/Parser.hpp"
#include "../includes/Errors.hpp"

RayTracer::Parser::Parser() : _width(0), _height(0), _fov(0), _ambientLight(0), _diffuseLight(0)
{}

RayTracer::Parser::~Parser()
{}

void RayTracer::Parser::displayHelp() const
{
    std::cout << "USAGE: ./raytracer <SCENE_FILE>" << std::endl;
    std::cout << "  SCENE_FILE: scene configuration" << std::endl;
}

int RayTracer::Parser::parseConfigFile(const std::string &filePath)
{
    try {
        _cfg.readFile(filePath.c_str());
    } catch (const libconfig::FileIOException &fioex) {
        try {
            throw RayTracer::ParseError("I/O error while reading file");
        } catch (const RayTracer::ParseError &error) {
            std::cerr << error.what() << std::endl;
        }
        return 84;
    } catch (const libconfig::ParseException &pex) {
        try {
            std::string errorMsg = "Parse error at " + std::string(pex.getFile()) + ":" + 
                                  std::to_string(pex.getLine()) + " - " + pex.getError();
            throw RayTracer::ParseError(errorMsg);
        } catch (const RayTracer::ParseError &error) {
            std::cerr << error.what() << std::endl;
        }
        return 84;
    }
    try {
        if (parseCameraSettings() != 0)
            return 84;
        if (parsePrimitives() != 0)
            return 84;
        if (parseLights() != 0)
            return 84;
    } catch (const libconfig::SettingNotFoundException &nfex) {
        try {
            throw RayTracer::ParseError(std::string("A setting was not found: ") + nfex.getPath());
        } catch (const RayTracer::ParseError &error) {
            std::cerr << error.what() << std::endl;
        }
        return 84;
    }
    return 0;
}

int RayTracer::Parser::parseCameraSettings()
{
    const libconfig::Setting &camera = _cfg.lookup("camera");

    camera.lookupValue("resolution.width", _width);
    camera.lookupValue("resolution.height", _height);
    camera.lookupValue("fieldOfView", _fov);
    std::cout << "Camera resolution: " << _width << "x" << _height << "\n";
    std::cout << "Field of View: " << _fov << "\n";
    return 0;
}

int RayTracer::Parser::parsePrimitives()
{
    const libconfig::Setting &spheres = _cfg.lookup("primitives.spheres");
    int sphereCount = spheres.getLength();
    std::cout << "Number of spheres: " << sphereCount << "\n";

    for (int i = 0; i < sphereCount; ++i) {
        const libconfig::Setting &s = spheres[i];
        int x, y, z, r;
        s.lookupValue("x", x);
        s.lookupValue("y", y);
        s.lookupValue("z", z);
        s.lookupValue("r", r);
        std::cout << "Sphere " << i << " at (" << x << ", " << y << ", " << z
                  << ") with radius " << r << "\n";
        const libconfig::Setting &color = s["color"];
        int cr, cg, cb;
        color.lookupValue("r", cr);
        color.lookupValue("g", cg);
        color.lookupValue("b", cb);
        std::cout << "Color: (" << cr << ", " << cg << ", " << cb << ")\n";
    }
    return 0;
}

int RayTracer::Parser::parseLights()
{
    _cfg.lookupValue("lights.ambient", _ambientLight);
    _cfg.lookupValue("lights.diffuse", _diffuseLight);
    std::cout << "Ambient light: " << _ambientLight << ", Diffuse light: " << _diffuseLight << "\n";
    return 0;
}

int RayTracer::Parser::getWidth() const
{
    return _width;
}

int RayTracer::Parser::getHeight() const
{
    return _height;
}

float RayTracer::Parser::getFov() const
{
    return _fov;
}

float RayTracer::Parser::getAmbientLight() const
{
    return _ambientLight;
}

float RayTracer::Parser::getDiffuseLight() const
{
    return _diffuseLight;
}