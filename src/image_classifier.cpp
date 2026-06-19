#include "autopainter/image_classifier.hpp"

#include <limits>

namespace autopainter {
namespace {

const cv::Vec3b kWhiteBgr{255, 255, 255};

int squaredDistance(const cv::Vec3b& a, const cv::Vec3b& b)
{
    int db = static_cast<int>(a[0]) - static_cast<int>(b[0]);
    int dg = static_cast<int>(a[1]) - static_cast<int>(b[1]);
    int dr = static_cast<int>(a[2]) - static_cast<int>(b[2]);
    return db * db + dg * dg + dr * dr;
}

} // namespace

MaskByPen classifyImage(const cv::Mat& image, const std::vector<Pen>& pens)
{
    MaskByPen masks;
    for (const Pen& pen : pens) {
        masks.emplace(pen.code, cv::Mat::zeros(image.size(), CV_8U));
    }

    for (int y = 0; y < image.rows; ++y) {
        for (int x = 0; x < image.cols; ++x) {
            const cv::Vec3b pixel = image.at<cv::Vec3b>(y, x);
            int bestDistance = squaredDistance(pixel, kWhiteBgr);
            const Pen* bestPen = nullptr;

            for (const Pen& pen : pens) {
                int distance = squaredDistance(pixel, pen.bgr);
                if (distance < bestDistance) {
                    bestDistance = distance;
                    bestPen = &pen;
                }
            }

            if (bestPen != nullptr) {
                masks[bestPen->code].at<unsigned char>(y, x) = 255;
            }
        }
    }

    return masks;
}

} // namespace autopainter
