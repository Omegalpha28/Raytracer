/*
** EPITECH PROJECT, 2024
** B-OOP-400-LYN-4-1-arcade-loan.badey
** File description:
** Parser.hpp
*/

#pragma once
#include "includes.hpp"

namespace RayTracer {

    class ErrorClass : public std::exception
    {
        protected:
            std::string _Message;
        public:
            ErrorClass() = default;
            explicit ErrorClass(const std::string &message);
            ~ErrorClass() = default;
            void updateMessage(const std::string &message);
            void updateMessage(const char *message);
            void addMessage(const std::string &message);
            void addMessage(const char *message);
            const char *what() const noexcept override;
    };
    class LoarderError : public ErrorClass {
        public:
            LoarderError(const std::string &Message);
            ~LoarderError() = default;
    };
    class RayError : public ErrorClass {
        public:
            RayError(const std::string &message);
            ~RayError() = default;
    };
    class ExecError : public ErrorClass {
        public:
            ExecError(const std::string &message);
            ~ExecError() = default;
    };
    class ParseError : public ErrorClass {
        public:
            ParseError(const std::string &message);
            ~ParseError() = default;
    };
}