#ifndef D9DA99CB_DCA4_46AB_9F04_31D8E80935DA
#define D9DA99CB_DCA4_46AB_9F04_31D8E80935DA

#include <string>
#include <vector>

namespace System {
    bool isPathValid(const std::string& path);

    std::string getLocalPath();
    std::string getFilePath(const std::string& file);
    std::vector<std::string> getFiles(const std::string& path);

    void createPath(const std::string& path);
    void createPath(const std::vector<std::string>& paths);
}

#endif /* D9DA99CB_DCA4_46AB_9F04_31D8E80935DA */