add_library(network network.c)

target_sources(network INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/network.c
        )

target_include_directories(network PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/.. # for configs
        )

target_link_libraries(network
        pico_stdlib
        pico_cyw43_arch_lwip_poll
        )