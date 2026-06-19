#include "autopainter/palette.hpp"

#include <stdexcept>

namespace autopainter {
namespace {

int hexPairToInt(const std::string& text, std::size_t offset)
{
    return std::stoi(text.substr(offset, 2), nullptr, 16);
}

} // namespace

cv::Vec3b rgbHexToBgr(const std::string& rgbHex)
{
    if (rgbHex.size() != 6) {
        throw std::invalid_argument("RGB color must contain exactly six hex digits");
    }

    int red = hexPairToInt(rgbHex, 0);
    int green = hexPairToInt(rgbHex, 2);
    int blue = hexPairToInt(rgbHex, 4);
    return cv::Vec3b(
        static_cast<unsigned char>(blue),
        static_cast<unsigned char>(green),
        static_cast<unsigned char>(red));
}

std::vector<Pen> supportedPens()
{
    std::vector<Pen> pens = {
        {"8FF5", "000000", {}},
        {"8FF4", "0033CC", {}},
        {"8FF6", "FF9933", {}},
        {"8FF1", "FF0000", {}},
        {"8FF3", "FFFF00", {}},
        {"8FF2", "00FF00", {}},
        {"8FF7", "00EEFF", {}},
    };

    for (Pen& pen : pens) {
        pen.bgr = rgbHexToBgr(pen.rgbHex);
    }
    return pens;
}

} // namespace autopainter

