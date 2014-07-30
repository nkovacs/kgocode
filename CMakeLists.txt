find_package(KDE4 REQUIRED)

include (KDE4Defaults)
include_directories(${KDE4_INCLUDES})

kde4_add_plugin(ktexteditor_gocode gocodeplugin.cpp gocodemodel.cpp process.cpp)

target_link_libraries(ktexteditor_gocode ${KDE4_KDECORE_LIBS} ${KDE4_KTEXTEDITOR_LIBS})

install(TARGETS ktexteditor_gocode DESTINATION ${PLUGIN_INSTALL_DIR})

install(FILES ktexteditor_gocode.desktop DESTINATION ${SERVICES_INSTALL_DIR})
