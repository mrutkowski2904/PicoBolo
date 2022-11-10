add_executable(robot-fw main.c core1.c)

pico_set_program_name(robot-fw "robot-fw")
pico_set_program_version(robot-fw "0.1")

pico_enable_stdio_uart(robot-fw 1)
pico_enable_stdio_usb(robot-fw 0)

add_subdirectory(network)

# Add the standard library to the build
target_link_libraries(robot-fw
        pico_stdlib
        pico_multicore)

# Add the standard include files to the build
target_include_directories(robot-fw PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/..
)

# Add any user requested libraries
target_link_libraries(robot-fw
        pico_cyw43_arch_lwip_poll
        network
        )

pico_add_extra_outputs(robot-fw)
