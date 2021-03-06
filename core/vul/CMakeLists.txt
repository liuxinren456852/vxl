# core/vul/CMakeLists.txt

doxygen_add_library(core/vul
  DEPENDS core/vsl
  PACKAGE core
  DESCRIPTION "Utility Library"
  )


set(vul_sources
  vul_export.h
  vul_fwd.h
  vul_whereami.h

  vul_arg.h                   vul_arg.cxx
  vul_awk.h                   vul_awk.cxx
  vul_checksum.h
  vul_debug.h                 vul_debug.cxx
  vul_expand_path.h           vul_expand_path.cxx
  vul_file.h                  vul_file.cxx
  vul_file_iterator.h         vul_file_iterator.cxx
  vul_get_timestamp.h         vul_get_timestamp.cxx
  vul_ios_state.h
  vul_printf.h                vul_printf.cxx
  vul_psfile.h                vul_psfile.cxx
  vul_redirector.h            vul_redirector.cxx
  vul_reg_exp.h               vul_reg_exp.cxx
  vul_sequence_filename_map.h vul_sequence_filename_map.cxx
  vul_sprintf.h               vul_sprintf.cxx
  vul_string.h                vul_string.cxx
  vul_temp_filename.h         vul_temp_filename.cxx
  vul_timer.h                 vul_timer.cxx
  vul_timestamp.h             vul_timestamp.cxx
  vul_trace.h                 vul_trace.cxx
  vul_user_info.h             vul_user_info.cxx
)

# Some versions of Solaris (at least 5.8) has a brain-dead mechanism
# for implementing DNS services, where the user of a library that uses
# gethostbyname should link to -lnsl *before* linking to the
# library. This creates a kind of "pre-dependency" that the CMake
# dependency analysis is not equipped to handle. We cope by isolating
# the offending code into its own library vul_network (under Solaris
# only, of course). We can then control the dependencies of vul to
# link nsl before this vul_network.
#
# This workaround also occurs in vil
#
set( vul_network_sources
  vul_url.h                   vul_url.cxx
)


if(CMAKE_COMPILER_IS_GNUCXX)
  set_source_files_properties(vul_sequence_filename_map.cxx PROPERTIES COMPILE_FLAGS -O0)
endif()

if(APPLE)
  vxl_add_library(LIBRARY_NAME ${VXL_LIB_PREFIX}vul LIBRARY_SOURCES ${vul_sources})
else()

if(NOT SOLARIS)
  vxl_add_library(LIBRARY_NAME ${VXL_LIB_PREFIX}vul LIBRARY_SOURCES ${vul_sources} ${vul_network_sources})
else()
  vxl_add_library(LIBRARY_NAME ${VXL_LIB_PREFIX}vul LIBRARY_SOURCES ${vul_sources})
  vxl_add_library(LIBRARY_NAME ${VXL_LIB_PREFIX}vul_network LIBRARY_SOURCES ${vul_network_sources})
endif()

if(NOT UNIX)
  target_link_libraries( ${VXL_LIB_PREFIX}vul ws2_32 )
endif()

if(SOLARIS)
  target_link_libraries( ${VXL_LIB_PREFIX}vul nsl ${VXL_LIB_PREFIX}vul_network socket )
endif()

endif()

target_link_libraries( ${VXL_LIB_PREFIX}vul ${VXL_LIB_PREFIX}vcl )

if( BUILD_EXAMPLES )
  add_subdirectory(examples)
endif()

if( BUILD_TESTING )
  add_subdirectory(tests)
endif()
