CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
 
PROJECT(YAP C CXX)

SET(YAP_VERSION 6.3.2)
SET(MYDDAS_VERSION MYDDAS-0.9.1)

MESSAGE(STATUS "Building YAP version ${YAP_VERSION}")

# set path to additional CMake modules
SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

# Compatibility vars with autotols
set (prefix "${CMAKE_INSTALL_PREFIX}")
set (exec_prefix "${prefix}")
set (libdir "${exec_prefix}/lib")
set (includedir "${prefix}/include")
set (datarootdir "${prefix}/share")
set (datadir "${datarootdir}")
set (mandir "${datarootdir}/man")
set (bindir "${exec_prefix}/man")

#
# YAP PATHS
#
# some coments about the autotools transition
# rootdir -> C_MAKE_INSTALL_PREFIX (or in autotools prefix)
# erootdir -> rootdir
# bindir defined above
# libdir defined above
set(YAPLIBDIR "${libdir}/Yap")



# where to find source files, 
# this is inherited in sub folders
#include build directory
INCLUDE_DIRECTORIES (${CMAKE_BINARY_DIR})
#default headers directories
INCLUDE_DIRECTORIES(H include os)

# Compilation Flags
IF (CMAKE_COMPILER_IS_GNUCC)
  MESSAGE(STATUS "Original CMAKE_C_FLAGS ${CMAKE_C_FLAGS}")
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wstrict-prototypes -Wmissing-prototypes")
  MESSAGE(STATUS "Running with CMAKE_C_FLAGS ${CMAKE_C_FLAGS}")
  MESSAGE(STATUS "Original CMAKE_C_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG}")
  SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -O -g")
  MESSAGE(STATUS "Runing with CMAKE_C_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG}")
  MESSAGE(STATUS "Original CMAKE_C_FLAGS_RELEASE ${CMAKE_C_FLAGS_RELEASE}")
  SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} -O3 -fomit-frame-pointer")
  MESSAGE(STATUS "Running with CMAKE_C_FLAGS_RELEASE ${CMAKE_C_FLAGS_RELEASE}")
ENDIF()

ADD_DEFINITIONS(-D_YAP_NOT_INSTALLED_=1 -DCUT_C=1 -DHAVE_CONFIG_H)

SET(YAPLIB libYap.a)
SET(YAPSTARTUP startup.yss)

#
# Optional libraries that affect compilation
#
include (MacroOptionalFindPackage)
include (MacroLogFeature)

macro_optional_find_package (GMP ON)
macro_log_feature (GMP_FOUND "libgmp" 
  "GNU Multiple Precision" 
  "http://gmplib.org")
if (GMP_FOUND)
  include_directories (${GMP_INCLUDE_DIR})
  set (EXTRALIBS ${EXTRALIBS} ${GMP_LIBRARIES})
  #config.h needs this (TODO: change in code latter)
  set (USE_GMP 1)
endif (GMP_FOUND)

macro_optional_find_package (READLINE ON)
macro_log_feature (READLINE_FOUND "libreadline" 
  "GNU Readline Library (or simmilar)" 
  "http://www.gnu.org/software/readline")
if (READLINE_FOUND)
  include_directories (${READLINE_INCLUDE_DIR})
  set (EXTRALIBS ${EXTRALIBS} ${READLINE_LIBRARIES})
  #config.h needs this
  set (HAVE_LIBREADLINE 1)
  set (HAVE_READLINE_READLINE_H TRUE)
  set (HAVE_READLINE_HISTORY_H ${READLINE_HAVE_READLINE_HISTORY_H})
endif (READLINE_FOUND)

set (CURSES_NEED_NCURSES TRUE)
macro_optional_find_package (CURSES ON)
macro_log_feature (CURSES_FOUND "libncurses" 
  "NCurses Library" 
  "")
if (CURSES_FOUND)
  include_directories (${CURSES_INCLUDE_DIR})
  set (EXTRALIBS ${EXTRALIBS} ${CURSES_NCURSES_LIBRARY})
endif (CURSES_FOUND)

#TODO: change macro_log_feature to check both WITH_{$name} and ${name}_FOUND
#TODO: improve FindGecode.cmake to be similar to other Find*.cmake
#CHECK: GECODE
macro_optional_find_package (GECODE OFF)
macro_log_feature (GECODE_FOUND "libgecode" 
  "Use Generic Constraint Development Environment (GECODE) library" 
  "http://www.gecode.org" FALSE)
if (GECODE_FOUND)
  #DEFINES:
  #   GECODE_INLUDE_DIR
  #   GECODE_VERSION
  #   GECODE_LIBRARIES

  #add_subdirectory (library/gecode)
  #set (EXTRALIBS gecode)

  #include_directories (${GECODE_INCLUDE_DIR})
  #set (EXTRALIBS ${EXTRALIBS} ${GECODE_LIBRARIES})
endif (GECODE_FOUND)

#
# Optional Components
#

# option (WITH_RATIONAL_TREES "support infinite rational trees" ON) 
add_definitions (-DRATIONAL_TREES=1)

# option (WITH_COROUTINING 
#   "support co-routining, attributed variables and constraints" ON)
add_definitions (-DCOROUTINING=1)
# if (WITH_RATIONAL_TREES and WITH_COROUTINING)
#TODO: install (cd LGPL/clp ; $(MAKE) install)
# endif (WITH_RATIONAL_TREES and WITH_COROUTINING)

# option (WITH_DEPTH_LIMIT
#   "support depth-bound computation" ON)
add_definitions (-DDEPTH_LIMIT=1)

option (WITH_TABLING "Support tabling" ON)
if (WITH_TABLING) 
  #this depends on DEPTH_LIMIT define it after

  #this macro should realy be in config.h or other like it
  #and it is used across several files outside OPTYap
  add_definitions (-DTABLING=1)
  include_directories (OPTYap)
  add_subdirectory (OPTYap)
  set (EXTRALIBS ${EXTRALIBS} optyap)
endif(WITH_TABLING)

option (WITH_EAM "enable EAM (Extended Andorra Model)" OFF)
if (WITH_EAM)
  #this macro should realy be in config.h or other like it
  add_definitions (-DBEAM=1)
  include_directories (BEAM)
  add_subdirectory (BEAM)
  set (EXTRALIBS ${EXTRALIBS} beam)
endif (WITH_EAM)

#TODO: option (or-parallelism)


# option (WITH_WAM_Profile
#   "support low level profiling of abstract machine" OFF)

option (WITH_Low_Level_Tracer
  "support for procedure-call tracing" OFF)
#TODO:

option (System_Threads
  "support system threads" OFF)
#TODO:

option (WITH_Dynamic_BDD
  "dynamic bdd library" OFF)
#TODO:

include (CMakeDependentOption)
cmake_dependent_option (WITH_PThreadLocking
  "use pthread locking primitives for internal locking" OFF
  System_Threads OFF)
#TODO:

#todo: use cmake target builds
# option (MAXPERFORMANCE
#   "try using the best flags for specific architecture" OFF)

# option (MAXMEMORY
#   "try using the best flags for using the memory to the most" ON)
#TODO: check MAXMEMORY

#TODO: use cmake target builds
# option (DEBUGYAP
#   "enable C-debugging for YAP" OFF)

#TODO: use cmake arch/compiler
# option (CYGWIN
#   "use cygwin library in WIN32" OFF)

option (WITH_PRISM
  "use PRISM system in YAP" ON)
#TODO:

option (WITH_Dynamic_Loading
  "compile YAP as a DLL" OFF)
#TODO:

option (WITH_Static_compilation
  "compile YAP statically" OFF)
#TODO:

option (Use_MALLOC
  "use malloc to allocate memory" ON)
#TODO:

OPTION(CONDOR
  "allow YAP to be used from condor" OFF)
#TODO:

#TODO: detect arch before allow this option
# OPTION(WIN64
#   "compile YAP for win64" OFF)

# option (WITH_APRIL
#   "compile Yap to support April ILP system" OFF)
# option (DLCOMPAT
#   "use dlcompat library for dynamic loading on Mac OS X" OFF)

# find_package(R)
# if (R_FOUND)
#   MESSAGE(STATUS "RFOUND ${R_LIBRARIES} ${R_DEFINITIONS} ${R_EXECUTABLE}")
# endif (R_FOUND)
#TODO: check REAL_TARGET ENABLE_REAL

option (WITH_MYDDAS
  "enable the MYDDAS library" OFF)
if (WITH_MYDDAS)
  find_package(MYSQL)
  if (MYSQL_FOUND)
    add_definitions (-DMYDDAS_MYSQL=1)
  endif (MYSQL_FOUND)

  find_package(ODBC)
  if (ODBC_FOUND)
    add_definitions (-DMYDDAS_ODBC=1)
    set (EXTRALIBS ${EXTRALIBS} ${ODBC_LIBRARY})
    if (APPLE)
      set (EXTRALIBS ${EXTRALIBS} "-framework CoreFoundation")
    endif (APPLE)
  endif (ODBC_FOUND)

  if (MYSQL_FOUND OR ODBC_FOUND)
    include_directories (MYDDAS)
    add_subdirectory (MYDDAS)
    set (EXTRALIBS ${EXTRALIBS} myddas)
  else (MYSQL_FOUND OR ODBC_FOUND)
    MESSAGE(SEND_ERROR "MYDDAS needs either MYSQL or ODBC none where found")
  endif (MYSQL_FOUND OR ODBC_FOUND)
endif (WITH_MYDDAS)

cmake_dependent_option (WITH_MYDDAS_Stats
  "enable the MYDDAS library statistics support" OFF
  WITH_MYDDAS OFF)
#TODO:

cmake_dependent_option (WITH_MYDDAS_top_level
  "enable the MYDDAS top-level support to MySQL" OFF
  'WITH_MYDDAS AND MYSQL_FOUND' OFF)
#TODO:

#TODO: Switch to feature detection
# OPTION(CHR
#   "install chr library" ON)
# OPTION(CLPQR
#   "install clpqr library" ON)
# OPTION(CPLINT
#   "enable the cplint library using the CUDD library in DIR/lib" OFF)
# OPTION(yap_cv_clpbn_bp
#   "enable belief propagation solver in CLPBN." OFF)
# OPTION( 

# SHARED PACKAGES with SWI
# swi packages have both Makefile.in which we will use and
# Makefile.mak, we will use the later to identify this packages
# while we keep both autotools amd cmake working side by side
# Search for available packages which all have a Makefile.mak
file (GLOB PACKAGES packages/*/Makefile.mak)

# needed by this packages
configure_file(packages/Makefile.defs.cmake packages/Makefile.defs)
configure_file(packages/Dialect.defs.cmake packages/Dialect.defs)

foreach (PACKAGE ${PACKAGES})
  message ("Adding: ${PACKAGE}")
endforeach (PACKAGE)

#
# Arch checks
#
include(ConfigureChecks)

#
# Sources Section
#

SET(IOLIB_SOURCES
  os/pl-buffer.c 
  os/pl-codelist.c 
  os/pl-ctype.c 
  os/pl-dtoa.c  
  os/pl-error.c  
  os/pl-file.c 
  os/pl-files.c  
  os/pl-fmt.c  
  os/pl-glob.c  
  os/pl-option.c  
  os/pl-nt.c
  os/pl-os.c 
  os/pl-privitf.c 
  os/pl-prologflag.c 
  os/pl-read.c 
  os/pl-rl.c  
  os/pl-stream.c
  os/pl-string.c 
  os/pl-table.c 
  os/pl-tai.c  
  os/pl-text.c 
  os/pl-utf8.c
  os/pl-write.c 
  C/pl-yap.c
)
IF (WIN32)
  SET(IOLIBS_SOURCES
    ${IOLIBS_SOURCES}
    os/windows/uxnt.c
    )
ENDIF (WIN32)

SET (ENGINE_SOURCES 
  C/agc.c 
  C/absmi.c
  C/adtdefs.c 
  C/alloc.c 
  C/amasm.c
  C/analyst.c 
  C/arrays.c   
  C/arith0.c
  C/arith1.c
  C/arith2.c 
  C/attvar.c
  C/bignum.c 
  C/bb.c
  C/cdmgr.c
  C/cmppreds.c
  C/compiler.c
  C/computils.c 
  C/corout.c 
  C/cut_c.c 
  C/dbase.c
  C/dlmalloc.c 
  C/errors.c 
  C/eval.c
  C/exec.c 
  C/globals.c
  C/gmp_support.c 
  C/gprof.c
  C/grow.c 
  C/heapgc.c
  C/index.c	   
  C/init.c
  C/inlines.c	   
  C/iopreds.c
  C/depth_bound.c 
  C/mavar.c
  C/modules.c
  C/other.c       
  C/parser.c 
  C/qlyr.c 
  C/qlyw.c 
  C/save.c
  C/scanner.c 
  C/sort.c
  C/stdpreds.c
  C/sysbits.c 
  C/threads.c 
  C/tracer.c 
  C/unify.c
  C/userpreds.c  
  C/utilpreds.c
  C/yap-args.c 
  C/write.c 
  C/ypstdio.c 
  library/dialect/swi/fli/swi.c 
  library/dialect/swi/fli/blobs.c

  C/udi.c 
  packages/udi/rtree.c 
  packages/udi/rtree_udi.c 

#  ${IOLIB_SOURCES}
#  MPI_SOURCES
)

SET(LIBTAI_SOURCES
  os/libtai/tai_add.c
  os/libtai/tai_now.c
  os/libtai/tai_pack.c
  os/libtai/tai_sub.c
  os/libtai/tai_unpack.c 
  os/libtai/taia_add.c
  os/libtai/taia_approx.c
  os/libtai/taia_fmtfrac.c
  os/libtai/taia_frac.c
  os/libtai/taia_half.c
  os/libtai/taia_less.c
  os/libtai/taia_now.c
  os/libtai/taia_pack.c
  os/libtai/taia_sub.c
  os/libtai/taia_tai.c
  os/libtai/taia_unpack.c
  os/libtai/caldate_fmt.c
  os/libtai/caldate_scan.c
  os/libtai/caldate_fmjd.c
  os/libtai/caldate_mjd.c
  os/libtai/caldate_norm.c
  os/libtai/caldate_ster.c
  os/libtai/leapsecs_read.c
  os/libtai/leapsecs_init.c
  os/libtai/leapsecs_add.c
  os/libtai/leapsecs_sub.c
  os/libtai/caltime_fmt.c
  os/libtai/caltime_scan.c
  os/libtai/caltime_tai.c
  os/libtai/caltime_utc.c
)

SET(C_INTERFACE_SOURCES
  C/load_foreign.c 
  C/load_dl.c
  C/load_dld.c 
  C/load_dyld.c
  C/load_none.c 
  C/load_aout.c
  C/load_aix.c
  C/load_dll.c 
  C/load_shl.c 
  C/c_interface.c 
  C/clause_list.c 
  )
  
SET(STATIC_SOURCES
#NOT INCLUDED FOR NOW
)

SET(CONSOLE_SOURCES console/yap.c)   

#MPI STUFF
  # library/mpi/mpi.c library/mpi/mpe.c 
  # library/lammpi/yap_mpi.c library/lammpi/hash.c library/lammpi/prologterms2c.c  
  # )

#WIN STUFF
# SET(PLCONS_SOURCES
#   console/LGPL/pl-nt.c 
#   console/LGPL/pl-ntcon.c 
#   console/LGPL/pl-ntconsole.c 
#   console/LGPL/pl-ntmain.c
# )

# CONFIGURE_FILE(config.h.cmake config.h)
# CONFIGURE_FILE(YapTermConfig.h.cmake YapTermConfig.h)
CONFIGURE_FILE(build/config.h config.h)
CONFIGURE_FILE(build/YapTermConfig.h YapTermConfig.h)
CONFIGURE_FILE(parms.h.cmake parms.h)
configure_file(config.h.cmake config.h.cmake)

# ADD_SUBDIRECTORY(GPL)
# ADD_SUBDIRECTORY(LGPL)
# ADD_SUBDIRECTORY(library)
# ADD_SUBDIRECTORY(os)
# ADD_SUBDIRECTORY(packages)

ADD_LIBRARY(Yap 
  ${ENGINE_SOURCES} 
  ${IOLIB_SOURCES}
  ${C_INTERFACE_SOURCES} 
  ${STATIC_SOURCES}
  ${LIBTAI_SOURCES})

ADD_EXECUTABLE (yap-bin ${CONSOLE_SOURCES})
SET_TARGET_PROPERTIES (yap-bin PROPERTIES OUTPUT_NAME yap)

TARGET_LINK_LIBRARIES(yap-bin 
  ${EXTRALIBS} Yap resolv stdc++ m)

add_custom_command (OUTPUT ${YAPSTARTUP}
  COMMAND yap-bin -b ${CMAKE_SOURCE_DIR}/pl/boot.yap < echo 'bootstrap('${CMAKE_SOURCE_DIR}/pl/init.yap'). module(user). qsave_program('startup.yss').'
)
add_custom_target (yap-startup ALL DEPENDS ${YAPSTARTUP})

INSTALL (
  TARGETS yap-bin
  RUNTIME DESTINATION bin
)

macro_display_feature_log()
message(status ${EXTRALIBS})
message(status ${EXEC_INSTALL_PREFIX})
