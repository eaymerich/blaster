#ifndef __FILEUTIL_H__
#define __FILEUTIL_H__

#include <vector>
#include <string>

class FileUtil {
public:
    virtual ~FileUtil() = default;
    static std::vector<char> read(std::string filename);
private:
    FileUtil() = default;
};

#endif // __FILEUTIL_H__
