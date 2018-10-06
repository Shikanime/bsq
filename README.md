# 流体 v1.5.8

ガンダムマスタースーツ

docker build -t bsq .: プロジェクトをdockerize

docker run --rm -it -v ${PWD}:/usr/src/priv bsq: Dockerでプロジェクトを実行する

make: プロジェクトをコンパイルする

make init: プロジェクトを初期化する

make clean: クリア "オブジェクト"と "ソース"ディレクター

make fclean: "オブジェクト"と"ソース"ディレクトリを削除する

make re: "オブジェクト"と "ソース"ディレクトリを削除し、プロジェクトを再コンパイルする
