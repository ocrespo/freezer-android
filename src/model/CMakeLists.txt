add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/freezer)


set (Model_SOURCES ${Model_SOURCES} 
 					Model.cpp)


add_library(model OBJECT ${Model_SOURCES}  
						)
						
#set (Observer_SOURCES ${Observer_SOURCES} 
 #                     	${CMAKE_CURRENT_SOURCE_DIR}/Subject.cpp
 #                       ) #Add .cpp here

#add_library(observer OBJECT ${Observer_SOURCES})