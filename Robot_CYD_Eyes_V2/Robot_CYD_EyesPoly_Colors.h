

#ifndef ROBOT_CYD_EYESPOLY_COLORS_H
#define ROBOT_CYD_EYESPOLY_COLORS_H

#include <Arduino.h>

#include <string>


namespace RobotCYDEyesPoly {
namespace Colors {

#define COLOR_DEFAULT 10;

struct Palette
{
  std::string PaletteName;
  uint16_t* Palette[16]; 
};



inline void interpolatePalette(uint16_t* startPalette, uint16_t* endPalette, uint16_t* resultPalette, 
                            int stepIndex, int maxSteps, 
                            int bitDepthR, int bitDepthG, int bitDepthB, float acceleration) {
    // Maximální hodnoty na základě bitové hloubky
    int maxRangeR = (1 << bitDepthR) - 1;
    int maxRangeG = (1 << bitDepthG) - 1;
    int maxRangeB = (1 << bitDepthB) - 1;

    if (stepIndex < 0) stepIndex = 0;
    if (stepIndex > maxSteps) stepIndex = maxSteps;

    float t = (float)stepIndex / maxSteps; // Poměr pro interpolaci


    // Modifikace t pomocí akceleračního faktoru
    if (acceleration != 0.0f) {
        if (acceleration > 0.0f) {
            // Zrychlení (exponentiální růst)
            t = powf(t, 1.0f + acceleration);
        } else {
            // Zpomalení (exponentiální zpomalení)
            t = 1.0f - powf(1.0f - t, 1.0f - acceleration);
        }
    }

    for (int i = 0; i < 16; i++) {
        // Rozložit barvu startovací palety
        uint8_t startR = (startPalette[i] >> (bitDepthG + bitDepthB)) & maxRangeR;
        uint8_t startG = (startPalette[i] >> bitDepthB) & maxRangeG;
        uint8_t startB = startPalette[i] & maxRangeB;

        // Rozložit barvu cílové palety
        uint8_t endR = (endPalette[i] >> (bitDepthG + bitDepthB)) & maxRangeR;
        uint8_t endG = (endPalette[i] >> bitDepthB) & maxRangeG;
        uint8_t endB = endPalette[i] & maxRangeB;

        // Interpolace jednotlivých složek
        uint8_t resultR = startR + t * (endR - startR);
        uint8_t resultG = startG + t * (endG - startG);
        uint8_t resultB = startB + t * (endB - startB);

        if (resultR<0)resultR=0;
        if (resultR>31)resultR=31;
        if (resultG<0)resultG=0;
        if (resultG>31)resultG=31;
        if (resultB<0)resultB=0;
        if (resultB>31)resultB=31;
        // Složení výsledné barvy zpět do 16bitového formátu
        resultPalette[i] = (resultR << (bitDepthG + bitDepthB)) | 
                           (resultG << bitDepthB) | 
                           resultB;
    }
}


inline void interpolatePalette5bit(uint16_t* startPalette, uint16_t* endPalette, uint16_t* resultPalette, int stepIndex, int maxSteps) {
    // Ověření, že parametry jsou v platném rozsahu
    if (stepIndex < 0) stepIndex = 0;
    if (stepIndex > maxSteps) stepIndex = maxSteps;

    // Vypočítáme interpolaci (t) na základě aktuálního kroku
    float t = (float)stepIndex / maxSteps;

    for (int i = 0; i < 16; i++) {
        // Rozložíme barvy na složky R, G, B
        uint8_t startR = (startPalette[i] >> 10) & 0x1F;
        uint8_t startG = (startPalette[i] >> 5) & 0x1F;
        uint8_t startB = startPalette[i] & 0x1F;

        uint8_t endR = (endPalette[i] >> 10) & 0x1F;
        uint8_t endG = (endPalette[i] >> 5) & 0x1F;
        uint8_t endB = endPalette[i] & 0x1F;

        // Interpolace každé složky
        uint8_t resultR = startR + t * (endR - startR);
        uint8_t resultG = startG + t * (endG - startG);
        uint8_t resultB = startB + t * (endB - startB);

        // Složení zpět do 16bitové barvy
        resultPalette[i] = (resultR << 10) | (resultG << 5) | resultB;
    }
}
inline uint16_t interpolateColor12bit(uint16_t sourceColor, uint16_t targetColor, int steps, int stepIndex) {
    if (stepIndex >= steps) return targetColor;

    // Rozloží barvy na 4bitové RGB složky
    uint8_t sourceR = (sourceColor >> 8) & 0x0F;
    uint8_t sourceG = (sourceColor >> 4) & 0x0F;
    uint8_t sourceB = sourceColor & 0x0F;

    uint8_t targetR = (targetColor >> 8) & 0x0F;
    uint8_t targetG = (targetColor >> 4) & 0x0F;
    uint8_t targetB = targetColor & 0x0F;

    // Interpolace složek
    uint8_t currentR = sourceR + ((targetR - sourceR) * stepIndex) / steps;
    uint8_t currentG = sourceG + ((targetG - sourceG) * stepIndex) / steps;
    uint8_t currentB = sourceB + ((targetB - sourceB) * stepIndex) / steps;

    // Spojení RGB zpět na 12bitovou barvu
    return (currentR << 8) | (currentG << 4) | currentB;
}

inline void calculateTransitionPalette(const uint16_t* sourcePalette, const uint16_t* targetPalette, uint16_t* outputPalette, int steps, int stepIndex) {
    for (int i = 0; i < 16; i++) {
        uint32_t sourceColor = sourcePalette[i];
        uint32_t targetColor = targetPalette[i];

        // Rozdělení na složky R, G, B
        uint8_t sourceR = (sourceColor >> 16) & 0xFF;
        uint8_t sourceG = (sourceColor >> 8) & 0xFF;
        uint8_t sourceB = sourceColor & 0xFF;

        uint8_t targetR = (targetColor >> 16) & 0xFF;
        uint8_t targetG = (targetColor >> 8) & 0xFF;
        uint8_t targetB = targetColor & 0xFF;

        // Interpolace mezi složkami
        uint8_t currentR = sourceR + ((targetR - sourceR) * stepIndex) / steps;
        uint8_t currentG = sourceG + ((targetG - sourceG) * stepIndex) / steps;
        uint8_t currentB = sourceB + ((targetB - sourceB) * stepIndex) / steps;

        // Rekonstrukce barvy
        outputPalette[i] = (currentR << 16) | (currentG << 8) | currentB;
    }
}

// void Core::calculateTransitionPalette(const uint16_t* sourcePalette, const uint16_t* targetPalette, uint16_t* outputPalette, int steps, int stepIndex) {
//     for (int i = 0; i < 16; i++) {
//         outputPalette[i] = interpolateColor12bit(sourcePalette[i], targetPalette[i], steps, stepIndex);
//     }
// }

// void Core::calculateTransitionPalette(const uint16_t* sourcePalette, const uint16_t* targetPalette, uint16_t* outputPalette, int steps, int stepIndex) {
//     for (int i = 0; i < 16; i++) {
//         // Interpolace každé barvy v paletě
//         uint8_t sourceR = (sourcePalette[i] >> 16) & 0xFF;
//         uint8_t sourceG = (sourcePalette[i] >> 8) & 0xFF;
//         uint8_t sourceB = sourcePalette[i] & 0xFF;

//         uint8_t targetR = (targetPalette[i] >> 16) & 0xFF;
//         uint8_t targetG = (targetPalette[i] >> 8) & 0xFF;
//         uint8_t targetB = targetPalette[i] & 0xFF;

//         uint8_t currentR = sourceR + ((targetR - sourceR) * stepIndex) / steps;
//         uint8_t currentG = sourceG + ((targetG - sourceG) * stepIndex) / steps;
//         uint8_t currentB = sourceB + ((targetB - sourceB) * stepIndex) / steps;

//         outputPalette[i] = (currentR << 16) | (currentG << 8) | currentB;
//     }
// }




inline static uint16_t Black_4bit_palette[16] = {
      0x000000, //  0 - black
      0x000001, //  0 - black
      0x000002, //  0 - black
      0x000003, //  0 - black
      0x000004, //  0 - black
      0x000005, //  0 - black
      0x000006, //  0 - black
      0x000007, //  0 - black
      0x000008, //  0 - black
      0x000009, //  0 - black
      0x00000A, //  0 - black
      0x00000B, //  0 - black
      0x00000C, //  0 - black
      0x00000D, //  0 - black
      0x00000E, //  0 - black
      0x00000F //  0 - black     
    };

inline static uint16_t Default_4bit_palette[16] = {
      0x000000, //  0 - black
      0x000002, //  1 - blue 1
      0x000004, //  2 - blue 2
      0x000006, //  3 - blue 3
      0x000008, //  4 - blue 4
      0x00000A, //  5 - blue 5
      0x00000C, //  6 - blue 6
      0x00000E, //  7 - blue 7
      0x000010, //  8 - blue 8
      0x000012, //  9 - blue 9
      0x00001F, // 10 - Violet 1
      0x00F00F, // 11 - Violet 2
      0x00F000, // 12 - Violet 3
      0xDDDDFF, // 13 - Gray 1
      0xEEEEFF, // 14 - Gray 2
      0xFFFFFF  // 15 - White
    };

    
inline uint16_t Red_4bit_palette[16] = {
      0x000000, //  0 - black
      0x000200, //  1 - blue 1
      0x000400, //  2 - blue 2
      0x000600, //  3 - blue 3
      0x000800, //  4 - blue 4
      0x000A00, //  5 - blue 5
      0x000C00, //  6 - blue 6
      0x000E00, //  7 - blue 7
      0x001000, //  8 - blue 8
      0x001200, //  9 - blue 9
      0x001F00, // 10 - Violet 1
      0x00F00F, // 11 - Violet 2
      0x00F000, // 12 - Violet 3
      0xDDDDFF, // 13 - Gray 1
      0xEEEEFF, // 14 - Gray 2
      0xFFFFFF  // 15 - White
    };
      
inline uint16_t Test_4bit_palette[16] = {
      0x0000, //  0 - black
      0x000F, //  1 - red 1
      0x001F, //  2 - red 2
      0x0F00, //  3 - red 3
      0xF000, //  4 - red 4
      0xF00F, //  5 - red 5
      0xF0F0, //  6 - red 6
      0x00FF, //  7 - red 7
      0x0FF0, //  8 - red 8
      0xFF00, //  9 - red 9
      0xF000, // 10 - Violet 1
      0x0000, // 11 - Violet 2
      0x0FFF, // 12 - Violet 3
      0xFFF0, // 13 - Gray 1
      0xFF00, // 14 - Gray 2
      0xFFFF  // 15 - White
    };
      
inline uint16_t Green_4bit_palette[16] = {
      0x0000, //  0 - black
      0x0100, //  1 - red 1
      0x0200, //  2 - red 2
      0x0300, //  3 - red 3
      0x0400, //  4 - red 4
      0x0500, //  5 - red 5
      0x0600, //  6 - red 6
      0x0700, //  7 - red 7
      0x0800, //  8 - red 8
      0x0900, //  9 - red 9
      0x0a00, // 10 - Violet 1
      0x0b00, // 11 - Violet 2
      0x0c00, // 12 - Violet 3
      0x0d00, // 13 - Gray 1
      0x0e00, // 14 - Gray 2
      0x0f00  // 15 - White
    };

        
inline uint16_t Green2_4bit_palette[16] = {
      0x0000, //  0 - black
      0x0f01, //  1 - red 1
      0x0f02, //  2 - red 2
      0x0f03, //  3 - red 3
      0x0f04, //  4 - red 4
      0x0f05, //  5 - red 5
      0x0f06, //  6 - red 6
      0x0f07, //  7 - red 7
      0x0f08, //  8 - red 8
      0x0f09, //  9 - red 9
      0x0f0a, // 10 - Violet 1
      0x0f0b, // 11 - Violet 2
      0x0f0c, // 12 - Violet 3
      0x0f0d, // 13 - Gray 1
      0x0f0e, // 14 - Gray 2
      0x0f0f  // 15 - White
    };


inline uint16_t White_4bit_palette[16] = {
      0x00000,
      0x01110,
      0x02220,
      0x03330,
      0x04440,
      0x05550,
      0x06660,
      0x07770,
      0x08880,
      0x09990,
      0x0aaa0,
      0x0bbb0,
      0x0ccc0,
      0x0ddd0,
      0x0eee0,
      0x0fff0
    };

    
inline uint16_t White2_4bit_palette[16] = {
      0x00000,
      0x0111F,
      0x0222F,
      0x0333F,
      0x0444F,
      0x0555F,
      0x0666F,
      0x0777F,
      0x0888F,
      0x0999F,
      0x0aaaF,
      0x0bbbF,
      0x0cccF,
      0x0dddF,
      0x0eeeF,
      0x0fffF
    };
inline uint16_t sourcePalette[16] = {
    0x000000, 0x0000E0, 0x0000E8, 0x0000EA, 0x0000EB,
    0x0000ED, 0x0000F1, 0x0000F5, 0x0000FD, 0x0000FE,
    0x0000FF, 0x00F00F, 0x00F000, 0xDDDDFF, 0xEEEEFF,
    0xFFFFFF
};

inline uint16_t targetPalette[16] = {
    0x000000, 0xE0000, 0xE8000, 0xEA000, 0xEB000,
    0xED000, 0xF1000, 0xF5000, 0xFD000, 0xFE000,
    0xFF000, 0x00F00F, 0x00F000, 0xDDDDFF, 0xEEEEFF,
    0xFFFFFF
};




}
}

#endif