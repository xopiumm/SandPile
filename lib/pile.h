#pragma once
#include <fstream>
#include <limits>
#include "parse.h"

static constexpr const uint8_t kInputStringLength = 40;

struct Node {
    uint16_t x;
    uint16_t y;
    Node* prev;
};

struct UnstableSlots {
    Node* key;

    UnstableSlots();
    ~UnstableSlots();

    void Push(uint16_t x, uint16_t y);
    void Pop();
};

struct Field {
    uint64_t** field;
    uint16_t width;
    uint16_t height;
    UnstableSlots unstable_slots;

    int16_t max_x = std::numeric_limits<int16_t>::min();
    int16_t min_x = std::numeric_limits<int16_t>::max();
    int16_t max_y = std::numeric_limits<int16_t>::min();
    int16_t min_y = std::numeric_limits<int16_t>::max();

    bool upper;
    bool right;
    bool lower;
    bool left;

    void GetStartSize(Arguments& arguments);
    void InitField(Arguments& arguments);
    bool IsStable() const;
    bool NeedResize();
    void Resize();
    void Iteration();
};