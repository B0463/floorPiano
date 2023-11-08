#pragma once

//consts
#define BOARD 4
//#define DEBUG
#define TOUCHSENSE 900
#define SAMPLINGINTERVAL 5
#define WINDOWSIZE 15

//defs
void MaFilter(int si=10, int ws=20, int av[7]={0});

//board include
#if defined(BOARD) && BOARD == 1
    #include "board1.hpp"
#elif defined(BOARD) && BOARD == 2
    #include "board2.hpp"
#elif defined(BOARD) && BOARD == 3
    #include "board3.hpp"
#elif defined(BOARD) && BOARD == 4
    #include "board4.hpp"
#else
    #error "Selecione uma placa válida"
#endif