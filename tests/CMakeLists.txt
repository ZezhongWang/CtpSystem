ADD_EXECUTABLE(mytest mytest.cpp)
TARGET_LINK_LIBRARIES(mytest CtpTd)

ADD_EXECUTABLE(runmd runMdServer.cpp)
TARGET_LINK_LIBRARIES(runmd CtpMd)

ADD_EXECUTABLE(runtd runTdServer.cpp)
TARGET_LINK_LIBRARIES(runtd CtpTd)

ADD_EXECUTABLE(runmdc runMdClient.cpp)
TARGET_LINK_LIBRARIES(runmdc CtpMd)

ADD_EXECUTABLE(runtdc runTdClient.cpp)
TARGET_LINK_LIBRARIES(runtdc CtpTd)