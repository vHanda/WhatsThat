set(TOOL_SRCS
    main.cpp
    console.cpp
)

add_executable(whatsthat ${TOOL_SRCS})
target_link_libraries(whatsthat
    WhatsThat
    linenoise
)

install(TARGETS whatsthat DESTINATION ${BIN_INSTALL_DIR})
