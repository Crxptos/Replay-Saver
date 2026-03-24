#include "ReplaySaver.hpp"
#include <Geode/Geode.hpp>

#include <fstream>
#include <filesystem>
#include <thread>

using namespace geode::prelude;

bool ReplaySaver::saveReplay(const ReplayData& data, std::string& outPath) {
    try {
        auto base = Mod::get()->getSaveDir();
        std::filesystem::path folder = base / "savedReplays";

        std::filesystem::create_directories(folder);

        std::filesystem::path filePath =
            folder / ("level_" + std::to_string(data.levelID) + ".replay");

        std::ofstream out(filePath);

        if (!out.is_open()) {
            log::error("Failed to open replay file!");
            return false;
        }

        out << data.levelID << "\n";

        for (const auto& i : data.inputs) {
            out << i.frame << " "
                << i.button << " "
                << i.pressed << "\n";
        }

        out.close();
        outPath = filePath.string();

        return true;

    } catch (const std::exception& e) {
        log::error("Replay save error: {}", e.what());
        return false;
    }
}

void ReplaySaver::exportMP4(const std::string& inputFolder, const std::string& output) {
    std::thread([inputFolder, output]() {
        // 🔧 Replace later with FFmpeg API
        log::info("Exporting MP4 from {} -> {}", inputFolder, output);
    }).detach();
}
