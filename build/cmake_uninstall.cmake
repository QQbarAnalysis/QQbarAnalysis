##########################################
# create an uninstall target for cmake
# http://www.cmake.org/Wiki/CMake_FAQ
##########################################

IF(NOT EXISTS "/users/ilc/okugawa/QQbarAnalysis/build/install_manifest.txt")
  MESSAGE(FATAL_ERROR "Cannot find install manifest: \"/users/ilc/okugawa/QQbarAnalysis/build/install_manifest.txt\"")
ENDIF(NOT EXISTS "/users/ilc/okugawa/QQbarAnalysis/build/install_manifest.txt")

FILE(READ "/users/ilc/okugawa/QQbarAnalysis/build/install_manifest.txt" files)
STRING(REGEX REPLACE "\n" ";" files "${files}")
FOREACH(file ${files})
  MESSAGE(STATUS "Uninstalling \"$ENV{DESTDIR}${file}\"")
  IF(EXISTS "$ENV{DESTDIR}${file}")
    EXEC_PROGRAM(
      "/afs/desy.de/project/ilcsoft/sw/x86_64_gcc44_sl6/CMake/3.4.3/bin/cmake" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
      OUTPUT_VARIABLE rm_out
      RETURN_VALUE rm_retval
      )
    IF("${rm_retval}" STREQUAL 0)
    ELSE("${rm_retval}" STREQUAL 0)
      MESSAGE(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
    ENDIF("${rm_retval}" STREQUAL 0)
  ELSE(EXISTS "$ENV{DESTDIR}${file}")
    MESSAGE(STATUS "File \"$ENV{DESTDIR}${file}\" does not exist.")
  ENDIF(EXISTS "$ENV{DESTDIR}${file}")
ENDFOREACH(file)
