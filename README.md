
Tests:
echo hello world | nc 127.0.0.1 9090
echo load alejandro.suau@gmail.com password | nc 127.0.0.1 9090
echo load backend-testRTG@decagames.com backendtestRTG1 | nc 127.0.0.1 9090

cmake .. -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles"
cmake --build .
