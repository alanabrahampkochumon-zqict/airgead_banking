cmake_minimum_required(VERSION 3.25)

project(AirgeadBanking)

set(HeaderDirectory "include/")
set(HeaderFiles "Account.h")
list(TRANSFORM HeaderFiles PREPEND ${HeaderDirectory})

set(SourceDirectory "src/")
set(SourceFiles "Main.cpp;Account.cpp")
list(TRANSFORM SourceFiles PREPEND ${SourceDirectory})

add_executable(AirgeadBanking)

target_sources(
    AirgeadBanking
    PUBLIC
    FILE_SET HEADERS
    BASE_DIRS ${HeaderDirectory}
    FILES ${HeaderFiles}

    PRIVATE
    ${SourceFiles}
)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT AirgeadBanking)