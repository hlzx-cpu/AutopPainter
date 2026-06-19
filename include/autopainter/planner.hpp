#pragma once

#include "autopainter/command.hpp"
#include "autopainter/image_classifier.hpp"

#include <vector>

namespace autopainter {

struct PlannerOptions {
    int rowStep = 6;
    int pointStep = 6;
    int minRunLength = 2;
};

std::vector<Stroke> planStrokes(
    const MaskByPen& masks,
    const std::vector<Pen>& pens,
    const PlannerOptions& options = {});

} // namespace autopainter

