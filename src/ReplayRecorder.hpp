#pragma once

#include "ReplayData.hpp"

class ReplayRecorder {
public:
    static ReplayRecorder* get();

    void start(int levelID);
    void stop();
    void update();

    void recordPress(int button);
    void recordRelease(int button);

    ReplayData& getData();

private:
    ReplayData m_data{};
    int m_frame = 0;
    bool m_recording = false;
};
