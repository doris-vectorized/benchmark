# doris-benchmark
CK tag:v19.16.2.2-stable

## 快速开始

1. download boost 1.730 to thirdparty
2. download fmt-7.1.3 to thirdparty
3. download gtest to thirdparty
```
bash build.sh
```

## 测试
```
cd build;
for tst in `find -name '*_test'`; do $tst; done
```
## 讨论
