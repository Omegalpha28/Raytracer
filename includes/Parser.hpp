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
#include "RayTracer.hpp"

namespace RayTracer {
    class Parser {
    private:
        libconfig::Config _cfg;
        int _width;
        int _height;
        float _fov;
        float _ambientLight;
        float _diffuseLight;
        int _posX, _posY, _posZ;
        int _rotX, _rotY, _rotZ;
        int _dirX, _dirY, _dirZ;
        int _pointPosX, _pointPosY, _pointPosZ;
        int parseCameraSettings();
        int parsePrimitives();
        int parseLights();
        std::vector<std::shared_ptr<Primitives>> _scene;
    public:
        Parser();
        ~Parser();
        int parseConfigFile(const std::string &filePath);
        void displayHelp() const;
        int getWidth() const;
        int getHeight() const;
        float getFov() const;
        public:
        std::vector<std::shared_ptr<Primitives>> getScene() const;
        float getCameraPosX() const;
        float getCameraPosY() const;
        float getCameraPosZ() const;
        float getCameraRotX() const;
        float getCameraRotY() const;
        float getCameraRotZ() const;
        float getPointPosX() const;
        float getPointPosY() const;
        float getPointPosZ() const;
        float getDirX() const;
        float getDirY() const;
        float getDirZ() const;
        float getAmbientLight() const;
        float getDiffuseLight() const;
    };
}