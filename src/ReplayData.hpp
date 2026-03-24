#pragma once
#include <vector>

struct ReplayInput {
    int frame;
    int button;
    bool pressed;
};

struct ReplayData {
    int levelID = 0;
    int fps = 60;
    std::vector<ReplayInput> inputs;
};
