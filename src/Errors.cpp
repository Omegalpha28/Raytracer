/*
** EPITECH PROJECT, 2025
** bsraytracer
** File description:
** ErrorClass
*/

#include "includes/Errors.hpp"

RayTracer::ErrorClass::ErrorClass(const std::string &message) : _Message{message}
{}

void RayTracer::ErrorClass::addMessage(const std::string &message)
{
     _Message += message;
}

void RayTracer::ErrorClass::addMessage(const char *message)
{
    _Message += message;
}

void RayTracer::ErrorClass::updateMessage(const std::string &message)
{
    _Message = message;
}

void RayTracer::ErrorClass::updateMessage(const char *message)
{
    _Message = message;
}

const char *RayTracer::ErrorClass::what() const noexcept
{
    return _Message.c_str();
}

RayTracer::LoarderError::LoarderError(const std::string &message) : ErrorClass{"Dynamic Library: " + message}
{}

RayTracer::ExecError::ExecError(const std::string &message) : ErrorClass{"Execution Error: " + message}
{}
