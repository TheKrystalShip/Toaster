#include "IOManager.h"

#include <string>
#include <vector>
#include <fstream>

namespace Toaster
{
    bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char> &buffer)
    {
        std::ifstream file(filePath, std::ios::binary);
        if (file.fail())
        {
            perror(filePath.c_str());
            return false;
        }

        // Put cursor to end of file to get size.
        file.seekg(0, std::ios::end);

        // Get the size in bytes
        int fileSize = file.tellg();

        // Put cursos back at the start of the file before actually reading data
        file.seekg(0, std::ios::beg);

        // Skip file headers
        fileSize -= file.tellg();

        buffer.resize(fileSize);
        file.read((char *)&buffer[0], fileSize);

        file.close();

        return true;
    }
}
