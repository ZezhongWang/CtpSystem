PROJECT(CtpSystem)
SET(CTP_SYSTEM_SRCS
 base/baseengine.cpp
 log/logger.cpp
 md/ctpmdengine.cpp
 md/mdengine.cpp
 td/ctptdengine.cpp
 td/tdengine.cpp
 strategy/basestrategy.cpp
 util/iniparser.cpp
 net/server.cpp
)

SET(CTP_TD_SRCS
 base/baseengine.cpp
 log/logger.cpp
 td/ctptdengine.cpp
 td/tdengine.cpp
 util/iniparser.cpp
 net/server.cpp
)

SET(CTP_MD_SRCS
 base/baseengine.cpp
 log/logger.cpp
 md/ctpmdengine.cpp
 md/mdengine.cpp
 util/iniparser.cpp
)

LINK_DIRECTORIES(
 ${CMAKE_CURRENT_SOURCE_DIR}/../lib/api/ctp
 ${PROJECT_BINARY_DIR}/lib
 /usr/local/lib
 /usr/lib
)

# shared library
ADD_LIBRARY(CtpSystem_dynamic SHARED ${CTP_SYSTEM_SRCS})
TARGET_LINK_LIBRARIES(CtpSystem_dynamic thostmduserapi thosttraderapi)
# static library
ADD_LIBRARY(CtpSystem_static STATIC ${CTP_SYSTEM_SRCS})
TARGET_LINK_LIBRARIES(CtpSystem_static thostmduserapi thosttraderapi)

# td shared library
ADD_LIBRARY(CtpTd_dynamic SHARED ${CTP_TD_SRCS})
TARGET_LINK_LIBRARIES(CtpTd_dynamic thosttraderapi)
# td static library
ADD_LIBRARY(CtpTd_static STATIC ${CTP_TD_SRCS})
TARGET_LINK_LIBRARIES(CtpTd_static thosttraderapi)

# md shared library
ADD_LIBRARY(CtpMd_dynamic SHARED ${CTP_MD_SRCS})
TARGET_LINK_LIBRARIES(CtpMd_dynamic thostmduserapi)
# md static library
ADD_LIBRARY(CtpMd_static STATIC ${CTP_MD_SRCS})
TARGET_LINK_LIBRARIES(CtpMd_static thostmduserapi)

# whole system
SET_TARGET_PROPERTIES(CtpSystem_static PROPERTIES OUTPUT_NAME "CtpSystem")
SET_TARGET_PROPERTIES(CtpSystem_dynamic PROPERTIES OUTPUT_NAME "CtpSystem")
SET_TARGET_PROPERTIES(CtpSystem_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(CtpSystem_dynamic PROPERTIES CLEAN_DIRECT_OUTPUT 1)
# trader
SET_TARGET_PROPERTIES(CtpTd_static PROPERTIES OUTPUT_NAME "CtpTd")
SET_TARGET_PROPERTIES(CtpTd_dynamic PROPERTIES OUTPUT_NAME "CtpTd")
SET_TARGET_PROPERTIES(CtpTd_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(CtpTd_dynamic PROPERTIES CLEAN_DIRECT_OUTPUT 1)
# Market data
SET_TARGET_PROPERTIES(CtpMd_static PROPERTIES OUTPUT_NAME "CtpMd")
SET_TARGET_PROPERTIES(CtpMd_dynamic PROPERTIES OUTPUT_NAME "CtpMd")
SET_TARGET_PROPERTIES(CtpMd_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(CtpMd_dynamic PROPERTIES CLEAN_DIRECT_OUTPUT 1)