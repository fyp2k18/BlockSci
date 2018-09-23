cmake_minimum_required(VERSION 3.5)
project(blocksci_taint)

find_package( Boost 1.58 COMPONENTS filesystem REQUIRED )

add_executable(blocksci_taint main.cpp)

target_compile_options(blocksci_taint PRIVATE -Wall -Wextra -Wpedantic)

if(CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(blocksci_taint PRIVATE -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-old-style-cast -Wno-documentation-unknown-command -Wno-documentation -Wno-shadow -Wno-covered-switch-default -Wno-missing-prototypes -Wno-weak-vtables -Wno-unused-macros -Wno-padded)
endif()

target_link_libraries( blocksci_taint blocksci)
#target_link_libraries( mempool_recorder bitcoinapi_static)
#target_link_libraries( mempool_recorder clipp)
#target_link_libraries( mempool_recorder Boost::filesystem)

install(TARGETS blocksci_taint DESTINATION bin)
