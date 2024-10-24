#include "image.h"

void GenerateModel(Arguments& arguments) {
    Field pile;
    Image image;
    pile.GetStartSize(arguments);
    pile.InitField(arguments);

    std::string string_path (arguments.output_path, strlen(arguments.output_path));
    std::string output_filename = string_path + "/sandpile" + std::to_string(arguments.iterations) + ".bmp";

    for (int64_t iter = 1; (iter <= arguments.iterations) && (!pile.IsStable()); ++iter) {
        pile.Iteration();
        if ((arguments.frequency != 0) && (iter % arguments.frequency == 0)) {
            output_filename = string_path + "/sandpile" + std::to_string(iter) + ".bmp";
            image.CreateImage(pile, output_filename);
        }
    }

    image.CreateImage(pile, output_filename);
}

void Image::GetActualSize(Field &pile) {
    bool found = false;

    for (int i = 0; !found && i < pile.width; ++i) {
        for (int j = 0; j < pile.height; ++j) {
            if (pile.field[i][j] != 0) {
                offset_x = i;
                found = true;
                break;
            }
        }
    }

    found = false;

    for (int i = pile.width - 1; !found &&  i >= 0; --i) {
        for (int j = 0; j < pile.height; ++j) {
            if (pile.field[i][j] != 0) {
                width = i + 1 - offset_x;
                found = true;
                break;
            }
        }
    }

    found = false;

    for (int i = 0; !found && i < pile.height; ++i) {
        for (int j = 0; j < pile.width; ++j) {
            if (pile.field[j][i] != 0) {
                offset_y = i;
                found = true;
                break;
            }
        }
    }

    found = false;

    for (int i = pile.height - 1; !found && i >= 0; --i) {
        for (int j = 0; j < pile.width; ++j) {
            if (pile.field[j][i] != 0) {
                height = i + 1 - offset_y;
                found = true;
                break;
            }
        }
    }
}

void Image::SetFileSize() {
    padding_amount = (8 - (width % 8)) % 8;
    file_size = kFileHeaderSize + kInfoHeaderSize + kPaletteSize + ((width + padding_amount) * height) / 2;
}

void Image::SetHeader() {
    bmp_file_header = new uint8_t[kFileHeaderSize];
    bmp_inf_header = new uint8_t[kInfoHeaderSize];

    bmp_file_header[0] = 0x42;
    bmp_file_header[1] = 0x4D;  //  BM signature

    bmp_file_header[2] = static_cast<uint8_t>(file_size);
    bmp_file_header[3] = static_cast<uint8_t>(file_size >> 8);
    bmp_file_header[4] = static_cast<uint8_t>(file_size >> 16);
    bmp_file_header[5] = static_cast<uint8_t>(file_size >> 24);  //  size of BMP file in bytes

    bmp_file_header[6] = 0;
    bmp_file_header[7] = 0;
    bmp_file_header[8] = 0;
    bmp_file_header[9] = 0;  //  reserved

    bmp_file_header[10] = kFileHeaderSize + kInfoHeaderSize + kPaletteSize;
    bmp_file_header[11] = 0;
    bmp_file_header[12] = 0;
    bmp_file_header[13] = 0;  //  offset

    bmp_inf_header[0] = kInfoHeaderSize;
    bmp_inf_header[1] = 0;
    bmp_inf_header[2] = 0;
    bmp_inf_header[3] = 0;  //  size of info header

    bmp_inf_header[4] = static_cast<uint8_t>(width);
    bmp_inf_header[5] = static_cast<uint8_t>(width >> 8);
    bmp_inf_header[6] = static_cast<uint8_t>(width >> 16);
    bmp_inf_header[7] = static_cast<uint8_t>(width >> 24);  //  width in pixels

    bmp_inf_header[8] = static_cast<uint8_t>(height);
    bmp_inf_header[9] = static_cast<uint8_t>(height >> 8);
    bmp_inf_header[10] = static_cast<uint8_t>(height >> 16);
    bmp_inf_header[11] = static_cast<uint8_t>(height >> 24);  //  height in pixels

    bmp_inf_header[12] = 1;
    bmp_inf_header[13] = 0;  //  number of color planes

    bmp_inf_header[14] = kBitsPerPixel;
    bmp_inf_header[15] = 0;  // number of bits per pixel

    bmp_inf_header[16] = 0;
    bmp_inf_header[17] = 0;
    bmp_inf_header[18] = 0;
    bmp_inf_header[19] = 0;  //  compression method

    bmp_inf_header[20] = 0;
    bmp_inf_header[21] = 0;
    bmp_inf_header[22] = 0;
    bmp_inf_header[23] = 0;  //  size of the image

    bmp_inf_header[24] = 0;
    bmp_inf_header[25] = 0;
    bmp_inf_header[26] = 0;
    bmp_inf_header[27] = 0;  //  horizontal resolution

    bmp_inf_header[28] = 0;
    bmp_inf_header[29] = 0;
    bmp_inf_header[30] = 0;
    bmp_inf_header[31] = 0;  //  vertical resolution

    bmp_inf_header[32] = kColorAmount;
    bmp_inf_header[33] = 0;
    bmp_inf_header[34] = 0;
    bmp_inf_header[35] = 0;  //  number of colors in a palette

    bmp_inf_header[36] = 0;
    bmp_inf_header[37] = 0;
    bmp_inf_header[38] = 0;
    bmp_inf_header[39] = 0;  //  number of important colors
}

void Palette::SetPalette() {
    palette[0] = white.blue;
    palette[1] = white.green;
    palette[2] = white.red;
    palette[3] = 0;

    palette[4] = green.blue;
    palette[5] = green.green;
    palette[6] = green.red;
    palette[7] = 0;

    palette[8] = yellow.blue;
    palette[9] = yellow.green;
    palette[10] = yellow.red;
    palette[11] = 0;

    palette[12] = purple.blue;
    palette[13] = purple.green;
    palette[14] = purple.red;
    palette[15] = 0;

    palette[16] = black.blue;
    palette[17] = black.green;
    palette[18] = black.red;
    palette[19] = 0;
}

void Image::SetColors(Field& pile) {
    pixels = new uint8_t[width * height];

    for (uint16_t j = 0; j < height; ++j) {
        for (uint16_t i = 0; i < width; ++i) {
            uint64_t value = pile.field[i + offset_x][j + offset_y];

            switch (value) {
                case 0:
                    pixels[j * width + i] = 0;
                    break;
                case 1:
                    pixels[j * width + i] = 1;
                    break;
                case 2:
                    pixels[j * width + i] = 2;
                    break;
                case 3:
                    pixels[j * width + i] = 3;
                    break;
                default:
                    pixels[j * width + i] = 4;
                    break;
            }
        }
    }
}

void Image::CreateImage(Field& pile, std::string& output_filename) {
    Palette palette;
    GetActualSize(pile);
    SetFileSize();
    SetHeader();
    palette.SetPalette();
    SetColors(pile);

    std::ofstream bmp_file(output_filename, std::ios::out | std::ios::binary);
    bmp_file.write(reinterpret_cast<char*>(bmp_file_header), kFileHeaderSize);
    bmp_file.write(reinterpret_cast<char*>(bmp_inf_header), kInfoHeaderSize);
    bmp_file.write(reinterpret_cast<char*>(palette.palette), kPaletteSize);

    uint8_t left;
    uint8_t right;
    uint8_t byte;
    uint8_t padding_byte = 0;
    for (uint16_t y = 0; y < height; ++y) {
        for (uint16_t x = 0; x < width + padding_amount; x += 2) {
            if (x >= width) {
                left = padding_byte;
                right = padding_byte;
            } else if (x + 1 >= width) {
                left = pixels[y * width + x];
                right = padding_byte;
            } else {
                left = pixels[y * width + x];
                right = pixels[y * width + x + 1];
            }

            byte = (left << kBitsPerPixel);
            byte += right;

            bmp_file << byte;
        }
    }

    delete[] pixels;
    bmp_file.close();
}
