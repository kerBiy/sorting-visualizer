# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/sorting_visualiser_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/sorting_visualiser_autogen.dir/ParseCache.txt"
  "sorting_visualiser_autogen"
  )
endif()
