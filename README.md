# TCP_ProcessCloser

## Description
- You don't need any third libraries, just pure C++ (11 or higher)
- Tested at the Ubuntu 18.04 and Windows 11
## How to start?
1. `git clone https://github.com/losimen/TCP_ProcessCloser.git`
2. Move to the folder that you have cloned
3. Open `./CMakeLists.txt` and build server and client:
   - To build server please change `set(BUILD_SERVER FALSE)` to `set(BUILD_SERVER TRUE)`
   - To build client please change `set(BUILD_CLIENT FALSE)` to `set(BUILD_CLIENT TRUE)`
4. Once you have built the server and client, please start the server, then open the client.
