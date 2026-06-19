#pragma once

#include <filesystem>
#include <map>
#include <string>

namespace autopainter {

void writeSubmission(
    const std::filesystem::path& outputPath,
    const std::map<std::string, std::string>& programs);

} // namespace autopainter

