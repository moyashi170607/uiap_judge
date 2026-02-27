#ifndef MatrixLED_HPP
#define MatrixLED_HPP

#include <Arduino.h>

// CSピン
constexpr uint8_t CS_PIN = 6;

// 連結されているデバイス数
constexpr int NUM_DEV = 4;
// デバイス1つのLEDの行数
constexpr int LED_ROW = 8;
// デバイス1つのLEDの列数
constexpr int LED_COLUMN = 8;

// 端子と逆側の端が0
//  yesで光るデバイス
constexpr int YES_DEV = 0;
// noで光るデバイス
constexpr int NO_DEV = 3;

// 制御レジスタ
constexpr uint8_t REG_NOOP = 0x00;
constexpr uint8_t REG_DECODE_MODE = 0x09;
constexpr uint8_t REG_INTENSITY = 0x0A;
constexpr uint8_t REG_SCAN_LIMIT = 0x0B;
constexpr uint8_t REG_SHUTDOWN = 0x0C;
constexpr uint8_t REG_DISPLAY_TEST = 0x0F;

inline constexpr uint8_t LIGHTUP_ALL_LED[8] = {
    0b11111111, 0b11111111, 0b11111111, 0b11111111,
    0b11111111, 0b11111111, 0b11111111, 0b11111111,
};
inline constexpr uint8_t LIGHTDOWN_ALL_LED[8] = {
    0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000,
};
inline constexpr uint8_t LEFT_COLUMN_LED[8] = {
    0b11110000, 0b11110000, 0b11110000, 0b11110000,
    0b11110000, 0b11110000, 0b11110000, 0b11110000,
};
inline constexpr uint8_t RIGHT_COLUMN_LED[8] = {
    0b00001111, 0b00001111, 0b00001111, 0b00001111,
    0b00001111, 0b00001111, 0b00001111, 0b00001111,
};

// マトリックスLEDの初期化
void setupLed();

// 特定デバイスにだけ reg/val を送り、他には NOP を送る
void sendToDevice(int device, uint8_t reg, uint8_t val);

// 全デバイスに同じデータを送る
void sendAll(uint8_t reg, uint8_t val);

// 特定デバイスのLEDを配列で指定された形に設定する
void setLedToDevice(int device, const uint8_t val[LED_ROW]);

// YESとNOに対応するブロックの明暗を設定する
void setLedYn(bool yes, bool no);

// ブロックとブロックの間を光らせる
void setCenterLed(int left_block, int right_block);

// LEDを全て消灯
void clearLed();

// 標準の明るさに設定
void defaultBrightness();

// 中央のLEDが点灯した後、yesの方に流れていく
void flowToYes();

// 中央のLEDが点灯した後、NOの方に流れていく
void flowToNo();

#endif  // !MatrixLED_HPP
