set(BINARY ${CMAKE_PROJECT_NAME})

set(SOURCES
    character/equipment_loader_exceptions.cpp
    character/equipment_loader.cpp
    character/local_equipment.cpp
    server/message_handler.cpp
    server/message_handler_load_equipment.cpp
    server/server.cpp
    main.cpp
)

add_executable(${BINARY}_run ${SOURCES})

add_library(${BINARY}_lib STATIC ${SOURCES})

target_include_directories(${BINARY}_run
    PUBLIC
    "${PROJECT_SOURCE_DIR}/include"
)

target_link_libraries(${BINARY}_run
    PUBLIC
    cpr
    pugixml
)

target_include_directories(${BINARY}_lib
    PUBLIC
    "${PROJECT_SOURCE_DIR}/include"
)

target_link_libraries(${BINARY}_lib
    PUBLIC
    cpr
    pugixml
)