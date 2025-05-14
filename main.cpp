/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** main
*/

// Mediator 

#include <libconfig.h++>
#include "includes/includes.hpp"

// #include "includes/RayTracer.hpp"

int main(int ac, char *av[])
{
    if (ac != 2)
        return 84;
    std::string file = static_cast <std::string>(av[1]);
    if (file == "-help") {
        std::cout << "USAGE: ./raytracer <SCENE_FILE>\n" << "\tSCENE_FILE: scene configuration" << std::endl;
        return 0;
    }
    libconfig::Config cfg;

    try {
        cfg.readFile(file);
    } catch (const libconfig::FileIOException &fioex) {
        std::cerr << "I/O error while reading file." << std::endl;
        return 84;
    } catch (const libconfig::ParseException &pex) {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                  << " - " << pex.getError() << std::endl;
        return 84;
    }
    try {
        const libconfig::Setting &camera = cfg.lookup("camera");

        int width, height;
        camera.lookupValue("resolution.width", width);
        camera.lookupValue("resolution.height", height);
        std::cout << "Camera resolution: " << width << "x" << height << "\n";

        float fov;
        camera.lookupValue("fieldOfView", fov);
        std::cout << "Field of View: " << fov << "\n";

        const libconfig::Setting &spheres = cfg.lookup("primitives.spheres");
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

        float ambient, diffuse;
        cfg.lookupValue("lights.ambient", ambient);
        cfg.lookupValue("lights.diffuse", diffuse);
        std::cout << "Ambient light: " << ambient << ", Diffuse light: " << diffuse << "\n";

    } catch (const libconfig::SettingNotFoundException &nfex) {
        std::cerr << "A setting was not found: " << nfex.getPath() << std::endl;
        return 84;
    }

    return 0;
}
