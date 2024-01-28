# note
## ソフトウェア
### シリアル通信の実装
C/Cpp標準ライブラリ等にはシリアル通信を楽に行えるようにするライブラリなさそう。
→Linuxの場合、termiosと呼ばれるターミナルIO用のAPIがあるらしい。これを使って送受信ができそう。

#### 参考資料
* https://ssr-yuki.hatenablog.com/entry/2019/02/17/024943
* https://mcommit.hatenadiary.com/entry/2017/07/09/210840

### HIDデバイス制御
制御用の便利そうなライブラリが提供されている。libusbはフォークらしい。

#### 参考資料
* https://github.com/libusb/hidapi
* https://github.com/signal11/hidapi


## ハードウェア
### FT232Hについて
FT_Readは最新の情報を持ってこないらしい。実際、0.6秒程度の反映遅延がコンスタントに発生していた。現状FT_GetBitmodeを使うべきと判断。