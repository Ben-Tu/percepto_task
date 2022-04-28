
Welcome,

Before running the program please install the following package by:
https://github.com/eclipse/paho.mqtt.cpp

Requirements:
cmake >= VERSION 3.5

Run the following commands:
1) cmake . -> if cmake . not working please run cmake from snap by: /snap/bin/cmake . (after that 'cmake .' need to work properly)
2) make
3) ./percepto

Notes:
You can run the program with debug prints by following commands:
1) ccmake .
2) on user interface navigate to 'WITH_DEBUG_PRINT' press enter to turn on the flag.
3) Repeat the above commands to run.