IF(NOT WIN32)
    IF(LIBXCB-UTIL_INCLUDE_DIR AND LIBXCB-UTIL_LIBRARIES)

        SET(XCB-UTIL_FIND_QUIETLY TRUE)

    ENDIF(LIBXCB-UTIL_INCLUDE_DIR AND LIBXCB-UTIL_LIBRARIES)

    FIND_PACKAGE(PkgConfig)
    PKG_CHECK_MODULES(PKG_XCB-UTIL xcb-util)

    SET(LIBXCB-UTIL_DEFINITIONS ${PKG_XCB-UTIL_CFLAGS})

    FIND_PATH(LIBXCB-UTIL_INCLUDE_DIRS xcb/xcb_util.h ${PKG_XCB-UTIL_INCLUDE_DIRS})
    FIND_LIBRARY(LIBXCB-UTIL_LIBRARIES NAMES xcb-util PATHS ${PKG_XCB-UTIL_LIBRARY_DIRS})

    INCLUDE(FindPackageHandleStandardArgs)
    FIND_PACKAGE_HANDLE_STANDARD_ARGS(XCB-UTIL DEFAULT_MSG LIBXCB-UTIL_LIBRARIES LIBXCB-UTIL_INCLUDE_DIRS)

    MARK_AS_ADVANCED(LIBXCB-UTIL_INCLUDE_DIRS LIBXCB-UTIL_LIBRARIES XCB-UTILPROC_EXECUTABLE)
ENDIF(NOT WIN32)