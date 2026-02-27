#include "matrix_led.hpp"

#include <Arduino.h>
#include <SPI.h>

// SPI通信速度 (Hz)
constexpr uint32_t SPI_CLOCK = 100000;

// マトリックスLEDの初期化
void setupLed() {
    pinMode(CS_PIN, OUTPUT);
    // SPI.setMOSI(MOSI_PIN);
    // SPI.setSCLK(SCLK_PIN);

    digitalWrite(CS_PIN, HIGH);

    SPI.begin();

    sendAll(REG_DISPLAY_TEST, 0x00);  // テストモード無効
    sendAll(REG_DECODE_MODE, 0x00);   // デコードなし
    sendAll(REG_SCAN_LIMIT, 0x07);    // 8 行全スキャン
    sendAll(REG_SHUTDOWN, 0x01);      // 通常動作モード

    defaultBrightness();

    clearLed();
}

// 特定デバイスにだけ reg/val を送り、他には NOP を送る
void sendToDevice(int device, uint8_t reg, uint8_t val) {
    digitalWrite(CS_PIN, LOW);
    SPI.beginTransaction(SPISettings(SPI_CLOCK, MSBFIRST, SPI_MODE0));
    for (int i = 0; i < NUM_DEV; i++) {
        SPI.transfer(i == device ? reg : REG_NOOP);
        SPI.transfer(val);
    }
    SPI.endTransaction();
    digitalWrite(CS_PIN, HIGH);
}

// 全デバイスに同じデータを送る
void sendAll(uint8_t reg, uint8_t val) {
    digitalWrite(CS_PIN, LOW);
    SPI.beginTransaction(SPISettings(SPI_CLOCK, MSBFIRST, SPI_MODE0));
    for (int i = 0; i < NUM_DEV; i++) {
        SPI.transfer(reg);
        SPI.transfer(val);
    }
    SPI.endTransaction();
    digitalWrite(CS_PIN, HIGH);
}

// 特定デバイスのLEDを配列で指定された形に設定する
void setLedToDevice(int device, const uint8_t val[LED_ROW]) {
    for (int i = 0; i < LED_ROW; i++) {
        sendToDevice(device, i + 1, val[i]);
    }
}

// YESとNOに対応するブロックの明暗を設定する
void setLedYn(bool yes, bool no) {
    setLedToDevice(YES_DEV, yes ? LIGHTUP_ALL_LED : LIGHTDOWN_ALL_LED);
    setLedToDevice(NO_DEV, no ? LIGHTUP_ALL_LED : LIGHTDOWN_ALL_LED);
}

// ブロックとブロックの間を光らせる
void setCenterLed(int left_block, int right_block) {
    for (int i = 0; i < NUM_DEV; i++) {
        if (left_block == i) {
            setLedToDevice(i, RIGHT_COLUMN_LED);
        } else if (right_block == i) {
            setLedToDevice(i, LEFT_COLUMN_LED);
        } else {
            setLedToDevice(i, LIGHTDOWN_ALL_LED);
        }
    }
}

// LEDを全て消灯
void clearLed() {
    for (int row = 1; row <= LED_ROW; row++) {
        sendAll(row, 0b00000000);
    };
}

// 標準の明るさに設定
void defaultBrightness() {
    const uint8_t brightness = 0x08;
    sendAll(REG_INTENSITY, brightness);
}

// 中央のLEDが点灯した後、yesの方に流れていく
void flowToYes() {
    setCenterLed(1, 2);
    delay(100);
    setLedToDevice(1, LIGHTUP_ALL_LED);
    setLedToDevice(2, LIGHTDOWN_ALL_LED);
    delay(100);
    setLedToDevice(0, LIGHTDOWN_ALL_LED);
    setCenterLed(0, 1);
    delay(100);
    setLedToDevice(1, LIGHTDOWN_ALL_LED);
    setLedYn(true, false);
}

// 中央のLEDが点灯した後、NOの方に流れていく
void flowToNo() {
    setCenterLed(1, 2);
    delay(100);
    setLedToDevice(2, LIGHTUP_ALL_LED);
    setLedToDevice(1, LIGHTDOWN_ALL_LED);
    delay(100);
    setLedToDevice(3, LIGHTDOWN_ALL_LED);
    setCenterLed(2, 3);
    delay(100);
    setLedToDevice(2, LIGHTDOWN_ALL_LED);
    setLedYn(false, true);
}