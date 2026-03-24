#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/PlayerObject.hpp>

#include "ReplayRecorder.hpp"
#include "ReplaySaver.hpp"

using namespace geode::prelude;

//
// 🎮 PLAYLAYER (start/stop recording)
//
class $modify(ReplayPlayLayer, PlayLayer) {

    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects))
            return false;

        if (level) {
            ReplayRecorder::get()->start(level->m_levelID.value());
        }

        return true;
    }

    void update(float dt) {
        PlayLayer::update(dt);
        ReplayRecorder::get()->update();
    }

    void levelComplete() {
        ReplayRecorder::get()->stop();

        bool autoExport = Mod::get()->getSettingValue<bool>("auto-export-mp4");

        if (autoExport) {
            auto notif = Notification::create(
                "Saving replay...",
                NotificationIcon::Loading
            );
            notif->show();

            std::string path;
            bool success = ReplaySaver::saveReplay(
                ReplayRecorder::get()->getData(),
                path
            );

            if (success) {
                notif->setString("Replay saved!");
                notif->setIcon(NotificationIcon::Success);

                ReplaySaver::exportMP4("temp", path + ".mp4");
            } else {
                notif->setString("Failed to save replay.");
                notif->setIcon(NotificationIcon::Error);
            }
        }

        PlayLayer::levelComplete();
    }
};


//
// 🕹️ PLAYER INPUT HOOK (REAL RECORDING)
//
class $modify(ReplayPlayerObject, PlayerObject) {

    void pushButton(PlayerButton button) {
        ReplayRecorder::get()->recordPress(static_cast<int>(button));
        PlayerObject::pushButton(button);
    }

    void releaseButton(PlayerButton button) {
        ReplayRecorder::get()->recordRelease(static_cast<int>(button));
        PlayerObject::releaseButton(button);
    }
};
