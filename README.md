# BLE_CAULについて
2007年ぐらいに(株)タカラトミーから発売されたCAULと呼ばれるラジコンをBLE経由で操作できるようにするプログラムです。
付属のBLE_CAUL.inoをM5StickCPlusに書き込めばそのまま動かす事ができます。
(現在はタイプAのCAULのみ対象としています。タイプBのCAUL対応版もアップする予定です。また、ヘッダファイルとM5.begin関数を変えればM5Atom liteやM5StickCなどの他ボードでも使えるかと思います。)

本プログラムは下記のライブラリを使用します。
- M5StickCPlus バージョン0.0.2にて確認
- IRremoteESP8266 バージョン2.7.19にて確認

M5StickCPlusへの書き込み手順は下記リンクを参照する。

https://interface.cqpub.co.jp/202104support_4/

また、本リポジトリをローカルに直接ダウンロードしてChrome(バージョン92.0.4515.131にて動作確認)でcaul.htmlを開くことで、PCとcaulを直接接続することができます。caul.htmlの動作にはJellyWare Inc.にて作成されたBluejelly.jsと呼ばれるライブラリを使用しています。詳細は下記リンクを参照してください。

https://monomonotech.jp/kurage/webbluetooth/getting_started.html

# 組み立て方
はんだ付けやCAUL車体への加工は基本的に必要ありません。
M5StickCPlusのIR送信部の光がCAUL車体のIR受光部に当たるようにM5StickCPlusを置き、マスキングテープなどで固定してください。

<img src="https://github.com/henjin0/BLE_CAUL/blob/main/image/back.jpg?raw=true" width="300"> <img src="https://github.com/henjin0/BLE_CAUL/blob/main/image/front.jpg?raw=true" width="300">


# LICENSE
Please see [LICENSE](LICENSE).

