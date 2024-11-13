#ifndef AA584E0F_D3A8_41AB_B931_C3D6D0F4FE58
#define AA584E0F_D3A8_41AB_B931_C3D6D0F4FE58

#include <string>

namespace Macer {
namespace Platf {
namespace Mumu {

    bool isRunning();
    bool isRoxRunning();
    
    void start();
    void launchRox();
    void screenshot();
    void click(int x, int y);

} // namespace Mumu
} // namespace Platf
} // namespace Macer

#endif /* AA584E0F_D3A8_41AB_B931_C3D6D0F4FE58 */