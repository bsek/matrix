#ifndef SPI_FONT_H
#define SPI_FONT_H

#include <cstdint>

std::uint8_t font[] = {
        0,   0,   0,   0,   0,   0,   0,   0,
        126, 129, 165, 129, 189, 153, 129, 126,
        126, 255, 219, 255, 195, 231, 255, 126,
        108, 254, 254, 254, 124, 56,   16,   0,
        16,  56, 124, 254, 124, 56,   16,   0,
        56, 124,  56, 254, 254, 214,  16,  56,
        16,  56, 124, 254, 254, 124,  16,  56,
        0,   0,  24,  60,  60,  24,   0,   0,
        255, 255, 231, 195, 195, 231, 255, 255,
        0,  60, 102,  66,  66, 102,  60,   0,
        255, 195, 153, 189, 189, 153, 195, 255,
        15,   7,  15, 125, 204, 204, 204, 120,
        60, 102, 102, 102,  60,  24, 126,  24,
        63,  51,  63,  48,  48, 112, 240, 224,
        127,  99, 127,  99,  99, 103, 230, 192,
        24, 219,  60, 231, 231,  60, 219,  24,
        128, 224, 248, 254, 248, 224, 128,   0,
        2,  14,  62, 254,  62,  14,   2,   0,
        24,  60, 126,  24,  24, 126,  60,  24,
        102, 102, 102, 102, 102,   0, 102,   0,
        127, 219, 219, 123,  27,  27,  27,   0,
        62,  97,  60, 102, 102,  60, 134, 124,
        0,   0,   0,   0, 126, 126, 126,   0,
        24,  60, 126,  24, 126,  60,  24, 255,
        24,  60, 126,  24,  24,  24,  24,   0,
        24,  24,  24,  24, 126,  60,  24,   0,
        0,  24,  12, 254,  12,  24,   0,   0,
        0,  48,  96, 254,  96,  48,   0,   0,
        0,   0, 192, 192, 192, 254,   0,   0,
        0,  36, 102, 255, 102,  36,   0,   0,
        0,  24,  60, 126, 255, 255,   0,   0,
        0, 255, 255, 126,  60,  24,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,
        24,  60,  60,  24,  24,   0,  24,   0,
        102, 102,  36,   0,   0,   0,   0,   0,
        108, 108, 254, 108, 254, 108, 108,   0,
        24,  62,  96,  60,   6, 124,  24,   0,
        0, 198, 204,  24,  48, 102, 198,   0,
        56, 108,  56, 118, 220, 204, 118,   0,
        24,  24,  48,   0,   0,   0,   0,   0,
        12,  24,  48,  48,  48,  24,  12,   0,
        48,  24,  12,  12,  12,  24,  48,   0,
        0, 102,  60, 255,  60, 102,   0,   0,
        0,  24,  24, 126,  24,  24,   0,   0,
        0,   0,   0,   0,   0,  24,  24,  48,
        0,   0,   0, 126,   0,   0,   0,   0,
        0,   0,   0,   0,   0,  24,  24,   0,
        6,  12,  24,  48,  96, 192, 128,   0,
        56, 108, 198, 214, 198, 108,  56,   0,
        24,  56,  24,  24,  24,  24, 126,   0,
        124, 198,   6,  28,  48, 102, 254,   0,
        124, 198,   6,  60,   6, 198, 124,   0,
        28,  60, 108, 204, 254,  12,  30,   0,
        254, 192, 192, 252,   6, 198, 124,   0,
        56,  96, 192, 252, 198, 198, 124,   0,
        254, 198,  12,  24,  48,  48,  48,   0,
        124, 198, 198, 124, 198, 198, 124,   0,
        124, 198, 198, 126,   6,  12, 120,   0,
        0,  24,  24,   0,   0,  24,  24,   0,
        0,  24,  24,   0,   0,  24,  24,  48,
        6,  12,  24,  48,  24,  12,   6,   0,
        0,   0, 126,   0,   0, 126,   0,   0,
        96,  48,  24,  12,  24,  48,  96,   0,
        124, 198,  12,  24,  24,   0,  24,   0,
        124, 198, 222, 222, 222, 192, 120,   0,
        56, 108, 198, 254, 198, 198, 198,   0,
        252, 102, 102, 124, 102, 102, 252,   0,
        60, 102, 192, 192, 192, 102,  60,   0,
        248, 108, 102, 102, 102, 108, 248,   0,
        254,  98, 104, 120, 104,  98, 254,   0,
        254,  98, 104, 120, 104,  96, 240,   0,
        60, 102, 192, 192, 206, 102,  58,   0,
        198, 198, 198, 254, 198, 198, 198,   0,
        60,  24,  24,  24,  24,  24,  60,   0,
        30,  12,  12,  12, 204, 204, 120,   0,
        230, 102, 108, 120, 108, 102, 230,   0,
        240,  96,  96,  96,  98, 102, 254,   0,
        198, 238, 254, 254, 214, 198, 198,   0,
        198, 230, 246, 222, 206, 198, 198,   0,
        124, 198, 198, 198, 198, 198, 124,   0,
        252, 102, 102, 124,   96, 96, 240,   0,
        124, 198, 198, 198, 198, 206, 124,  14,
        252, 102, 102, 124, 108, 102, 230,   0,
        60, 102,  48,  24,  12, 102,  60,   0,
        126, 126,  90,  24,  24,  24,  60,   0,
        198, 198, 198, 198, 198, 198, 124,   0,
        198, 198, 198, 198, 198, 108,  56,   0,
        198, 198, 198, 214, 214, 254, 108,   0,
        198, 198, 108,  56, 108, 198, 198,   0,
        102, 102, 102,  60,  24,  24,  60,   0,
        254, 198, 140,  24,  50, 102, 254,   0,
        60,  48,  48,  48,  48,  48,  60,   0,
        192,  96,  48,  24,  12,   6,   2,   0,
        60,  12,  12,  12,  12,  12,  60,   0,
        16,  56, 108, 198,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0, 255,
        48,  24,  12,   0,   0,   0,   0,   0,
        0,   0, 120,  12, 124, 204, 118,   0,
        224,  96, 124, 102, 102, 102, 220,   0,
        0,   0, 124, 198, 192, 198, 124,   0,
        28,  12, 124, 204, 204, 204, 118,   0,
        0,   0, 124, 198, 254, 192, 124,   0,
        60, 102,  96, 248,  96,  96, 240,   0,
        0,   0, 118, 204, 204, 124,  12, 248,
        224,  96, 108, 118, 102, 102, 230,   0,
        24,   0,  56,  24,  24,  24,  60,   0,
        6,   0,   6,   6,   6, 102, 102,  60,
        224,  96, 102, 108, 120, 108, 230,   0,
        56,  24,  24,  24,  24,  24,  60,   0,
        0,   0, 236, 254, 214, 214, 214,   0,
        0,   0, 220, 102, 102, 102, 102,   0,
        0,   0, 124, 198, 198, 198, 124,   0,
        0,   0, 220, 102, 102, 124,  96, 240,
        0,   0, 118, 204, 204, 124,  12,  30,
        0,   0, 220, 118,  96,  96, 240,   0,
        0,   0, 126, 192, 124,   6, 252,   0,
        48,  48, 252,  48,  48,  54,  28,   0,
        0,   0, 204, 204, 204, 204, 118,   0,
        0,   0, 198, 198, 198, 108,  56,   0,
        0,   0, 198, 214, 214, 254, 108,   0,
        0,   0, 198, 108,  56, 108, 198,   0,
        0,   0, 198, 198, 198, 126,   6, 252,
        0,   0, 126,  76,  24,  50, 126,   0,
        14,  24,  24, 112,  24,  24,  14,   0,
        24,  24,  24,  24,  24,  24,  24,   0,
        112,  24,  24,  14,  24,  24, 112,   0,
        118, 220,   0,   0,   0,   0,   0,   0,
        0,  16,  56, 108, 198, 198, 254,   0,
        124, 198, 192, 192, 198, 124,  12, 120,
        204,   0, 204, 204, 204, 204, 118,   0,
        12,  24, 124, 198, 254, 192, 124,   0,
        124, 130, 120,  12, 124, 204, 118,   0,
        198,   0, 120,  12, 124, 204, 118,   0,
        48,  24, 120,  12, 124, 204, 118,   0,
        48,  48, 120,  12, 124, 204, 118,   0,
        0,   0, 126, 192, 192, 126, 12,   56,
        124, 130, 124, 198, 254, 192, 124,   0,
        198,   0, 124, 198, 254, 192, 124,   0,
        48,  24, 124, 198, 254, 192, 124,   0,
        102,  0,  56,  24,  24,  24,  60,   0,
        124, 130,  56,  24,  24,  24,  60,   0,
        48,  24,   0,  56,  24,  24,  60,   0,
        198,  56, 108, 198, 254, 198, 198,   0,
        56, 108, 124, 198, 254, 198, 198,   0,
        24,  48, 254, 192, 248, 192, 254,   0,
        0,   0, 126,  24, 126, 216, 126,   0,
        62, 108, 204, 254, 204, 204, 206,   0,
        124, 130, 124, 198, 198, 198, 124,   0,
        198,   0, 124, 198, 198, 198, 124,   0,
        48,  24, 124, 198, 198, 198, 124,   0,
        120, 132,   0, 204, 204, 204, 118,   0,
        96,  48, 204, 204, 204, 204, 118,   0,
        198,   0, 198, 198, 198, 126,   6, 252,
        198,  56, 108, 198, 198, 108,  56,   0,
        198,   0, 198, 198, 198, 198, 124,   0,
        24,  24, 126, 192, 192, 126,  24,  24,
        56, 108, 100, 240,  96, 102, 252,   0,
        102, 102,  60, 126,  24, 126,  24,  24,
        248, 204, 204, 250, 198, 207, 198, 199,
        14,  27,  24,  60,  24, 216, 112,   0,
        24,  48, 120,  12, 124, 204, 118,   0,
        12,  24,   0,  56,  24,  24,  60,   0,
        12,  24, 124, 198, 198, 198, 124,   0,
        24,  48, 204, 204, 204, 204, 118,   0,
        118, 220,   0, 220, 102, 102, 102,   0,
        118, 220,   0, 230, 246, 222, 206,   0,
        60, 108, 108,  62,   0, 126,   0,   0,
        56, 108, 108,  56,   0, 124,   0,   0,
        24,   0,  24,  24,  48,  99,  62,   0,
        0,   0,   0, 254, 192, 192,   0,   0,
        0,   0,   0, 254,   6,   6,   0,   0,
        99, 230, 108, 126,  51, 102, 204,  15,
        99, 230, 108, 122,  54, 106, 223,   6,
        24,   0,  24,  24,  60,  60,  24,   0,
        0,  51, 102, 204, 102,  51,   0,   0,
        0, 204, 102,  51, 102, 204,   0,   0,
        34, 136,  34, 136,  34, 136,  34, 136,
        85, 170,  85, 170,  85, 170,  85, 170,
        119, 221, 119, 221, 119, 221, 119, 221,
        24,  24,  24,  24,  24,  24,  24,  24,
        24,  24,  24,  24, 248,  24,  24,  24,
        24,  24, 248,  24, 248,  24,  24,  24,
        54,  54,  54,  54, 246,  54,  54,  54,
        0,   0,   0,   0, 254,  54,  54,  54,
        0,   0, 248,  24, 248,  24,  24,  24,
        54,  54, 246,   6, 246,  54,  54,  54,
        54,  54,  54,  54,  54,  54,  54,  54,
        0,   0, 254,   6, 246,  54,  54,  54,
        54,  54, 246,   6, 254,   0,   0,   0,
        54,  54,  54,  54, 254,   0,   0,   0,
        24,  24, 248,  24, 248,   0,   0,   0,
        0,   0,   0,   0, 248,  24,  24,  24,
        24,  24,  24,  24,  31,   0,   0,   0,
        24,  24,  24,  24, 255,   0,   0,   0,
        0,   0,   0,   0, 255,  24,  24,  24,
        24,  24,  24,  24,  31,  24,  24,  24,
        0,   0,   0,   0, 255,   0,   0,   0,
        24,  24,  24,  24, 255,  24,  24,  24,
        24,  24,  31,  24,  31,  24,  24,  24,
        54,  54,  54,  54,  55,  54,  54,  54,
        54,  54,  55,  48,  63,   0,   0,   0,
        0,   0,  63,  48,  55,  54,  54,  54,
        54,  54, 247,   0, 255,   0,   0,   0,
        0,   0, 255,   0, 247,  54,  54,  54,
        54,  54,  55,  48,  55,  54,  54,  54,
        0,   0, 255,   0, 255,   0,   0,   0,
        54,  54, 247,   0, 247,  54,  54,  54,
        24,  24, 255,   0, 255,   0,   0,   0,
        54,  54,  54,  54, 255,   0,   0,   0,
        0,   0, 255,   0, 255,  24,  24,  24,
        0,   0,   0,   0, 255,  54,  54,  54,
        54,  54,  54,  54,  63,   0,   0,   0,
        24,  24,  31,  24,  31,   0,   0,   0,
        0,   0,  31,  24,  31,  24,  24,  24,
        0,   0,   0,   0,  63,  54,  54,  54,
        54,  54,  54,  54, 255,  54,  54,  54,
        24,  24, 255,  24, 255,  24,  24,  24,
        24,  24,  24,  24, 248,   0,   0,   0,
        0,   0,   0,   0,  31,  24,  24,  24,
        255, 255, 255, 255, 255, 255, 255, 255,
        0,   0,   0,   0, 255, 255, 255, 255,
        240, 240, 240, 240, 240, 240, 240, 240,
        15,  15,  15,  15,  15,  15,  15,  15,
        255, 255, 255, 255,   0,   0,   0,   0,
        0,   0, 118, 220, 200, 220, 118,   0,
        120, 204, 204, 216, 204, 198, 204,   0,
        254, 198, 192, 192, 192, 192, 192,   0,
        0,   0, 254, 108, 108, 108, 108,   0,
        254, 198,  96,  48,  96, 198, 254,   0,
        0,   0, 126, 216, 216, 216, 112,   0,
        0,   0, 102, 102, 102, 102, 124, 192,
        0, 118, 220,  24,  24,  24,  24,   0,
        126,  24,  60, 102, 102,  60,  24, 126,
        56, 108, 198, 254, 198, 108,  56,   0,
        56, 108, 198, 198, 108, 108, 238,   0,
        14,  24,  12,  62, 102, 102,  60,   0,
        0,   0, 126, 219, 219, 126,   0,   0,
        6,  12, 126, 219, 219, 126,  96, 192,
        30,  48,  96, 126,  96,  48,  30,   0,
        0, 124, 198, 198, 198, 198, 198,   0,
        0, 254,   0, 254,   0, 254,   0,   0,
        24,  24, 126,  24,  24,   0, 126,   0,
        48,  24,  12,  24,  48,   0, 126,   0,
        12,  24,  48,  24,  12,   0, 126,   0,
        14,  27,  27,  24,  24,  24,  24,  24,
        24,  24,  24,  24,  24, 216, 216, 112,
        0,  24,   0, 126,   0,  24,   0,   0,
        0, 118, 220,   0, 118, 220,   0,   0,
        56, 108, 108,  56,   0,   0,   0,   0,
        0,   0,   0,  24,  24,   0,   0,   0,
        0,   0,   0,  24,   0,   0,   0,   0,
        15,  12,  12,  12, 236, 108,  60,  28,
        108,  54,  54,  54,  54,   0,   0,   0,
        120,  12,  24,  48, 124,   0,   0,   0,
        0,   0,  60,  60,  60,  60,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0
};

#endif //SPI_FONT_H
