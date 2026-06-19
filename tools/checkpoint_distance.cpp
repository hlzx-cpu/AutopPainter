#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

struct MachineState {
    bool penDown = false;
    int x = 0;
    int y = 0;
    double upDistance = 0.0;
    double downDistance = 0.0;
};

bool isPenCode(const std::string& word)
{
    return word == "8FF5" || word == "8FF4" || word == "8FF6" ||
           word == "8FF1" || word == "8FF3" || word == "8FF2" ||
           word == "8FF7";
}

int parseHex(const std::string& word)
{
    return std::stoi(word, nullptr, 16);
}

std::vector<std::string> splitWords(const std::string& text)
{
    std::istringstream input(text);
    std::vector<std::string> words;
    std::string word;
    while (input >> word) {
        words.push_back(word);
    }
    return words;
}

std::string defaultProgram()
{
    return "8FF5 0000 0102 0304 8FDD 0000 0045 00AE 8FEE 0000";
}

} // namespace

int main(int argc, char** argv)
{
    std::ostringstream joined;
    for (int i = 1; i < argc; ++i) {
        if (i > 1) {
            joined << ' ';
        }
        joined << argv[i];
    }

    std::vector<std::string> words = splitWords(argc > 1 ? joined.str() : defaultProgram());
    MachineState state;

    for (std::size_t i = 0; i < words.size();) {
        const std::string& first = words[i];
        if (i + 1 >= words.size()) {
            throw std::runtime_error("instruction word count is odd");
        }
        const std::string& second = words[i + 1];

        if (first == "8FDD" && second == "0000") {
            state.penDown = true;
        } else if (first == "8FEE" && second == "0000") {
            state.penDown = false;
        } else if (isPenCode(first) && second == "0000") {
            // Switching pens is not a planar movement.
        } else {
            int nextX = parseHex(first);
            int nextY = parseHex(second);
            double distance = std::hypot(nextX - state.x, nextY - state.y);
            if (state.penDown) {
                state.downDistance += distance;
            } else {
                state.upDistance += distance;
            }
            state.x = nextX;
            state.y = nextY;
        }

        i += 2;
    }

    std::cout << std::fixed << std::setprecision(1);
    std::cout << "up=" << state.upDistance << '\n';
    std::cout << "down=" << state.downDistance << '\n';
    std::cout << "total=" << state.upDistance + state.downDistance << '\n';
    return 0;
}

