/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-arcade-loan.badey
** File description:
** Parser.hpp
*/

#pragma once

#include <libconfig.h++>
#include <string>
#include <iostream>
#include "includes.hpp"

namespace RayTracer {
    class Parser {
    private:
        libconfig::Config _cfg;
        int _width;
        int _height;
        float _fov;
        float _ambientLight;
        float _diffuseLight;
        int parseCameraSettings();
        int parsePrimitives();
        int parseLights();
    public:
        Parser();
        ~Parser();
        int parseConfigFile(const std::string &filePath);
        void displayHelp() const;
        int getWidth() const;
        int getHeight() const;
        float getFov() const;
        float getAmbientLight() const;
        float getDiffuseLight() const;
    };
}