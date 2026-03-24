#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/binding/LevelCompleteLayer.hpp>

#include "ReplayRecorder.hpp"
#include "ReplaySaver.hpp"

using namespace geode::prelude;

//
// 🎮 PLAYLAYER
//
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
            this->saveReplayAuto();
        }

        PlayLayer::levelComplete();
    }

    void saveReplayAuto() {
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
};


//
// 🏁 LEVEL COMPLETE BUTTON
//
class $modify(ReplayEndLayer, LevelCompleteLayer) {

    bool init(GJGameLevel* level) {
        if (!LevelCompleteLayer::init(level)) return false;

        bool autoExport = Mod::get()->getSettingValue<bool>("auto-export-mp4");

        if (!autoExport) {
            this->addButton(level);
        }

        return true;
    }

    void addButton(GJGameLevel* level) {
        auto winSize = CCDirector::sharedDirector()->getWinSize();

        auto sprite = ButtonSprite::create("Save Replay");
        auto btn = CCMenuItemSpriteExtra::create(
            sprite,
            this,
            menu_selector(ReplayEndLayer::onSave)
        );

        btn->setPosition({ winSize.width / 2, 80 });

        auto menu = this->getChildByID("button-menu");
        if (!menu) {
            menu = CCMenu::create();
            menu->setPosition({0, 0});
            this->addChild(menu);
        }

        menu->addChild(btn);

        m_level = level;
        m_button = btn;
    }

    void onSave(CCObject*) {
        if (!m_level) return;

        m_button->setEnabled(false);

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

private:
    GJGameLevel* m_level = nullptr;
    CCMenuItemSpriteExtra* m_button = nullptr;
};
