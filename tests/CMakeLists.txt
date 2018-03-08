ADD_EXECUTABLE(mytest mytest.cpp)
TARGET_LINK_LIBRARIES(mytest CtpTd)

ADD_EXECUTABLE(runmd runmd.cpp)
TARGET_LINK_LIBRARIES(runmd CtpMd)

ADD_EXECUTABLE(runtd runtd.cpp)
TARGET_LINK_LIBRARIES(runtd CtpTd)