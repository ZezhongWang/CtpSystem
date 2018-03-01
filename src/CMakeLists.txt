PROJECT(CtpSystem)
SET(CTP_SYSTEM_SRCS
 base/baseengine.cpp
 log/logger.cpp
 md/ctpmdengine.cpp
 md/mdengine.cpp
 td/ctptdengine.cpp
 td/tdengine.cpp
 strategy/basestrategy.cpp
)

LINK_DIRECTORIES(
  ${PROJECT_SOURCE_DIR}/lib/api/ctp
  ${PROJECT_BINARY_DIR}/lib
  /usr/local/lib
  /usr/lib
)

# shared library
ADD_LIBRARY(CtpSystem_dynamic SHARED ${CTP_SYSTEM_SRCS})
TARGET_LINK_LIBRARIES(CtpSystem_dynamic thostmduserapi.so thosttraderapi.so)
# static library
ADD_LIBRARY(CtpSystem_static STATIC ${CTP_SYSTEM_SRCS})
TARGET_LINK_LIBRARIES(CtpSystem_static thostmduserapi.so thosttraderapi.so)

SET_TARGET_PROPERTIES(CtpSystem_static PROPERTIES OUTPUT_NAME "CtpSystem")
SET_TARGET_PROPERTIES(CtpSystem_dynamic PROPERTIES OUTPUT_NAME "CtpSystem")
SET_TARGET_PROPERTIES(CtpSystem_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(CtpSystem_dynamic PROPERTIES CLEAN_DIRECT_OUTPUT 1)

