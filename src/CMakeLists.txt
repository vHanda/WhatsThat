add_executable(whatsAppTest
    main.cpp
    whatsappjsinterface.cpp
)

target_link_libraries(whatsAppTest Qt5::WebEngine Qt5::WebEngineWidgets Qt5::WebChannel)

install(FILES webChan.js jquery.js DESTINATION ${DATA_INSTALL_DIR}/whatsapptest)
install(TARGETS whatsAppTest DESTINATION ${BIN_INSTALL_DIR})
