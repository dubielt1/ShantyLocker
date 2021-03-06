IF(NOT WIN32)
    IF(LIBXCB-EWMH_INCLUDE_DIR AND LIBXCB-EWMH_LIBRARIES)

        SET(XCB-EWMH_FIND_QUIETLY TRUE)

    ENDIF(LIBXCB-EWMH_INCLUDE_DIR AND LIBXCB-EWMH_LIBRARIES)

    FIND_PACKAGE(PkgConfig)
    PKG_CHECK_MODULES(PKG_XCB-EWMH xcb-ewmh)

    SET(LIBXCB-EWMH_DEFINITIONS ${PKG_XCB-EWMH_CFLAGS})

    FIND_PATH(LIBXCB-EWMH_INCLUDE_DIRS xcb/xcb_ewmh.h ${PKG_XCB-EWMH_INCLUDE_DIRS})
    FIND_LIBRARY(LIBXCB-EWMH_LIBRARIES NAMES xcb-ewmh PATHS ${PKG_XCB-EWMH_LIBRARY_DIRS})

    INCLUDE(FindPackageHandleStandardArgs)
    FIND_PACKAGE_HANDLE_STANDARD_ARGS(XCB-EWMH DEFAULT_MSG LIBXCB-EWMH_LIBRARIES LIBXCB-EWMH_INCLUDE_DIRS)

    MARK_AS_ADVANCED(LIBXCB-EWMH_INCLUDE_DIRS LIBXCB-EWMH_LIBRARIES XCB-EWMHPROC_EXECUTABLE)
ENDIF(NOT WIN32)