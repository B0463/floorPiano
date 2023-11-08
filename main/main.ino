#define DEBUG

void MaFilter(int si=10, int ws=20, int av[7]={0});

void setup() {
    pinMode(13, OUTPUT);
    pinMode(3, OUTPUT);
    Serial.begin(115200);
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);
    pinMode(A3, INPUT);
    pinMode(A4, INPUT);
    pinMode(A5, INPUT);
    pinMode(A6, INPUT);
    pinMode(A7, INPUT);
}

void loop() {
    int touchSense = 900;
    int samplingInterval = 4;
    int windowSize = 15;
    int analogValues[7]={0};
    MaFilter(samplingInterval, windowSize, analogValues);
    #ifdef DEBUG
    Serial.write(27);
    Serial.print("[2J");
    Serial.write(27);
    Serial.print("[H");
    Serial.println("Port|Value |Press");
    for(int i=0;i<7;i++) {
        int value = analogValues[i];
        Serial.print("A" + String(i+1) + "  |");
        if(value < 10) Serial.print("    ");
        else if(value < 100) Serial.print("   ");
        else if(value < 1000) Serial.print("  ");
        else Serial.print(" ");
        Serial.print(String(value) + " | " + String((value < touchSense) ? 1 : 0));
        Serial.println();
    }
    #endif
    bool uso=0;
    if(analogValues[0] < touchSense) {tone(3, 442); uso=1;}
    if(analogValues[1] < touchSense) {tone(3, 496); uso=1;}
    if(!uso) noTone(3);
}

void MaFilter(int si=10, int ws=20, int av[7]={0}) {
    int avBuffer[ws][7];
    for(int i=0;i<ws;i++) {
        for(int j=0;j<7;j++) {
            avBuffer[i][j] = analogRead(j+1);
        }
        delay(si);
    }
    for(int i=0;i<ws;i++) {
        for(int j=0;j<7;j++) {
            av[j] = av[j] + avBuffer[i][j];
        }
    }
    for(int i=0;i<7;i++) {
        av[i] = av[i]/ws;
    }
}