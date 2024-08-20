project(JointProject LANGUAGES CXX)


add_executable(jointproject ./src/main.cpp ./src/ChatClient.cpp ./src/include/ChatClient.h ./src/include/ChatServer.h ./src/ChatServer.cpp)

