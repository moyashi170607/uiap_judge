# uiap_judge

## 概要
CdSセル（光センサ）に手をかざすと、マトリックスLEDがはい/いいえをランダムで表示する「デジタルこっくりさん」です。

CdSセルの光量が閾値を下回ると（暗くなると）「お告げ」演出が発動します。ブザーが鳴り、4枚連結した8x8マトリックスLEDの中央が点灯し、左右どちらか（はい/いいえ）にアニメーションしながら流れていきます。

左側に「はい」、右側に「いいえ」、真ん中に任意のシンボルを書いた紙をマトリックスLEDの上に載せて楽しんでください。

https://github.com/user-attachments/assets/4796fa38-7cb5-41e6-a83b-19890796e3ff

## ハードウェア構成

| コンポーネント | 接続先 |
|---|---|
| CdSセル | A0 (アナログ入力) |
| ランダムシード用ノイズ | A1 (アナログ入力) |
| アクティブブザー | ピン 10 |
| マトリックスLED CS | ピン 6 |
| マトリックスLED SCLK |ハードウェアSCLK|
| マトリックスLED MOSI |ハードウェアMOSI|

`src/matrix_led.hpp`のピンの定数を変更することで、任意のピンに変更することが可能です。

- **UIAPduino V1.4(CH32V003)** https://www.uiap.jp/uiapduino/pro-micro/ch32v003/v1dot4
- **platformIO Core 6.1.19·Home 3.4.4**
- **platform-ch32v** https://github.com/Community-PIO-CH32V/platform-ch32v
- **マトリックスLED**: 8×8 × 4枚 (MAX7219等) をSPIデイジーチェーン接続
  - デバイス 0: はい 側(端子から遠い方)
  - デバイス 3: いいえ 側(端子から近い方)


## ビルド・書き込み

PlatformIO を使用します。

```bash
# ビルド
pio run

# 書き込み (minichlink)
pio run --target upload
```

# コントリビュート
issue, PR どちらも大歓迎です。

## 謝辞
PlatformIOコミュニティ、UIAPduinoコミュニティ、ch32funコミュニティ、platform-ch32vコミュニティ等、本プロジェクトに関わるあらゆる方々、リソースに感謝します。

## ライセンス
このプロジェクトはMITライセンスの下でライセンスされています。詳細についてはLICENSEファイルを参照してください。
