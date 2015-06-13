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
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDEFrameworkCompilerSettings)
include(ECMAddTests)

find_package(Qt5 5.5 REQUIRED NO_MODULE COMPONENTS WebEngine WebEngineWidgets WebChannel Test)

include_directories(
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/3rdParty/linenoise/src/
)

feature_summary(WHAT ALL
    INCLUDE_QUIET_PACKAGES
    FATAL_ON_MISSING_REQUIRED_PACKAGES
)

add_definitions(-DQT_NO_KEYWORDS)
remove_definitions(-DQT_NO_CAST_FROM_ASCII)
remove_definitions(-DQT_NO_CAST_FROM_BYTEARRAY)

add_subdirectory(3rdParty)
add_subdirectory(src)
add_subdirectory(tool)
