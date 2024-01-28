# FT232H(BITBANG機能付きFTDIチップ)を用いた出力遅延測定システム
## 概要

* BITBANG機能を用いることにより低遅延検知が可能
* FTDI社から提供されるドライバを用いているのでOSに依らず(多分)低遅延
* C言語による実装なのでそこそこ速い
* BOボードが広く出回っている(特にFT232H)

## プロジェクトのゴール

* HID/Serial通信で動作するデバイスに対して命令を送信
* FTDIチップをBITBANGで監視してデバイス動作までの遅延時間を測定する
* 複数回の測定を行い、中央値などを算出

## ソフトウェア

### [latency_checker.c](/latency_checker.c)
#### 概要
実行から特定のPINがグラウンドに落ちるまでの時間を測定する。
#### 注意点
WIP
#### ビルド
静的リンクライブラリが必要。環境に従ったlibファイルをリンクする必要がある。
```bash
gcc -c ./latency_checker.c
gcc ./latency_checker.o ./ftd2xx.lib
```
また、同一ディレクトリにftd2xx.hを配置する必要がある。

### [serial_latency_checker.c](/serial_latency_checker.c)
実装中

## ハードウェア
### FT232HQ BOボード
Adafruit社製のもの。SwitchScienceから購入。
