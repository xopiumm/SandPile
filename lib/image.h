#pragma once
#include <string>
#include "parse.h"
#include "pile.h"

static constexpr const uint8_t kFileHeaderSize = 14;
static constexpr const uint8_t kInfoHeaderSize = 40;
static constexpr const uint8_t kPaletteSize = 20;
static constexpr const uint8_t kColorAmount = 5;
static constexpr const uint8_t kBitsPerPixel = 4;

void GenerateModel(Arguments& arguments);

struct Color {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
};

struct Palette {
    uint8_t palette[kPaletteSize] {0};

    Color white = {255, 255, 255};  //  0
    Color green = {10, 85, 71};  //  1
    Color yellow = {5, 178, 252};  //  2
    Color purple = {159, 83, 134};  //  3
    Color black = {31, 29, 39};  //  4

    void SetPalette();
};

struct Image {
    uint8_t* pixels;
    uint32_t file_size;
    uint8_t* bmp_file_header;
    uint8_t* bmp_inf_header;
    uint8_t padding_amount;
    uint16_t offset_x;
    uint16_t offset_y;
    uint16_t width;
    uint16_t height;

    void GetActualSize(Field& pile);
    void SetFileSize();
    void SetHeader();
    void SetColors(Field& pile);
    void CreateImage(Field& pile, std::string& output_filename);
};