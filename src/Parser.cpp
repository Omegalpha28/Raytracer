/*
** EPITECH PROJECT, 2025
** bsraytracer
** File description:
** Parser
*/
#include "../includes/Parser.hpp"
#include "../includes/Errors.hpp"

RayTracer::Parser::Parser() : _width(0), _height(0), _fov(0), _ambientLight(0), _diffuseLight(0), _posX(0), _posY(0), _posZ(0), _rotX(0), _rotY(0), _rotZ(0)
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
        parseCameraSettings();
        parsePrimitives();
        parseLights();
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

    const libconfig::Setting &resolution = camera.lookup("resolution");
    resolution.lookupValue("width", _width);
    resolution.lookupValue("height", _height);
    const libconfig::Setting &position = camera.lookup("position");
    position.lookupValue("x", _posX);
    position.lookupValue("y", _posY);
    position.lookupValue("z", _posZ);
    const libconfig::Setting &rotation = camera.lookup("rotation");
    rotation.lookupValue("x", _rotX);
    rotation.lookupValue("y", _rotY);
    rotation.lookupValue("z", _rotZ);
    camera.lookupValue("fieldOfView", _fov);
    std::cout << "Camera resolution: " << _width << "x" << _height << "\n";
    std::cout << "Position Cam: (" << _posX << ", " << _posY << ", " << _posZ << ")\n";
    std::cout << "Rotation Cam: (" << _rotX << ", " << _rotY << ", " << _rotZ << ")\n";
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
    const libconfig::Setting &lights = _cfg.lookup("lights");

    lights.lookupValue("ambient", _ambientLight);
    lights.lookupValue("diffuse", _diffuseLight);
    if (lights.exists("point")) {
        const libconfig::Setting &points = lights["point"];
        int count = points.getLength();
        std::cout << "Number of point lights: " << count << "\n";

        for (int i = 0; i < count; ++i) {
            const libconfig::Setting &pt = points[i];
            int x, y, z;
            pt.lookupValue("x", x);
            pt.lookupValue("y", y);
            pt.lookupValue("z", z);
            std::cout << "Point light " << i << ": (" << x << ", " << y << ", " << z << ")\n";
        }
    }
    if (lights.exists("directional") && lights["directional"].getLength() > 0) {
        const libconfig::Setting &dir = lights["directional"][0];
        int dx, dy, dz;
        dir.lookupValue("x", dx);
        dir.lookupValue("y", dy);
        dir.lookupValue("z", dz);
        std::cout << "Directional light: (" << dx << ", " << dy << ", " << dz << ")\n";
    }

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

float RayTracer::Parser::getPointPosX() const
{
    return _pointPosX;
}

float RayTracer::Parser::getPointPosY() const
{
    return _pointPosY;
}

float RayTracer::Parser::getPointPosZ() const
{
    return _pointPosZ;
}

float RayTracer::Parser::getDirX() const
{
    return _dirX;
}

float RayTracer::Parser::getDirY() const
{
    return _dirY;
}

float RayTracer::Parser::getDirZ() const
{
    return _dirZ;
}
