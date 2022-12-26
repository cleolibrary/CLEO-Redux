#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>

#include "../../SDK/cleo_redux_sdk.h"

namespace std {

    class TxtLoader {
    public:
        TxtLoader()
        {
            Log("TXT Loader 1.1");
            RegisterLoader("*.txt", Loader);
            RegisterLoader("*.text", Loader);
            GenerateTypings();
        }

        static void* Loader(const char* fileName)
        {
            ifstream input_file(fileName);

            // return nullptr if we can't open the file
            if (!input_file.is_open()) {
                return nullptr;
            }

            ostringstream ss;
            string line;

            // construct a JSON array where every item is a line from the source file
            ss << "[";
            if (getline(input_file, line)) {
                ss << "\"" << line << "\"";
            }
            while (getline(input_file, line)) {
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

        static void GenerateTypings()
        {
            char path[MAX_PATH];
            GetDirectoryPath(Directory::CONFIG, path);
            string p(path);
            p += "\\txt_loader.d.ts";

            ofstream typing_file(p);

            if (!typing_file.is_open()) {
                Log("Failed to write txt_loader.d.ts");
                return;
            }

            typing_file << R"(declare module "*.txt" {
  const value: string[];
  export default value;
}

declare module "*.text" {
  const value: string[];
  export default value;
}
)";

            typing_file.close();
        }

    } TxtLoader;

}