#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <sstream>

#include "../../SDK/cleo_redux_sdk.h"

class TxtLoader {
public:
    TxtLoader() 
    {
        Log("TXT Loader 1.0");
        RegisterLoader("*.txt", Loader);
        RegisterLoader("*.text", Loader);
    }

    static void* Loader(const char* fileName)
    {
        std::ifstream input_file(fileName);

        // return nullptr if we can't open the file
        if (!input_file.is_open()) {
            return nullptr;
        }

        std::ostringstream ss;
        std::string line;

        // construct a JSON array where every item is a line from the source file
        ss << "[";
        if (std::getline(input_file, line)) {
            ss << "\"" << line << "\"";
        }
        while (std::getline(input_file, line)) {
            ss << ",\"" << line << "\"";
        }
        ss << "]";
        input_file.close();

        // allocate enough space to put the serialized string
        auto content = ss.str();
        char* buf = reinterpret_cast<char*>(AllocMem(content.length() + 1));

        // copy serialized string to the buffer
        sprintf(buf, content.c_str());

        // let CLEO read from the buffer and free up the memory
        return buf;
    }

} TxtLoader;