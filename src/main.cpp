#include "autopainter/command.hpp"
#include "autopainter/image_classifier.hpp"
#include "autopainter/json_writer.hpp"
#include "autopainter/palette.hpp"
#include "autopainter/planner.hpp"

#include <opencv2/imgcodecs.hpp>

#include <filesystem>
#include <algorithm>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace {

std::vector<fs::path> collectImages(const fs::path& datasetDir)
{
    std::vector<fs::path> images;
    for (const fs::directory_entry& entry : fs::directory_iterator(datasetDir)) {
        if (!entry.is_regular_file()) {
            continue;
        }
        std::string ext = entry.path().extension().string();
        if (ext == ".jpg" || ext == ".jpeg" || ext == ".JPG" || ext == ".JPEG") {
            images.push_back(entry.path());
        }
    }

    std::sort(images.begin(), images.end());
    return images;
}

} // namespace

int main(int argc, char** argv)
{
    try {
        fs::path datasetDir = argc > 1 ? fs::path(argv[1]) : fs::path("test_dataset");
        fs::path outputPath = argc > 2 ? fs::path(argv[2]) : fs::path("submission.json");

        const std::vector<autopainter::Pen> pens = autopainter::supportedPens();
        std::map<std::string, std::string> programs;

        for (const fs::path& imagePath : collectImages(datasetDir)) {
            cv::Mat image = cv::imread(imagePath.string(), cv::IMREAD_COLOR);
            if (image.empty()) {
                throw std::runtime_error("failed to load image: " + imagePath.string());
            }

            autopainter::MaskByPen masks = autopainter::classifyImage(image, pens);
            std::vector<autopainter::Stroke> strokes = autopainter::planStrokes(masks, pens);
            programs.emplace(imagePath.filename().string(), autopainter::encodeProgram(strokes));

            std::cout << imagePath.filename().string() << ": "
                      << strokes.size() << " strokes\n";
        }

        autopainter::writeSubmission(outputPath, programs);
        std::cout << "wrote " << outputPath << '\n';
    } catch (const std::exception& error) {
        std::cerr << "error: " << error.what() << '\n';
        return 1;
    }

    return 0;
}
