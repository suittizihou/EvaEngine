[33mcommit 45381fc0393e6d28e5ce64892c4c358d9bf59c00[m[33m ([m[1;36mHEAD -> [m[1;32mSystemChange_1[m[33m)[m
Author: suittizihou <suittizihou@gmail.com>
Date:   Fri Dec 11 21:09:05 2020 +0900

    vertual呼び出しのオーバーヘッドを無くすように中身の処理を一新。ここでのvertualの呼び出しのオーバーヘッドとはメモリ呼び出しなどの低レベルなものではなく

[33mcommit 3203c40eea1f87711931be74f95b88d82f4a2748[m[33m ([m[1;31morigin/main[m[33m, [m[1;31morigin/HEAD[m[33m, [m[1;32mmain[m[33m)[m
Merge: 4bc24e1 852c116
Author: suittizihou <suittizihou@gmail.com>
Date:   Thu Dec 10 10:04:08 2020 +0900

    Merge branch 'main' of https://github.com/suittizihou/DirectX11Project into main

[33mcommit 4bc24e116cdf6fac7e21e3ccaa9f670fcd23e217[m
Author: suittizihou <suittizihou@gmail.com>
Date:   Thu Dec 10 10:03:12 2020 +0900

    テスト用プログラムをちょこっと編集

[33mcommit 852c116f337316c7df7be0eccda423d168e743d6[m
Author: suittizihou <suittizihou@gmail.com>
Date:   Tue Nov 17 17:31:53 2020 +0900

    テストスクリプトの作成(ジャンプとか)

[33mcommit fba905316faf69a692f3aa814d9fcda0afc1dcc5[m
Author: suittizihou <suittizihou@gmail.com>
Date:   Tue Nov 10 18:07:56 2020 +0900

    耐久テストの結果かなり絶望的という結果が。。。

[33mcommit 99d42f4c882e97b62623d4bf2fe366e480aff069[m
Author: suittizihou <suittizihou@gmail.com>
Date:   Tue Nov 10 11:28:39 2020 +0900

    解放漏れしていたシェーダー関連のリソースをちゃんと解放するようにした

[33mcommit b867c43ace5ce39f12dade1f2c3bb1d57c7de806[m
Author: suittizihou <suittizihou@gmail.com>
Date:   Tue Nov 10 10:03:30 2020 +0900

    Vector3の正規化でゼロの値だけ返してる関数があったのを修正...

[33mcommit 8d676074e152288a1b982dc0cc93c6685730e994[m
Author: suittizihou <suittizihou@gmail.com>
Date:   Tue Nov 10 01:22:59 2020 +0900

    ビュー行列の計算間違っていたのを修正、ある程度動けるサンプルまでは作った

[33mcommit 1e5a3acc06a9020198cf6d4895cb291ee5b27050[m
Author: suittizihou <suittizihou@gmail.com>
Date:   Mon Nov 9 21:54:48 2020 +0900

    コンポーネントシステムとの連携をさせた。

[33mcommit cc6ff1f53bee7b6f40fe703aa6d0bf5fb5c4e987[m
Author: suittizihou <suittizihou@gmail.com>
Date:   Mon Nov 9 00:23:31 2020 +0900

    頂点を直接セットと描画、FBXファイルの読み込みと描画、VRMファイルの読み込みと描画ができるようになった。
    でもまだマテリアルの設定とかテクスチャの読み込みはしてない

[33mcommit dac3a5ac4bb2fe80fa013784b1cad4399ebc5008[m
Author: suittizihou <suittizihou@gmail.com>
Date:   Sun Nov 8 16:20:32 2020 +0900

    色々やってみた結果定数バッファの作り方かシェーダーがバグっていると思われる

[33mcommit 5dac51a0da889fd5850d752b6ef1da1e0da4f0fc[m
Author: suittizihou <suittizihou@gmail.com>
Date:   Sun Nov 8 14:34:13 2020 +0900

    ポリゴン描画はできてるやーつ
    次はモデルの描画
    定数バッファ、頂点バッファ、インデックスバッファがバグっていると思われる
    頂点バッファ、インデックスバッファをどこかで二回やってるとか

[33mcommit 512ec181bd692636dd349831258e06119ab08871[m
Author: suittizihou <suittizihou@gmail.com>
Date:   Fri Nov 6 23:36:32 2020 +0900

    FBXモデルの読み込みで頂点バッファやインデックスバッファの作成する部分をコメントアウトしていたため、そのコメントアウトを消して作成されるようにした。

[33mcommit 3d86ec8e5090e6ca1f40b193b9569c3164c0834a[m
Author: suittizihou <suittizihou@gmail.com>
Date:   Fri Nov 6 02:16:13 2020 +0900

    怪しい箇所の修正はしたが、いまだにポリゴンが出ない

[33mcommit 6137df11cefcf7fe0078e891350e4b30e7009328[m
Author: suittizihou <suittizihou@gmail.com>
Date:   Fri Nov 6 01:50:00 2020 +0900

    シェーダーのリソースマネージャー作ろうと思ったけど既に作ってあった(ShaderDataBase)
    次のやることはいまなぜかポリゴンがでなくなっちゃったから出るように頑張るところ
    原因の予想はIndexBufferがおかしいとかVertexLayoutがおかしいとか。。。
    ポリゴンが裏返ってる可能性あり

[33mcommit 36ed621d243bdae833cdeff77291f3d70e8c38b9[m
Author: suittizihou <suittizihou@gmail.com>
Date:   Fri Nov 6 01:35:10 2020 +0900

    シェーダーのリソースをまだ使っているのにComPtrでリリースされていたのが原因でエラーが起きていた。
    Releaseの処理をどこかのタイミングで実行するようにしたけどいいタイミングがみつからん。。。
    いっそのことMapで各シェーダーファイルを管理して任意のタイミングで消せるようにした方がいいかも

[33mcommit 0b0b3a16bd0ebb6ee598f218c6ed05aa70109ccb[m
Author: suittizihou <suittizihou@gmail.com>
Date:   Thu Nov 5 17:48:07 2020 +0900

    色々作った

[33mcommit b1006312d014c45775fd864862fbe2cc29f26b6a[m
Author: suittizihou <suittizihou@gmail.com>
Date:   Thu Nov 5 09:40:47 2020 +0900

    学校で使ってるノートPCでも動くようにした

[33mcommit 2b65e57871e5a19d237d7c934f7ac00f42626368[m
Author: suittizihou <suittizihou@gmail.com>
Date:   Thu Nov 5 00:19:59 2020 +0900

    深度ステンシルビューなどを追加した。
    ポリゴンがやっと出るようになった！！！
    原因はインデックスバッファの順番が違うことで、ポリゴンが裏返っていたこと

[33mcommit 4320c0b90022cf61b8ebe4b97d6bc97ded734c45[m
Author: suittizihou <suittizihou@gmail.com>
Date:   Tue Nov 3 02:04:11 2020 +0900

    includeのパス指定間違っていたのを修正

[33mcommit 145074c29118db46ac426af0147848e12ed67853[m
Author: suittizihou <suittizihou@gmail.com>
Date:   Tue Nov 3 01:59:38 2020 +0900

    各シェーダーのリソース管理部分ができたと思われる

[33mcommit 7920af27e711019f6298afc3c4fa4f9a58817095[m
Author: suittizihou <suittizihou@gmail.com>
Date:   Mon Nov 2 21:20:56 2020 +0900

    ピクセルシェーダー、ジオメトリシェーダー、コンピュートシェーダー、ハルシェーダー、ドメインシェーダーのコンパイルに対応
    インプットレイアウトの作成も対応

[33mcommit 9225cc801c76c4975264dd23ef0f0f01282f9d8b[m
Author: suittizihou <suittizihou@gmail.com>
Date:   Sat Oct 31 00:49:01 2020 +0900

    ・リーク出力より前に呼び出されているDLL側のメモリ確保に関してはメモリリークとして出力しないようにした(メモリリークチェック範囲の指定)
    ・DirectX12Projectからコンポーネントの仕組みやシーン切り替え、作ってたコンポーネント関連のコードを丸っと持ってきた

[33mcommit 1d93bfb7b5e50150fc23c26740ccb9adf5c77ffe[m
Author: suittizihou <suittizihou@gmail.com>
Date:   Thu Oct 29 21:39:43 2020 +0900

    初期プロジェクト
