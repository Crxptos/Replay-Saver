#pragma once
#include "ReplayData.hpp"
#include <string>

class ReplaySaver {
public:
    static bool saveReplay(const ReplayData& data, std::string& outPath);
    static void exportMP4(const std::string& inputFolder, const std::string& output);
};
