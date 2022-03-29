# TensionCPU - CPU load generator
**Generates CPU load in percentage value for set period time and process scheduling policy**

**TensionCPU supports four scheduling policies:**
- OTHER 
- FIFO
- RR
- BATCH

## Features

- CPU load in percentage
- load generation duration in seconds
- scheduling policy
- powered by C++11


## Building for source

###### Build EquinoxLogger first (linked as static library):

```sh
cd EquinoxLogger/Build/
cmake CMakeLists.txt
make
```

###### Build TensionCPU:

```sh
cd TensionCPU/Build/
cmake CMakeLists.txt
make
```

###### For UnitTests:

```sh
cd UnitTests/Build
cmake CMakeLists.txt
make
```
## Examples:
```sh
For help run:               TensionCPU.x86 -h
Run CPU load 80% for 10s:   TensionCPU.x86 -l 80 -T 10
Unlimmited time:            TensionCPU.x86 -l 80 -T 0
Scheduling policy RR:       TensionCPU.x86 -l 80 -T 10 -S r
```
![](https://github.com/jwolak/TensionCPU/blob/main/Screenshot.png?raw=true)

## License

BSD 3-Clause License
**Copyright (c) 2022, Janusz Wolak,**
All rights reserved.
