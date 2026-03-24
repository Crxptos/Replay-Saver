#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

#include "ReplayRecorder.hpp"
#include "ReplaySaver.hpp"

using namespace geode::prelude;

class $modify(ReplayPlayLayer, PlayLayer) {

    bool init(GJGameLevel* level) {
        if (!PlayLayer::init(level)) return false;

        if (level) {
            ReplayRecorder::get()->start(level->m_levelID.value());
        }

        return true;
    }

    void update(float dt) {
        PlayLayer::update(dt);
        ReplayRecorder::get()->update();
    }

    void pushButton(int button) {
        ReplayRecorder::get()->recordPress(button);
        PlayLayer::pushButton(button);
    }

    void releaseButton(int button) {
        ReplayRecorder::get()->recordRelease(button);
        PlayLayer::releaseButton(button);
    }

    void levelComplete() {
        ReplayRecorder::get()->stop();

        bool autoExport = Mod::get()->getSettingValue<bool>("auto-export-mp4");

        if (autoExport) {
            auto notif = Notification::create("Saving replay...", 3.0f);
            notif->show();

            std::string path;
            bool success = ReplaySaver::saveReplay(
                ReplayRecorder::get()->getData(),
                path
            );

            if (success) {
                notif->setString("Replay saved!");
                ReplaySaver::exportMP4("temp", path + ".mp4");
            } else {
                notif->setString("Failed to save replay.");
            }
        }

        PlayLayer::levelComplete();
    }
};
