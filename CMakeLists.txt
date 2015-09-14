project(ktexteditor_gocode)

cmake_minimum_required (VERSION 2.8.12 FATAL_ERROR)
set (QT_MIN_VERSION "5.2.0")
set(KF5_DEP_VERSION "5.6.0")

find_package(ECM 1.1.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings)
include(FeatureSummary)

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED Core)

find_package(KF5 "${KF5_DEP_VERSION}" REQUIRED COMPONENTS
#  GuiAddons
  I18n
  KIO
  TextEditor
)


include_directories( ${CMAKE_CURRENT_BINARY_DIR} )

add_definitions(-DTRANSLATION_DOMAIN=\"ktexteditor_gocode\")

set(kgocode_SRCS
  gocodeplugin.cpp
  gocodemodel.cpp
  process.cpp
)

add_library(ktexteditor_gocode MODULE ${kgocode_SRCS})

target_link_libraries(ktexteditor_gocode
  KF5::TextEditor
  KF5::XmlGui
)

install(TARGETS ktexteditor_gocode DESTINATION ${PLUGIN_INSTALL_DIR}/ktexteditor)

# install(FILES ui.rc DESTINATION ${KXMLGUI_INSTALL_DIR}/ktexteditor_gocode)

kcoreaddons_desktop_to_json(ktexteditor_gocode ktexteditor_gocode.desktop)
