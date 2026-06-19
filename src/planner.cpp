#include "autopainter/planner.hpp"

#include <algorithm>

namespace autopainter {
namespace {

std::vector<cv::Point> makeRunPoints(int y, int x0, int x1, int pointStep, bool reverse)
{
    std::vector<cv::Point> points;
    if (reverse) {
        for (int x = x1; x >= x0; x -= pointStep) {
            points.emplace_back(x, y);
        }
        if (points.empty() || points.back().x != x0) {
            points.emplace_back(x0, y);
        }
    } else {
        for (int x = x0; x <= x1; x += pointStep) {
            points.emplace_back(x, y);
        }
        if (points.empty() || points.back().x != x1) {
            points.emplace_back(x1, y);
        }
    }
    return points;
}

} // namespace

std::vector<Stroke> planStrokes(
    const MaskByPen& masks,
    const std::vector<Pen>& pens,
    const PlannerOptions& options)
{
    std::vector<Stroke> strokes;

    for (const Pen& pen : pens) {
        auto found = masks.find(pen.code);
        if (found == masks.end()) {
            continue;
        }

        const cv::Mat& mask = found->second;
        bool reverse = false;

        for (int y = 0; y < mask.rows; y += options.rowStep) {
            const unsigned char* row = mask.ptr<unsigned char>(y);
            int x = 0;

            while (x < mask.cols) {
                while (x < mask.cols && row[x] == 0) {
                    ++x;
                }
                if (x >= mask.cols) {
                    break;
                }

                int x0 = x;
                while (x < mask.cols && row[x] != 0) {
                    ++x;
                }
                int x1 = x - 1;
                if (x1 - x0 + 1 < options.minRunLength) {
                    continue;
                }

                strokes.push_back({
                    pen.code,
                    makeRunPoints(y, x0, x1, options.pointStep, reverse),
                });
                reverse = !reverse;
            }
        }
    }

    return strokes;
}

} // namespace autopainter

