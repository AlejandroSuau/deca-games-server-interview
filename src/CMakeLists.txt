# local_equipment
add_library(local_equipment
    local_equipment.cpp
)

target_link_libraries(local_equipment
    PUBLIC
    pugixml
)

target_include_directories(local_equipment
    PUBLIC
    "${PROJECT_SOURCE_DIR}/include"
)

# character_equipment_loader
add_library(character_equipment_loader
    character_equipment_loader.cpp
)

target_include_directories(character_equipment_loader
    PUBLIC
    "${PROJECT_SOURCE_DIR}/include"
)

target_link_libraries(character_equipment_loader
    PUBLIC
    cpr
    pugixml
    local_equipment
)

# message_handler_load_equipment
add_library(message_handler_load_equipment
    message_handler_load_equipment.cpp
)

target_include_directories(message_handler_load_equipment
    PUBLIC
    "${PROJECT_SOURCE_DIR}/include"
)

target_link_libraries(message_handler_load_equipment
    PUBLIC
    character_equipment_loader
    local_equipment
)

# server
add_library(server
    server.cpp
)

target_include_directories(server
    PUBLIC
    "${PROJECT_SOURCE_DIR}/include"
)

target_link_libraries(server
    PUBLIC
    message_handler_load_equipment
)

# Main executable.
add_executable("${CMAKE_PROJECT_NAME}" main.cpp)
target_include_directories("${CMAKE_PROJECT_NAME}"
    PUBLIC
    "${PROJECT_SOURCE_DIR}/include"
)

target_include_directories("${CMAKE_PROJECT_NAME}"
    PRIVATE
    server
)

target_link_libraries("${CMAKE_PROJECT_NAME}"
    PRIVATE
    server
)

