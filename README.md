# doris-benchmark
CK tag:v19.16.2.2-stable

## 快速开始
git submodule update --init --recursive

1. download boost 1.730 to thirdparty
```
bash build.sh
```

## 测试
```
bash test.sh
```

## benchmark
cd bench
mkdir build && cmake .. -DCMAKE\_BUILD\_TYPE=Release -DDORIS\_HOME=/home/workspace/apache-doris/ -DPREBUILT\_THIRDPARTY=/home/workspace/apache-doris/thirdparty/install/
