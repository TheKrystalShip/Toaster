#pragma once

#include <string>
#include <vector>

namespace Toaster
{
    class IOManager
    {
    public:
        static bool readFileToBuffer(std::string filePath, std::vector<unsigned char> &buffer);
        static bool readFileToBuffer(std::string filePath, std::string &buffer);
    };
}
