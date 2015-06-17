set(WHATSTHAT_LIB_SRCS
    interface.cpp
    chatlistjob.cpp
    chat.cpp
    message.cpp
    sendmessagejob.cpp

    jsinterface.cpp
)

add_library(WhatsThat ${WHATSTHAT_LIB_SRCS})
generate_export_header(WhatsThat BASE_NAME WHATSTHAT EXPORT_FILE_NAME whatsthat_export.h)

target_link_libraries(WhatsThat
PUBLIC
    Qt5::Widgets
PRIVATE
    Qt5::WebEngine
    Qt5::WebEngineWidgets
    Qt5::WebChannel
)

target_include_directories(WhatsThat INTERFACE "$<INSTALL_INTERFACE:${INCLUDE_INSTALL_DIR}/WhatsThat>")

ecm_generate_headers(WhatsThat_CamelCase_HEADERS
    HEADER_NAMES
    Interface
    ChatListJob
    Chat
    SendMessageJob

    PREFIX whatsthat
    REQUIRED_HEADERS WHATSTHAT_HEADERS
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/whatsthat_export.h
    ${WHATSTHAT_HEADERS}
    DESTINATION ${INCLUDE_INSTALL_DIR}/WhatsThat/whatsthat
    COMPONENT Devel
)

install(FILES
    ${WhatsThat_CamelCase_HEADERS}
    DESTINATION ${INCLUDE_INSTALL_DIR}/WhatsThat/WhatsThat
    COMPONENT Devel
)

install(TARGETS WhatsThat DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES webChan.js jquery.js DESTINATION ${DATA_INSTALL_DIR}/whatsthat)
