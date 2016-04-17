add_executable(control_node main.cpp control.cpp control.h)

target_link_libraries(control_node
    ${catkin_LIBRARIES}
)
