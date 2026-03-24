#include "ReplaySaver.hpp"
#include <Geode/Geode.hpp>
#include <fstream>
#include <filesystem>
#include <thread>

using namespace geode::prelude;

bool ReplaySaver::saveReplay(const ReplayData& data, std::string& outPath) {
    try {
        std::string base = Mod::get()->getSaveDir().string();
        std::string folder = base + "/savedReplays/";
        std::filesystem::create_directories(folder);

        outPath = folder + "level_" + std::to_string(data.levelID) + ".replay";

        std::ofstream out(outPath);

        out << data.levelID << "\n";
        for (auto& i : data.inputs) {
            out << i.frame << " " << i.button << " " << i.pressed << "\n";
        }

        out.close();
        return true;

    } catch (...) {
        return false;
    }
}

void ReplaySaver::exportMP4(const std::string& inputFolder, const std::string& output) {
    std::thread([=]() {
        // 🔧 Replace this with FFmpeg API later
        // Example:
        // FFmpeg::encodeVideo(inputFolder + "/frame_%d.png", output, 60);

        log::info("Exporting MP4: {}", output);
    }).detach();
}
