

#Source
       
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/model)
        
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/presenter)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/view)

set (Freezer_SOURCES ${Freezer_SOURCES} 
					main.cpp
					$<TARGET_OBJECTS:model>
					)


#Resource

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Resources)

qt5_add_resources(Freezer_RESOURCES ${Freezer_RESOURCES} )


add_executable(${PROJECT_NAME}  ${Freezer_SOURCES} ${Freezer_RESOURCES})

target_link_libraries(${PROJECT_NAME}  Qt5::Widgets)
target_link_libraries(${PROJECT_NAME}  ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME}  ${CMAKE_THREAD_LIBS_INIT})

add_test(${PROJECT_NAME} FreezerTest)
 
install (TARGETS ${PROJECT_NAME}  DESTINATION ${CMAKE_BUILD_TYPE}/bin)




