cmake_minimum_required(VERSION 2.8.12)

project(WhatsAppWeb)

# ECM setup
find_package(ECM 1.2.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(GenerateExportHeader)
include(ECMGenerateHeaders)
include(ECMPackageConfigHelpers)
include(ECMSetupVersion)
include(FeatureSummary)
include(KDEFrameworkCompilerSettings)
include(ECMAddTests)

find_package(Qt5 REQUIRED NO_MODULE COMPONENTS WebEngine WebEngineWidgets Test)

include_directories(
  ${CMAKE_SOURCE_DIR}
)

feature_summary(WHAT ALL
    INCLUDE_QUIET_PACKAGES
    FATAL_ON_MISSING_REQUIRED_PACKAGES
)

add_definitions(-DQT_NO_KEYWORDS)
remove_definitions(-DQT_NO_CAST_FROM_ASCII)
remove_definitions(-DQT_NO_CAST_FROM_BYTEARRAY)

add_executable(whatsAppTest main.cpp)
target_link_libraries(whatsAppTest Qt5::WebEngine Qt5::WebEngineWidgets)
