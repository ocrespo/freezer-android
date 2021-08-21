set (FreezerTest_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/model)


add_executable(FreezerTest ${FreezerTest_SOURCES})


find_package( Threads )

include_directories(${PROJECT_INCLUDE_DIR})

include_directories(${PROJECT_SOURCE_DIR})


target_link_libraries(FreezerTest $<TARGET_OBJECTS:model>
								${CMAKE_THREAD_LIBS_INIT} 
								gmock
                              	gtest
                              	${Boost_LIBRARIES}
                               	)                               	

add_test(${PROJECT_NAME}  FreezerTest)

add_custom_command(TARGET FreezerTest
                    POST_BUILD
                    COMMAND FreezerTest
                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                    COMMENT "Running FreezerTest ${CMAKE_CURRENT_BINARY_DIR}" VERBATIM)
