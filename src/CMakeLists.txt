cmake_minimum_required (VERSION 3.9.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(LINK_FLAGS
    -Wl,-z,relro
    -Wl,-z,now
    -Wl,--hash-style=gnu
    -Wl,--no-copy-dt-needed-entries)

set(CXX_FLAGS
    -fstrict-aliasing
    -fstrict-overflow
    -fstack-protector-strong)

set(CXX_WARNINGS
    -Wall
    -Wextra
    -Wformat=2
    -Wstrict-overflow=5
    -Wcast-align
    -Wcast-qual
    -Wpointer-arith
    -Wshadow
    -Wunreachable-code
    -Wredundant-decls
    -Wunused
    -Wlogical-op
    -Wno-effc++
    -Wno-psabi
)

find_package(Threads REQUIRED)
find_package(CURL REQUIRED)
find_package(LTTngUST)

option(USE_TRACE "Enable tracepoints with LTTng" ${LTTNGUST_FOUND})

set(SOURCE_MODULES main api_client config)

foreach(_MODULE IN LISTS SOURCE_MODULES)
    set(MOD_NAME "${_MODULE}")

    list(APPEND SOURCE_CODE ${MOD_NAME})
endforeach()

foreach(_SOURCE_FILE IN LISTS SOURCE_CODE)
    list(APPEND SOURCES "${_SOURCE_FILE}.cpp")
endforeach()

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE src ${CMAKE_CURRENT_BINARY_DIR}/src)
target_compile_options(${PROJECT_NAME} PRIVATE ${CXX_FLAGS} ${CXX_WARNINGS})

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    stdc++fs
    curl
    ${PLATFORM_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT})

# Add standard linker options.
target_link_libraries(${PROJECT_NAME} PRIVATE ${LINK_FLAGS})

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")

if (USE_TRACE)
   target_link_libraries(${PROJECT_NAME} PRIVATE LTTng::UST urcu-bp urcu-cds z)
else()
   message(STATUS "Disabled LTTng-UST tracepoint generation")
   target_compile_definitions(${PROJECT_NAME} PRIVATE DISABLE_TRACEPOINTS)
endif()
