# Install script for directory: /home/infloop/Documents/LogicToolbox/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "shlib")
  if(EXISTS "$ENV{DESTDIR}/usr/local/lib/liblogictoolbox.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/liblogictoolbox.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/lib/liblogictoolbox.so"
         RPATH "/usr/local/lib")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/lib/liblogictoolbox.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/lib" TYPE SHARED_LIBRARY FILES "/home/infloop/Documents/LogicToolbox/lib/liblogictoolbox.so")
  if(EXISTS "$ENV{DESTDIR}/usr/local/lib/liblogictoolbox.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/liblogictoolbox.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}/usr/local/lib/liblogictoolbox.so"
         OLD_RPATH "::::::::::::::"
         NEW_RPATH "/usr/local/lib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/lib/liblogictoolbox.so")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/include/logictoolbox/Variable.h;/usr/local/include/logictoolbox/Token.h;/usr/local/include/logictoolbox/Graph.h;/usr/local/include/logictoolbox/World.h;/usr/local/include/logictoolbox/Expression.h;/usr/local/include/logictoolbox/CoreEvaluator.h;/usr/local/include/logictoolbox/ResultTree.h;/usr/local/include/logictoolbox/Universe.h;/usr/local/include/logictoolbox/Operators.h;/usr/local/include/logictoolbox/version.h;/usr/local/include/logictoolbox/Net.h;/usr/local/include/logictoolbox/Neuron.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/include/logictoolbox" TYPE FILE FILES
    "/home/infloop/Documents/LogicToolbox/include/Variable.h"
    "/home/infloop/Documents/LogicToolbox/include/Token.h"
    "/home/infloop/Documents/LogicToolbox/include/Graph.h"
    "/home/infloop/Documents/LogicToolbox/include/World.h"
    "/home/infloop/Documents/LogicToolbox/include/Expression.h"
    "/home/infloop/Documents/LogicToolbox/include/CoreEvaluator.h"
    "/home/infloop/Documents/LogicToolbox/include/ResultTree.h"
    "/home/infloop/Documents/LogicToolbox/include/Universe.h"
    "/home/infloop/Documents/LogicToolbox/include/Operators.h"
    "/home/infloop/Documents/LogicToolbox/src/version.h"
    "/home/infloop/Documents/LogicToolbox/src/Net.h"
    "/home/infloop/Documents/LogicToolbox/src/Neuron.h"
    )
endif()

