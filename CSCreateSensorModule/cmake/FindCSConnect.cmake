# - Try to find RUR module library
# Once done, this will define
#
#  CSCONNECT_FOUND - system has RUR module library
#  CSCONNECT_INCLUDE_DIRS - the RUR module include directories
#  CSCONNECT_LIBRARIES - link these to use the RUR module 

include(LibFindMacros)

# Include dir
find_path(CSCONNECT_INCLUDE_DIR
  NAMES csconnect/CSConnect.h
  PATHS ${CSCONNECT_PKGCONF_INCLUDE_DIRS}
)

# Finally the library itself
find_library(CSCONNECT_LIBRARY
  NAMES csconnect
  PATHS ${CSCONNECT_PKGCONF_LIBRARY_DIRS}
)

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this lib depends on.
set(CSCONNECT_PROCESS_INCLUDES CSCONNECT_INCLUDE_DIR CSCONNECT_INCLUDE_DIRS)
set(CSCONNECT_PROCESS_LIBS CSCONNECT_LIBRARY CSCONNECT_LIBRARIES)
libfind_process(CSCONNECT)

