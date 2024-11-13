#include "visual.h"

#include "global.h"

namespace Macer {
namespace Utils {
namespace Visual {

cv::Point findPos(const std::string& screenshotPath, const std::string& targetPath, double threshold) {

    cv::Mat largeImage = cv::imread(screenshotPath, cv::IMREAD_COLOR);
    cv::Mat smallImage = cv::imread(targetPath, cv::IMREAD_COLOR);
    if (largeImage.empty() || smallImage.empty()) {
        gLog.error("图像路径不存在");
        return cv::Point(-1, -1);
    }
    
    // 转化为灰度
    cv::Mat largeGray;
    cv::Mat smallGray;
    cv::cvtColor(largeImage, largeGray, cv::COLOR_BGR2GRAY);
    cv::cvtColor(smallImage, smallGray, cv::COLOR_BGR2GRAY);

    // 模版匹配
    cv::Mat result;
    cv::matchTemplate(largeGray, smallGray, result, cv::TM_CCOEFF_NORMED);
    
    // 返回最优解
    double minVal;
    double maxVal;
    cv::Point minLoc;
    cv::Point maxLoc;
    cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);

    // 评估结果
    if (maxVal < threshold) { // 相似度太低判定为找不到
        return cv::Point(-1, -1);
    }

    // 分析小图位置
    cv::Point topLeft(maxLoc);
    cv::Point bottomRight(topLeft.x + smallImage.cols, topLeft.y + smallImage.rows);

    // 计算中心点
    int middleX = (topLeft.x + bottomRight.x) / 2;
    int middleY = (topLeft.y + bottomRight.y) / 2;
    cv::Point middlePoint(middleX, middleY);

    return middlePoint;
}

} // namespace Visual
} // namespace Utils
} // namespace Macer