/*
 EPITECH PROJECT, 2025
 bsraytracer
 File description:
 Parser
*/
#include "../includes/RayTracer.hpp"
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
    _scene.clear();
    const libconfig::Setting &root = _cfg.lookup("primitives");
    // === Spheres ===
    if (root.exists("spheres")) {
        const libconfig::Setting &spheres = root["spheres"];
        for (int i = 0; i < spheres.getLength(); ++i) {
            const libconfig::Setting &s = spheres[i];
            int x, y, z, r;
            int cr, cg, cb;
            s.lookupValue("x", x);
            s.lookupValue("y", y);
            s.lookupValue("z", z);
            s.lookupValue("r", r);
            const libconfig::Setting &color = s["color"];
            color.lookupValue("r", cr);
            color.lookupValue("g", cg);
            color.lookupValue("b", cb);
            _scene.push_back(std::make_shared<Sphere>(
                Math::Point3D(x, y, z),
                static_cast<double>(r),
                Color(cr, cg, cb)
            ));
        }
    }
    // === Planes ===
    if (root.exists("planes")) {
        const libconfig::Setting &planes = root["planes"];
        for (int i = 0; i < planes.getLength(); ++i) {
            const libconfig::Setting &p = planes[i];
            std::string axis;
            double position;
            int cr, cg, cb;
            p.lookupValue("axis", axis);
            p.lookupValue("position", position);
            const libconfig::Setting &color = p["color"];
            color.lookupValue("r", cr);
            color.lookupValue("g", cg);
            color.lookupValue("b", cb);
            _scene.push_back(std::make_shared<Plane>(
                axis[0], position,
                Color(cr, cg, cb)
            ));
        }
    }
    // === Rectangles ===
    if (root.exists("rectangles")) {
        const libconfig::Setting &rects = root["rectangles"];
        for (int i = 0; i < rects.getLength(); ++i) {
            const libconfig::Setting &r = rects[i];
            const libconfig::Setting &origin = r["origin"];
            const libconfig::Setting &bottom = r["bottom_side"];
            const libconfig::Setting &left = r["left_side"];
            const libconfig::Setting &color = r["color"];
            Math::Point3D o(
                origin["x"], origin["y"], origin["z"]
            );
            Math::Vector3D b(
                bottom["x"], bottom["y"], bottom["z"]
            );
            Math::Vector3D l(
                left["x"], left["y"], left["z"]
            );
            int cr, cg, cb;
            color.lookupValue("r", cr);
            color.lookupValue("g", cg);
            color.lookupValue("b", cb);
            _scene.push_back(std::make_shared<Rectangle3D>(
                o, b, l, Color(cr, cg, cb)
            ));
        }
    }
    // === Cubes ===
    if (root.exists("cubes")) {
        const libconfig::Setting &cubes = root["cubes"];
        for (int i = 0; i < cubes.getLength(); ++i) {
            const libconfig::Setting &c = cubes[i];
            const libconfig::Setting &max = c["max"];
            const libconfig::Setting &min = c["min"];
            const libconfig::Setting &color = c["color"];

            int maxX, maxY, maxZ, minX, minY, minZ;
            max.lookupValue("x", maxX);
            max.lookupValue("y", maxY);
            max.lookupValue("z", maxZ);
            min.lookupValue("x", minX);
            min.lookupValue("y", minY);
            min.lookupValue("z", minZ);

            Math::Point3D max_point(maxX, maxY, maxZ);
            Math::Point3D min_point(minX, minY, minZ);

            int cr, cg, cb;
            color.lookupValue("r", cr);
            color.lookupValue("g", cg);
            color.lookupValue("b", cb);

            _scene.push_back(std::make_shared<Cube>(
                max_point, min_point, Color(cr, cg, cb)
            ));
        }
    }
    std::cout << "Primitives parsed" << std::endl;
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
            _pointPosX = x;
            _pointPosY = y;
            _pointPosZ = z;
            std::cout << "Point light " << i << ": (" << x << ", " << y << ", " << z << ")\n";
        }
    }
    if (lights.exists("directional") && lights["directional"].getLength() > 0) {
        const libconfig::Setting &dir = lights["directional"][0];
        int dx, dy, dz;
        dir.lookupValue("x", dx);
        dir.lookupValue("y", dy);
        dir.lookupValue("z", dz);
        _dirX = dx;
        _dirY = dy;
        _dirZ = dz;
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

double RayTracer::Parser::getFov() const
{
    return _fov;
}

double RayTracer::Parser::getAmbientLight() const
{
    return _ambientLight;
}

double RayTracer::Parser::getDiffuseLight() const
{
    return _diffuseLight;
}

double RayTracer::Parser::getPointPosX() const
{
    return _pointPosX;
}

double RayTracer::Parser::getPointPosY() const
{
    return _pointPosY;
}

double RayTracer::Parser::getPointPosZ() const
{
    return _pointPosZ;
}

double RayTracer::Parser::getDirX() const
{
    return _dirX;
}

double RayTracer::Parser::getDirY() const
{
    return _dirY;
}

double RayTracer::Parser::getDirZ() const
{
    return _dirZ;
}

std::vector<std::shared_ptr<RayTracer::Primitives>> RayTracer::Parser::getScene() const
{
    return _scene;
}

double RayTracer::Parser::getCameraPosX() const
{
    return _posX;
}

double RayTracer::Parser::getCameraPosY() const
{
    return _posY;
}

double RayTracer::Parser::getCameraPosZ() const
{
    return _posZ;
}

double RayTracer::Parser::getCameraRotX() const
{
    return _rotX;
}

double RayTracer::Parser::getCameraRotY() const
{
    return _rotY;
}

double RayTracer::Parser::getCameraRotZ() const
{
    return _rotZ;
}
