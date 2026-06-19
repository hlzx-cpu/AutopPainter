#pragma once

#include "autopainter/palette.hpp"

#include <opencv2/core.hpp>

#include <map>
#include <string>

namespace autopainter {

using MaskByPen = std::map<std::string, cv::Mat>;

MaskByPen classifyImage(const cv::Mat& image, const std::vector<Pen>& pens);

} // namespace autopainter

