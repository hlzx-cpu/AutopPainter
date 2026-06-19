#include "autopainter/command.hpp"

#include <iomanip>
#include <sstream>
#include <stdexcept>

namespace autopainter {

std::string encodeCoordinate(int value)
{
    if (value < 0 || value > 0xFFFF) {
        throw std::out_of_range("coordinate is outside four-hex-digit range");
    }

    std::ostringstream out;
    out << std::uppercase << std::hex << std::setw(4) << std::setfill('0') << value;
    return out.str();
}

std::string encodeProgram(const std::vector<Stroke>& strokes)
{
    std::vector<std::string> words;
    std::string activePen;

    for (const Stroke& stroke : strokes) {
        if (stroke.points.empty()) {
            continue;
        }

        if (stroke.penCode != activePen) {
            words.push_back(stroke.penCode);
            words.push_back("0000");
            activePen = stroke.penCode;
        }

        const cv::Point& start = stroke.points.front();
        words.push_back(encodeCoordinate(start.x));
        words.push_back(encodeCoordinate(start.y));
        words.push_back("8FDD");
        words.push_back("0000");

        for (std::size_t i = 1; i < stroke.points.size(); ++i) {
            words.push_back(encodeCoordinate(stroke.points[i].x));
            words.push_back(encodeCoordinate(stroke.points[i].y));
        }

        words.push_back("8FEE");
        words.push_back("0000");
    }

    std::ostringstream program;
    for (std::size_t i = 0; i < words.size(); ++i) {
        if (i > 0) {
            program << ' ';
        }
        program << words[i];
    }
    return program.str();
}

} // namespace autopainter

