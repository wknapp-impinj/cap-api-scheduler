cmake_minimum_required(VERSION 3.9.0)

project(scheduler)

add_subdirectory(../src scheduler)

set(CAP_PATH "cap")
set(CAPGEN_COMMAND "$ENV{ETK_ROOT_PATH}/cap_gen.sh")
add_custom_target(
    stage_cap
    COMMENT "Staging CAP..."
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
    VERBATIM
    COMMAND ${CMAKE_COMMAND} -E copy scheduler/scheduler ${CAP_PATH}/bin/scheduler
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/start ${CAP_PATH}/start
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/config.json ${CAP_PATH}/config.json
)

add_custom_target(
    generate_cap
    COMMENT "Generating CAP..."
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
    VERBATIM
    COMMAND ${CAPGEN_COMMAND} -d ${CMAKE_SOURCE_DIR}/cap_description.in -o ${PROJECT_NAME}.upgx
)

add_dependencies(stage_cap scheduler)
add_dependencies(generate_cap stage_cap)
