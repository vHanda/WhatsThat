add_executable(whatsAppTest
    main.cpp
    whatsappjsinterface.cpp
    console.cpp
)

target_link_libraries(whatsAppTest
    Qt5::WebEngine
    Qt5::WebEngineWidgets
    Qt5::WebChannel
    Qt5::Gui
    linenoise
)

install(FILES webChan.js jquery.js DESTINATION ${DATA_INSTALL_DIR}/whatsapptest)
install(TARGETS whatsAppTest DESTINATION ${BIN_INSTALL_DIR})
