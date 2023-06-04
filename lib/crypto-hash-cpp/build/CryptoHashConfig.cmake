include(CMakeFindDependencyMacro)

include("${CMAKE_CURRENT_LIST_DIR}/CryptoHashTargets.cmake")

get_filename_component(CMAKE_CURRENT_LIST_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
get_filename_component(_INSTALL_PREFIX "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)


####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was CryptoHashConfig.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################
set_and_check(CryptoHash_INCLUDE_DIR  "${_INSTALL_PREFIX}/include/safeheron")
set_and_check(CryptoHash_INCLUDE_DIRS "${_INSTALL_PREFIX}/include/safeheron")
set_and_check(CryptoHash_LIBRARY_DIR "${_INSTALL_PREFIX}/lib")

MESSAGE(STATUS "###################################")
MESSAGE(STATUS "operation system is ${CMAKE_SYSTEM}")

IF (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    MESSAGE(STATUS "current platform: Darwin ")
    set_and_check(CryptoHash_LIBRARY "${_INSTALL_PREFIX}/lib/libCryptoHash.dylib")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    MESSAGE(STATUS "current platform: Windows")
    set_and_check(CryptoHash_LIBRARY "${_INSTALL_PREFIX}/lib/libCryptoHash.dll")
ELSE ()
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
    set_and_check(CryptoHash_LIBRARY "${_INSTALL_PREFIX}/lib/libCryptoHash.so")
ENDIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")

MESSAGE(STATUS "###################################")
