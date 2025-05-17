/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** main
*/

// Mediator
#include "includes/Parser.hpp"
#include "includes/Errors.hpp"
#include "includes/RayTracer.hpp"

int main(int ac, char *av[])
{
    if (ac != 2) {
        try {
            throw RayTracer::RayError("Invalid number of arguments");
        } catch (const RayTracer::RayError &error) {
            std::cerr << error.what() << std::endl;
        }
        return 84;
    }
    std::string file = static_cast<std::string>(av[1]);
    RayTracer::Parser parser;
    if (file == "-help" || file == "-h") {
        parser.displayHelp();
        return 0;
    }
    if (parser.parseConfigFile(file) != 0)
        return 84;
    return 0;
}