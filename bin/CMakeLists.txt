add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE image_lib)
target_link_libraries(${PROJECT_NAME} PRIVATE parsing_lib)
target_link_libraries(${PROJECT_NAME} PRIVATE pile_lib)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
