# DECA Games Challenge

_This is a socket server (running on localhost with port 9090) developed for Windows 10 for DECA Games company interview.

## Used technologies.

* C++14.
* [pugixml](https://github.com/zeux/pugixml)
* [libcpr](https://github.com/libcpr/cpr)
* [googletest](https://github.com/google/googletest)

## How to run (Windows 10).

```
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles"
cmake --build .
```

### For running tests:
```
bin\DecaGamesServer_tst.exe
```

### For running server:
```
bin\DecaGamesServer_run.exe
```
_Examples of sending messages to the server:

```
echo This is a wrong format message | nc 127.0.0.1 9090

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