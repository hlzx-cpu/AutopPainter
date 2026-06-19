#pragma once

#include <opencv2/core.hpp>

#include <string>
#include <vector>

namespace autopainter {

struct Stroke {
    std::string penCode;
    std::vector<cv::Point> points;
};

std::string encodeCoordinate(int value);
std::string encodeProgram(const std::vector<Stroke>& strokes);

} // namespace autopainter

