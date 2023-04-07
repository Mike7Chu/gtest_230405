# Google Test
- Google Test: 단위 테스트 프레임워크
- Google Mock: 테스트 대역 프레임워크

- 정적 라이브러리: libgtest.a
  : 라이브러리의 모든 구현이 실행 파일에 포함됩니다.
    라이브러리가 변경될 때마다 라이브러리를 이용하는 바이너리를 다시 컴파일 해야 합니다.

  동적 라이브러리: libgtest.so
  : 라이브러리의 구현이 실행 파일에 포함되지 않습니다.
    실행 파일이 수행될 때, 라이브러리를 로드해서, 사용하기 때문에
    라이브러리가 변경될 때마다 실행 파일을 다시 컴파일할 필요가 없습니다.
- google test 라이브러리는 일반적으로 정적 라이브러리를 많이 사용합니다.


## Google Test 설치 방법
```
$ wget https://github.com/google/googletest/archive/refs/tags/v1.13.0.tar.gz
$ tar xvf v1.13.0.tar.gz
$ rm v1.13.0.tar.gz
$ mv googletest-1.13.0/ googletest

# gtest-all.cc
$ g++ googletest/googletest/src/gtest-all.cc -c -I ./googletest/googletest/include/ -I ./googletest/googletest/

# gtest_main.cc
$ g++ googletest/googletest/src/gtest_main.cc -c -I ./googletest/googletest/include/


# libgtest.a
$ ar rcv libgtest.a gtest-all.o gtest_main.o

```

## Google Mock 설치 방법(Google Test 의존성)
```
# gmock-all.cc
$ g++ googletest/googlemock/src/gmock-all.cc -c \
-I ./googletest/googlemock/include/ \
-I ./googletest/googletest/include/ \
-I ./googletest/googlemock/

# gmock_main.cc
$ g++ googletest/googlemock/src/gmock_main.cc -c \
-I ./googletest/googlemock/include/ \
-I ./googletest/googletest/include/

# libgtest.a
$ ar rcv libgtest.a gmock-all.o gmock_main.o

```
