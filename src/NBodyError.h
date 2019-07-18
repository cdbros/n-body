#pragma once

#ifndef NBODYERROR_H
#define NBODYERROR_H

#include <stdexcept>
#include <string>

class NBodyError : public std::runtime_error {

    public:

        NBodyError(const std::string &message) throw()
            : std::runtime_error(message.c_str()) {}
};

#endif /* NBODYERROR_H */
