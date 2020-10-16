cmake_minimum_required(VERSION 3.10)

# set the project name
project(warmer)

# add the executable
add_executable(warm_ccache warm_ccache.c warm_ccache.service warm_ccache.timer)

install(TARGETS warm_ccache DESTINATION /usr/local/bin COMPONENT binary)
install(FILES warm_ccache.service warm_ccache.timer DESTINATION /etc/systemd/user COMPONENT config)
