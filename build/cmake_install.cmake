# Install script for directory: /users/ilc/okugawa/QQbarAnalysis

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/users/ilc/okugawa/QQbarAnalysis")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
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
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libQQbarProcessor.so.0.1.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libQQbarProcessor.so.0.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libQQbarProcessor.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "/users/ilc/okugawa/QQbarAnalysis/lib:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-11/Marlin/v01-09/lib:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-11/lcio/v02-07-03/lib:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-11/gear/v01-06-01/lib:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-11/CLHEP/2.1.4.1/lib:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/ilcutil/v01-03/lib:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-11/root/5.34.30/lib")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE FILES
    "/users/ilc/okugawa/QQbarAnalysis/build/lib/libQQbarProcessor.so.0.1.0"
    "/users/ilc/okugawa/QQbarAnalysis/build/lib/libQQbarProcessor.so.0.1"
    "/users/ilc/okugawa/QQbarAnalysis/build/lib/libQQbarProcessor.so"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libQQbarProcessor.so.0.1.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libQQbarProcessor.so.0.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libQQbarProcessor.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHANGE
           FILE "${file}"
           OLD_RPATH "/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-11/Marlin/v01-09/lib:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-11/lcio/v02-07-03/lib:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-11/gear/v01-06-01/lib:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-11/CLHEP/2.1.4.1/lib:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/ilcutil/v01-03/lib:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-11/root/5.34.30/lib:::::::::::::::::::::::::::::::::::::"
           NEW_RPATH "/users/ilc/okugawa/QQbarAnalysis/lib:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-11/Marlin/v01-09/lib:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-11/lcio/v02-07-03/lib:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-11/gear/v01-06-01/lib:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-11/CLHEP/2.1.4.1/lib:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/ilcutil/v01-03/lib:/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/v01-17-11/root/5.34.30/lib")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/users/ilc/okugawa/QQbarAnalysis/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
