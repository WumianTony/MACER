#ifndef AB214A28_73CF_440A_AFE1_FDF721098936
#define AB214A28_73CF_440A_AFE1_FDF721098936

#include <opencv2/opencv.hpp>

namespace Macer {
namespace Utils {
namespace Visual {

cv::Point findPos(const std::string& screenshotPath, const std::string& targetPath, double threshold = 0.8);

} // namespace Visual
} // namespace Utils
} // namespace Macer

#endif /* AB214A28_73CF_440A_AFE1_FDF721098936 */