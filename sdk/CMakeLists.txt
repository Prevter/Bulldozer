cmake_minimum_required (VERSION 3.13)
project(BulldozerSDK VERSION 0.9.5)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(SOURCES_SDK
	"src/teardown.cpp"
)

add_library(${PROJECT_NAME} STATIC ${SOURCES_SDK})

target_include_directories(${PROJECT_NAME} PRIVATE "src/")

target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
  $<INSTALL_INTERFACE:include>
)

set_target_properties(
	${PROJECT_NAME} 
	PROPERTIES 
	VERSION ${PROJECT_VERSION}
	# PUBLIC_HEADER include/teardown.h
)

configure_package_config_file(
    "bulldozer-sdk-config.cmake.in"
    "bulldozer-sdk-config.cmake"
  INSTALL_DESTINATION 
    "lib/bulldozer"
)

configure_file(bulldozer-sdk.pc.in bulldozer-sdk.pc @ONLY)
# target_include_directories(${PROJECT_NAME} PUBLIC include)

install(
  FILES 
    "${CMAKE_CURRENT_BINARY_DIR}/bulldozer-sdk-config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/bulldozer-sdk-config-version.cmake"
  DESTINATION 
    "lib/bulldozer"
)

install(TARGETS ${PROJECT_NAME}
        EXPORT BulldozerSDK
        ARCHIVE DESTINATION "lib"
        LIBRARY DESTINATION "lib"
)

install(
  EXPORT
    BulldozerSDK
  NAMESPACE 
  	${PROJECT_NAME}::
  DESTINATION 
    "lib/bulldozer"
)

install(
  DIRECTORY include DESTINATION .
)

install(FILES ${CMAKE_BINARY_DIR}/bulldozer-sdk.pc 
	DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
	
install(TARGETS ${PROJECT_NAME}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
