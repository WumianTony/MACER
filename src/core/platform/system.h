#ifndef D9DA99CB_DCA4_46AB_9F04_31D8E80935DA
#define D9DA99CB_DCA4_46AB_9F04_31D8E80935DA

#include <string>
#include <vector>

namespace Macer {
namespace Platf {
namespace System {

    bool isPathValid(const std::string& path);

    std::string getLocalPath();
    std::string getFilePath(const std::string& file);
    std::vector<std::string> getFiles(const std::string& path);
    std::string getCreateTime(const std::string& path);

    void createPath(const std::string& path);
    void createPath(const std::vector<std::string>& paths);
    void renameFile(const std::string& path, const std::string& name);

}
}
}

#endif /* D9DA99CB_DCA4_46AB_9F04_31D8E80935DA */