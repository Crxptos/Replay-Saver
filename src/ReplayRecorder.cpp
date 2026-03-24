#include "ReplayRecorder.hpp"

static ReplayRecorder* s_instance = nullptr;

ReplayRecorder* ReplayRecorder::get() {
    if (s_instance == nullptr) {
        s_instance = new ReplayRecorder();
    }
    return s_instance;
}

void ReplayRecorder::start(int levelID) {
    m_data = ReplayData{};
    m_data.levelID = levelID;

    m_frame = 0;
    m_recording = true;
}

void ReplayRecorder::stop() {
    m_recording = false;
}

void ReplayRecorder::update() {
    if (!m_recording) return;
    m_frame++;
}

void ReplayRecorder::recordPress(int button) {
    if (!m_recording) return;

    ReplayInput input;
    input.frame = m_frame;
    input.button = button;
    input.pressed = true;

    m_data.inputs.push_back(input);
}

void ReplayRecorder::recordRelease(int button) {
    if (!m_recording) return;

    ReplayInput input;
    input.frame = m_frame;
    input.button = button;
    input.pressed = false;

    m_data.inputs.push_back(input);
}

ReplayData& ReplayRecorder::getData() {
    return m_data;
}
