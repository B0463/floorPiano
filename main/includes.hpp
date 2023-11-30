#pragma once

// Config
#define BOARD 1            // Board to upload code (1-4)
#define DEBUG              // If defined, tx the filtred values of inputs
#define TOUCHSENSE 600     // (0-1023)
#define SAMPLINGINTERVAL 3 // Time(ms) between samples (0-255)
#define WINDOWSIZE 8       // Number of samplings (0-255)

// MaFilter define ( si=samplingInterval, ws=windowSize, av=analogValues )
void MaFilter(uint8_t si=10, uint8_t ws=20, uint16_t av[7]={0});

// Board key ( F=fliped )
#if defined(BOARD) && BOARD == 1
    uint16_t keyTones[7] = {
        131, // 2C
        234, // 2A# F1
        147, // 2D
        221, // 2A  F2
        166, // 2E
        175, // 2F
        197, // 2G  F3
    };
#elif defined(BOARD) && BOARD == 2
    uint16_t keyTones[7] = {
        186  // 2F# F3
        209, // 2G#
        157, // 2D# F2
        139, // 2C# F1
        249, // 2B
        313, // 3D# F4
        279  // 3C#
    };
#elif defined(BOARD) && BOARD == 3
    uint16_t keyTones[7] = {
        295, // 3D
        262, // 3C  F4
        330, // 3E
        351, // 3F
        442, // 3A  F5
        394, // 3G
        468, // 3A# F6
    };
#elif defined(BOARD) && BOARD == 4
    uint16_t keyTones[7] = {
        372, // 3F# F5
        417  // 3G# F6
        496, // 3B
        525, // 4C
        556, // 4C#
        589, // 4D
        0    // N/C
    };
#else
    #error "Select a valid board"
#endif