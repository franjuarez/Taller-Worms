#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "box2d::box2d" for configuration ""
set_property(TARGET box2d::box2d APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(box2d::box2d PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libbox2d.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS box2d::box2d )
list(APPEND _IMPORT_CHECK_FILES_FOR_box2d::box2d "${_IMPORT_PREFIX}/lib/libbox2d.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
