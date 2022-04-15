project(BasicLoad)
set(CMAKE_CXX_STANDARD 17)
include_directories("${CMAKE_SOURCE_DIR}/sdk/include")

add_library(
	${PROJECT_NAME} 
	SHARED 
	"main.cpp"
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE BulldozerSDK
)