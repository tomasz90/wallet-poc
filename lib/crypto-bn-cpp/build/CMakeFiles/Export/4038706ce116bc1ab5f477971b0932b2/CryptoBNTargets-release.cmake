#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "CryptoBN" for configuration "Release"
set_property(TARGET CryptoBN APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(CryptoBN PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libCryptoBN.dylib"
  IMPORTED_SONAME_RELEASE "@rpath/libCryptoBN.dylib"
  )

list(APPEND _cmake_import_check_targets CryptoBN )
list(APPEND _cmake_import_check_files_for_CryptoBN "${_IMPORT_PREFIX}/lib/libCryptoBN.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
