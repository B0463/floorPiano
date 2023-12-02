#include "includes.hpp"

void setup() {
    pinMode(13, OUTPUT);  // Built in
    pinMode(3, OUTPUT);   // Sound output
    Serial.begin(115200); // Serial rate 115200b/s
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);
    pinMode(A3, INPUT);
    pinMode(A4, INPUT);
    pinMode(A5, INPUT);
    pinMode(A6, INPUT);
    pinMode(A7, INPUT);
}
bool biState=0; // Blink state
void loop() {
    uint16_t analogValues[7]={0};
    MaFilter(SAMPLINGINTERVAL, WINDOWSIZE, analogValues); // Put filtred values in analogValues
    uint8_t use=0;
    for(uint16_t i=0;i<7;i++) {
        if(analogValues[i] < TOUCHSENSE) {tone(3, keyTones[i]); use=i+1; break;} // Play key
    }
    if(!use) noTone(3); // Stop key
    #ifdef DEBUG
        Serial.write(27);    // Serial clear
        Serial.print("[2J"); //
        Serial.write(27);    //
        Serial.print("[H");  //
        Serial.println("Port|Value |Press"); // Header
        for(uint8_t i=0;i<7;i++) {
            uint16_t value = analogValues[i];
            Serial.print("A" + String(i+1) + "  |");
            if(value < 10) Serial.print("    ");      // Number spacing
            else if(value < 100) Serial.print("   "); //
            else if(value < 1000) Serial.print("  "); //
            else Serial.print(" ");                   //
            Serial.print(String(value) + " | " + String((analogValues[i] < TOUCHSENSE) ? 1 : 0)); // Print data
            Serial.println();
        }
        Serial.println("Running key: " + String(use) + "\nfrequence: " + String((!use) ? 0 : keyTones[use-1]));
    #else
        // Flip Built in led state
        digitalWrite(13, !biState);
        biState=!biState;
    #endif
}

void MaFilter(uint8_t si=10, uint8_t ws=20, uint16_t av[7]={0}) {
    uint16_t avBuffer[ws][7]; // Storage all raw samples
    for(uint8_t i=0;i<ws;i++) {
        for(uint8_t j=0;j<7;j++) {
            avBuffer[i][j] = analogRead(j+1); // Samplings
        }
        delay(si);
    }
    for(uint8_t i=0;i<ws;i++) {
        for(uint8_t j=0;j<7;j++) {
            av[j] = av[j] + avBuffer[i][j]; // Add all raw samples
        }
    }
    for(uint8_t i=0;i<7;i++) {
        av[i] = av[i]/ws; // Div all added samples
    }
}