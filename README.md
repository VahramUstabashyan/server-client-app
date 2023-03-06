# Server-Client Application in C++

## Description

This is a small Linux based server-client application one can use to run
various shell commands on remote and get the result back.

## Prerequisites

First, you must have installed C++ Boost library on your device.
If you don't have any, run this in your terminal:

```
sudo apt install libboost-dev
```

And second, CMake will be used to build the project.

```
sudo apt install cmake
```

## Build

```
export SERVER_CLIENT_APP_PROJECT_DIR=/project/directory
cd ${SERVER_CLIENT_APP_PROJECT_DIR}
mkdir build
cd build
cmake ${SERVER_CLIENT_APP_PROJECT_DIR}
```

##### NOTE: You must have this application built both on server side and client side

## Run

### Test
```
${SERVER_CLIENT_APP_PROJECT_DIR}/build/test
```

### Server side
```
${SERVER_CLIENT_APP_PROJECT_DIR}/build/server_app
```

OR with specified _IP_ and _Port_, e.g.:
```
${SERVER_CLIENT_APP_PROJECT_DIR}/build/server_app 0.0.0.0 55555
```

##### NOTE: Enter `quit` to stop the server application

### Client side

```
${SERVER_CLIENT_APP_PROJECT_DIR}/build/client_app
```

##### NOTE: At most 5 client can be connected to the server simultaneously!

## Commands you can use from client side

1. `connect IP PORT` - Connect to the server with ip `IP` and port `PORT`
2. `disconnect` - Disconnect from the currently connected server
3. `shell "COMMAND"` - Run the command `COMMAND` on the connected server
and get the result
4. `quit` - Quit the client application

##### !!! CAUTION: If you run a command that runs forever, you'll never get the result back.

### Sample commands to use:

```
connect 0.0.0.0 55555
shell "pwd"
shell "date"
shell "ping 1.1.1.1 -c 1"
disconnect
quit
```

##### NOTE: You can skip `disconnect` as it will disconnect on `quit` automatically.
