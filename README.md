# DECA Games Challenge

_This is a socket server (running on localhost with port 9090) developed for Windows 10 for DECA Games company interview._

## Used technologies.

* C++17.
* CMake.
* [pugixml](https://github.com/zeux/pugixml)
* [libcpr](https://github.com/libcpr/cpr)
* [googletest](https://github.com/google/googletest)

## How to run.

_Inside /bin folder are 2 executables available:_
* Run server: DecaGamesServer_run.exe
* Run tests: DecaGamesServer_tst.exe

## How to build and compiler (Windows 10).

```
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles"
cmake --build .
```

_For running it from terminal, it is necessary to be in the same .exe folder._

### Running tests:
```
cd bin && DecaGamesServer_tst.exe
```

### Running server:
```
cd bin && DecaGamesServer_run.exe
```
_Examples of sending messages to the server:_

```
echo Alejandro Suau want to be part of DECA Games | nc 127.0.0.1 9090

// Expected response: Wrong message format
```

```
echo load alejandro.suau@gmail.com WantToBePartOfDECAGames | nc 127.0.0.1 9090

// Expected response: Account not found.
```

```
echo load backend-testRTG@decagames.com backendtestRTG1 | nc 127.0.0.1 9090

// Order may vary.
// Expected response: Firebrand Staff,Fire Spray Spell,Energy Staff
```
