cmake_minimum_required(VERSION 3.10)

# set the project name
project(kw-ccache)

install(
  FILES kw-ccache
  PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE
  GROUP_WRITE GROUP_READ WORLD_EXECUTE WORLD_WRITE WORLD_READ
  DESTINATION /usr/local/bin
  )

install(FILES kw-ccache.conf.example TYPE SYSCONF)
