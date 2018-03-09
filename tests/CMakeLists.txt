ADD_EXECUTABLE(mytest mytest.cpp)
TARGET_LINK_LIBRARIES(mytest CtpTd)

ADD_EXECUTABLE(runmd runMdServer.cpp)
TARGET_LINK_LIBRARIES(runmd CtpMd pthread)

ADD_EXECUTABLE(runtd runTdServer.cpp)
TARGET_LINK_LIBRARIES(runtd CtpTd pthread)

ADD_EXECUTABLE(runmdc runMdClient.cpp)
TARGET_LINK_LIBRARIES(runmdc CtpMd pthread)

ADD_EXECUTABLE(runtdc runTdClient.cpp)
TARGET_LINK_LIBRARIES(runtdc CtpTd pthread)