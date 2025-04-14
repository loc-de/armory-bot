file(GLOB SRC_FILES *.cpp)
file(GLOB HDR_FILES *.h)

add_executable(StrafeBot ${SRC_FILES} ${HDR_FILES})

target_include_directories(StrafeBot PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(StrafeBot PRIVATE sio_client)
