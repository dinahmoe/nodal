# Main CMakeLists for the nodal library
# Copyright 2012-2015 Dinahmoe
# See COPYING and LICENSE

CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

PROJECT("Nodal")

IF (NOT DEFINED DM_ROOT)
  SET(DM_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
ENDIF (NOT DEFINED DM_ROOT)

SET(CMAKE_MODULE_PATH ${DM_ROOT}/dm-cmake)

INCLUDE(SetTargetOptions)
INCLUDE(SetPlatformDefines)
INCLUDE(MergeStaticLibraries)
SET_PLATFORM_DEFINES()

ADD_SUBDIRECTORY(${DM_ROOT}/dm-audioengine "dm-audioengine")
ADD_SUBDIRECTORY(${DM_ROOT}/dm-audiomidi "dm-audiomidi")
ADD_SUBDIRECTORY(${DM_ROOT}/dm-dsp "dm-dsp")
ADD_SUBDIRECTORY(${DM_ROOT}/dm-log "dm-log")
ADD_SUBDIRECTORY(${DM_ROOT}/dm-utils "dm-utils")

SET(EXTRA_LIBRARIES "")

IF (DEFINED NODAL_USE_CONVOLVER)
  ADD_SUBDIRECTORY(${DM_ROOT}/dinahconv/library "dinahconv")
  SET(EXTRA_LIBRARIES "${EXTRA_LIBRARIES} dinahconv")
ENDIF (DEFINED NODAL_USE_CONVOLVER)

MERGE_STATIC_LIBS(nodal dm-utils dm-audioengine dm-dsp dm-log ${EXTRA_LIBRARIES})
