#include "autopainter/json_writer.hpp"

#include <fstream>
#include <iterator>
#include <stdexcept>

namespace autopainter {
namespace {

std::string escapeJson(const std::string& text)
{
    std::string escaped;
    escaped.reserve(text.size() + 8);

    for (char ch : text) {
        switch (ch) {
        case '\\':
            escaped += "\\\\";
            break;
        case '"':
            escaped += "\\\"";
            break;
        case '\n':
            escaped += "\\n";
            break;
        case '\r':
            escaped += "\\r";
            break;
        case '\t':
            escaped += "\\t";
            break;
        default:
            escaped += ch;
            break;
        }
    }

    return escaped;
}

} // namespace

void writeSubmission(
    const std::filesystem::path& outputPath,
    const std::map<std::string, std::string>& programs)
{
    std::ofstream out(outputPath);
    if (!out) {
        throw std::runtime_error("failed to open submission file: " + outputPath.string());
    }

    out << "{\n";
    out << "  \"results\": {\n";

    for (auto it = programs.begin(); it != programs.end(); ++it) {
        out << "    \"" << escapeJson(it->first) << "\": ";
        out << "\"" << escapeJson(it->second) << "\"";
        if (std::next(it) != programs.end()) {
            out << ',';
        }
        out << '\n';
    }

    out << "  }\n";
    out << "}\n";
}

} // namespace autopainter
