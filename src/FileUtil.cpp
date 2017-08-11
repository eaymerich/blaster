#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <fstream>

#include "FileUtil.h"

using std::cerr;
using std::endl;
using std::ifstream;
using std::ios;
using std::streampos;
using std::string;
using std::vector;

vector<char> FileUtil::read(const string& filename) {
    ifstream file{filename, ios::in | ios::binary | ios::ate};
    if (!file.is_open()) {
        cerr << "Couldn't open file: " << filename << endl;
        abort();
    }
    auto filesize = file.tellg();
    vector<char> buffer;
    buffer.resize(filesize);
    file.seekg(0, ios::beg);
    file.read(buffer.data(), filesize);
    file.close();
    return buffer;
}

bool FileUtil::hasExtension(const string& value, const string& ending) {
    return ending.size() <= value.size() &&
        std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}
