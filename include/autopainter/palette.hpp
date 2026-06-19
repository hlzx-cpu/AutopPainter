#pragma once

#include <opencv2/core.hpp>

#include <string>
#include <vector>

namespace autopainter {

struct Pen {
    std::string code;
    std::string rgbHex;
    cv::Vec3b bgr;
};

std::vector<Pen> supportedPens();
cv::Vec3b rgbHexToBgr(const std::string& rgbHex);

} // namespace autopainter

