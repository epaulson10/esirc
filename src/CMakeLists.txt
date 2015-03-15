set(INCLUDES ${esirc_SOURCE_DIR}/include)
set (SOURCES main.cpp protocol.cpp connect.cpp)

set(Boost_USE_STATIC_LIBS ON) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.57.0 COMPONENTS system thread) 
find_package(Threads REQUIRED)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    add_executable(esirc ${SOURCES})
    target_link_libraries(esirc ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
endif()

