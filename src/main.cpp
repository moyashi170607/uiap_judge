
#include <Arduino.h>
#include <SPI.h>

#include "matrix_led.hpp"

// CdSセルの電圧を受け取るアナログピン
constexpr uint8_t CdS_PIN = A0;
// 光量の閾値
constexpr float THRESHOLD = 600;

// 乱数のシードとなるノイズを取り出すアナログピン
constexpr uint8_t SEED_PIN = A1;

// アクティブブザー
constexpr uint8_t BUZZER_PIN = 10;

// シリアル通信レート
constexpr uint32_t BAUD_RATE = 9600;

// お告げ演出
void otuge() {
    digitalWrite(BUZZER_PIN, HIGH);
    clearLed();
    setCenterLed(1, 2);
    delay(1500);
    digitalWrite(BUZZER_PIN, LOW);

    int r_v = random() % 2;

    if (r_v) {
        flowToNo();
    } else {
        flowToYes();
    }

    digitalWrite(BUZZER_PIN, HIGH);

    delay(2000);

    digitalWrite(BUZZER_PIN, LOW);
    clearLed();
}

void setup() {
    // シリアル通信を初期化
    Serial.begin(BAUD_RATE);

    // ブザーのピン
    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(BUZZER_PIN, LOW);

    pinMode(CdS_PIN, INPUT);

    setupLed();

    pinMode(SEED_PIN, INPUT);
    randomSeed(analogRead(SEED_PIN));
}

void loop() {
    int light_value = analogRead(CdS_PIN);
    Serial.println(analogRead(CdS_PIN));

    if (light_value < THRESHOLD) {
        otuge();
    }
}
