# Install script for directory: /home/user/Dev/FTEDev/Games/SchizoMania-FTE/bin

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
    set(CMAKE_INSTALL_CONFIG_NAME "")
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

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/local/lib/fteplug_bullet.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/fteplug_bullet.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/lib/fteplug_bullet.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/lib/fteplug_bullet.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/lib" TYPE MODULE FILES "/home/user/Dev/FTEDev/Games/SchizoMania-FTE/bin/fteplug_bullet.so")
  if(EXISTS "$ENV{DESTDIR}/usr/local/lib/fteplug_bullet.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/fteplug_bullet.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}/usr/local/lib/fteplug_bullet.so"
         OLD_RPATH "/usr/local/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/lib/fteplug_bullet.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/localgames/fteqw" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/localgames/fteqw")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/localgames/fteqw"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/localgames/fteqw")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/localgames" TYPE EXECUTABLE FILES "/home/user/Dev/FTEDev/Games/SchizoMania-FTE/bin/fteqw")
  if(EXISTS "$ENV{DESTDIR}/usr/localgames/fteqw" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/localgames/fteqw")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/localgames/fteqw")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/localgames/fteqw-sv" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/localgames/fteqw-sv")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/localgames/fteqw-sv"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/localgames/fteqw-sv")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/localgames" TYPE EXECUTABLE FILES "/home/user/Dev/FTEDev/Games/SchizoMania-FTE/bin/fteqw-sv")
  if(EXISTS "$ENV{DESTDIR}/usr/localgames/fteqw-sv" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/localgames/fteqw-sv")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/localgames/fteqw-sv")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/localgames/iqmtool" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/localgames/iqmtool")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/localgames/iqmtool"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/localgames/iqmtool")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/localgames" TYPE EXECUTABLE FILES "/home/user/Dev/FTEDev/Games/SchizoMania-FTE/bin/iqmtool")
  if(EXISTS "$ENV{DESTDIR}/usr/localgames/iqmtool" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/localgames/iqmtool")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/localgames/iqmtool")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/localgames/imgtool" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/localgames/imgtool")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/localgames/imgtool"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/localgames/imgtool")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/localgames" TYPE EXECUTABLE FILES "/home/user/Dev/FTEDev/Games/SchizoMania-FTE/bin/imgtool")
  if(EXISTS "$ENV{DESTDIR}/usr/localgames/imgtool" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/localgames/imgtool")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/localgames/imgtool")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/localgames/qtv" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/localgames/qtv")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/localgames/qtv"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/localgames/qtv")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/localgames" TYPE EXECUTABLE FILES "/home/user/Dev/FTEDev/Games/SchizoMania-FTE/bin/qtv")
  if(EXISTS "$ENV{DESTDIR}/usr/localgames/qtv" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/localgames/qtv")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/localgames/qtv")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/localgames/ftemaster" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/localgames/ftemaster")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/localgames/ftemaster"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/localgames/ftemaster")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/localgames" TYPE EXECUTABLE FILES "/home/user/Dev/FTEDev/Games/SchizoMania-FTE/bin/ftemaster")
  if(EXISTS "$ENV{DESTDIR}/usr/localgames/ftemaster" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/localgames/ftemaster")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/localgames/ftemaster")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/localgames/fteqcc" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/localgames/fteqcc")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/localgames/fteqcc"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/localgames/fteqcc")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/localgames" TYPE EXECUTABLE FILES "/home/user/Dev/FTEDev/Games/SchizoMania-FTE/bin/fteqcc")
  if(EXISTS "$ENV{DESTDIR}/usr/localgames/fteqcc" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/localgames/fteqcc")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/localgames/fteqcc")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/localgames/fteqccgui" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/localgames/fteqccgui")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/localgames/fteqccgui"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/localgames/fteqccgui")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/localgames" TYPE EXECUTABLE FILES "/home/user/Dev/FTEDev/Games/SchizoMania-FTE/bin/fteqccgui")
  if(EXISTS "$ENV{DESTDIR}/usr/localgames/fteqccgui" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/localgames/fteqccgui")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/localgames/fteqccgui")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/local/lib/fteplug_qi.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/fteplug_qi.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/lib/fteplug_qi.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/lib/fteplug_qi.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/lib" TYPE MODULE FILES "/home/user/Dev/FTEDev/Games/SchizoMania-FTE/bin/fteplug_qi.so")
  if(EXISTS "$ENV{DESTDIR}/usr/local/lib/fteplug_qi.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/fteplug_qi.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/lib/fteplug_qi.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/local/lib/fteplug_ode.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/fteplug_ode.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/lib/fteplug_ode.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/lib/fteplug_ode.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/lib" TYPE MODULE FILES "/home/user/Dev/FTEDev/Games/SchizoMania-FTE/bin/fteplug_ode.so")
  if(EXISTS "$ENV{DESTDIR}/usr/local/lib/fteplug_ode.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/fteplug_ode.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}/usr/local/lib/fteplug_ode.so"
         OLD_RPATH "/usr/local/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/lib/fteplug_ode.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/local/lib/fteplug_ezhud.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/fteplug_ezhud.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/lib/fteplug_ezhud.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/lib/fteplug_ezhud.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/lib" TYPE MODULE FILES "/home/user/Dev/FTEDev/Games/SchizoMania-FTE/bin/fteplug_ezhud.so")
  if(EXISTS "$ENV{DESTDIR}/usr/local/lib/fteplug_ezhud.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/fteplug_ezhud.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/lib/fteplug_ezhud.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/local/lib/fteplug_namemaker.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/fteplug_namemaker.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/lib/fteplug_namemaker.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/lib/fteplug_namemaker.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/lib" TYPE MODULE FILES "/home/user/Dev/FTEDev/Games/SchizoMania-FTE/bin/fteplug_namemaker.so")
  if(EXISTS "$ENV{DESTDIR}/usr/local/lib/fteplug_namemaker.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/fteplug_namemaker.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/lib/fteplug_namemaker.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/local/lib/fteplug_terrorgen.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/fteplug_terrorgen.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/lib/fteplug_terrorgen.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/lib/fteplug_terrorgen.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/lib" TYPE MODULE FILES "/home/user/Dev/FTEDev/Games/SchizoMania-FTE/bin/fteplug_terrorgen.so")
  if(EXISTS "$ENV{DESTDIR}/usr/local/lib/fteplug_terrorgen.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/fteplug_terrorgen.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/lib/fteplug_terrorgen.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/local/lib/fteplug_irc.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/fteplug_irc.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/lib/fteplug_irc.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/lib/fteplug_irc.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/lib" TYPE MODULE FILES "/home/user/Dev/FTEDev/Games/SchizoMania-FTE/bin/fteplug_irc.so")
  if(EXISTS "$ENV{DESTDIR}/usr/local/lib/fteplug_irc.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/fteplug_irc.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/lib/fteplug_irc.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/local/lib/fteplug_models.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/fteplug_models.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/lib/fteplug_models.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/lib/fteplug_models.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/lib" TYPE MODULE FILES "/home/user/Dev/FTEDev/Games/SchizoMania-FTE/bin/fteplug_models.so")
  if(EXISTS "$ENV{DESTDIR}/usr/local/lib/fteplug_models.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/fteplug_models.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/lib/fteplug_models.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/local/lib/fteplug_xmpp.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/fteplug_xmpp.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/lib/fteplug_xmpp.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/lib/fteplug_xmpp.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/lib" TYPE MODULE FILES "/home/user/Dev/FTEDev/Games/SchizoMania-FTE/bin/fteplug_xmpp.so")
  if(EXISTS "$ENV{DESTDIR}/usr/local/lib/fteplug_xmpp.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/fteplug_xmpp.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/lib/fteplug_xmpp.so")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/user/Dev/FTEDev/Games/SchizoMania-FTE/bin/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
