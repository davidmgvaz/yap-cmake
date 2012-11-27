
#ifndef YAP_CONFIG_H

#define YAP_CONFIG_H

#include "parms.h"

/* are dynamic arrays supported? */
#cmakedefine HAVE_DYNARRAY 1

/* are we using gcc */
#cmakedefine HAVE_GCC 1

/* should we use gcc threaded code (i.e. goto *adrs) */
#cmakedefine USE_THREADED_CODE 1

/* Should we use lib readline ? 	*/
#cmakedefine HAVE_LIBREADLINE 1

/* Should we use lib readline ? 	*/
#cmakedefine HAVE_LIBSOCKET 1
#cmakedefine HAVE_LIBNSL 1

/* Should we use gmp ? 	*/
/* #undef HAVE_LIBGMP (not needed: changed) */

/* What MPI libraries are there? */
#define HAVE_LIBMPI 0
#define HAVE_LIBMPICH 

/* Is there an MPE library? */
#define HAVE_LIBMPE 0

/* does the compiler support inline ? */
#cmakedefine inline 1

/* Do we have Ansi headers ?		*/
#cmakedefine STDC_HEADERS 1

/* Host Name ?				*/
#cmakedefine HOST_ALIAS 1

#cmakedefine SUPPORT_CONDOR 1
#cmakedefine USE_PTHREAD_LOCKING 1

#cmakedefine HAVE_SYS_WAIT_H 1
#cmakedefine NO_UNION_WAIT 1

#cmakedefine HAVE_ALLOCA_H 1
/* #undef  HAVE_ARPA_INET_H (not used) */
#cmakedefine HAVE_CTYPE_H 1
#cmakedefine HAVE_CRYPT_H 1
#cmakedefine HAVE_CUDD_H 1
#cmakedefine HAVE_CUDDINT_H 1
#cmakedefine HAVE_CUDD_CUDD_H 1
#cmakedefine HAVE_CUDD_CUDDINT_H 1
#cmakedefine HAVE_CUDD_UTIL_H 1
#cmakedefine HAVE_DIRECT_H 1
#cmakedefine HAVE_DIRENT_H 1
/* #undef  HAVE_DLFCN_H (never defined) */
#cmakedefine HAVE_ERRNO_H 1
#cmakedefine HAVE_EXECINFO_H 1
#cmakedefine HAVE_FCNTL_H 1
#cmakedefine HAVE_FENV_H 1
#cmakedefine HAVE_FLOAT_H 1
#cmakedefine HAVE_FPU_CONTROL_H 1
/* #undef HAVE_GMP_H (not needed: changed) */
#cmakedefine HAVE_IEEEFP_H 1
#cmakedefine HAVE_IO_H 1
#cmakedefine HAVE_LIMITS_H 1
#cmakedefine HAVE_LOCALE_H 1
/* #undef  HAVE_MACH_O_DYLD_H (not used) */
#cmakedefine HAVE_MALLOC_H 1
#cmakedefine HAVE_MATH_H 1
#cmakedefine HAVE_MEMORY_H 1
/* #undef  HAVE_MPE_H (not used) */
#cmakedefine HAVE_MPI_H 1
/* #undef  HAVE_NETDB_H (not used) */
/* #undef  HAVE_NETINET_IN_H (not used) */
#cmakedefine HAVE_NETINET_TCP_H 1
#cmakedefine HAVE_PTHREAD_H 1
#cmakedefine HAVE_PWD_H 1
#cmakedefine HAVE_READLINE_READLINE_H 1
#cmakedefine HAVE_READLINE_HISTORY_H 1
/* #undef  HAVE_REGEX_H (not used) */
#cmakedefine HAVE_RINTERFACE_H 1
#cmakedefine HAVE_SIGINFO_H 1
#cmakedefine HAVE_SIGNAL_H 1
#cmakedefine HAVE_STDARG_H 1
#cmakedefine HAVE_STDINT_H 1
#cmakedefine HAVE_STRING_H 1
/* #undef  HAVE_STROPTS_H (not used) */
/* #undef  HAVE_SYS_CONF_H (not used) */
#cmakedefine HAVE_SYS_DIR_H 1
#cmakedefine HAVE_SYS_FILE_H 1
#cmakedefine HAVE_SYS_MMAN_H 1
#cmakedefine HAVE_SYS_NDIR_H 1
#cmakedefine HAVE_SYS_PARAM_H 1
#cmakedefine HAVE_SYS_RESOURCE_H 1
#cmakedefine HAVE_SYS_SELECT_H 1
#cmakedefine HAVE_SYS_SHM_H 1
/* #undef  HAVE_SYS_SOCKET_H (not used) */
#cmakedefine HAVE_SYS_STAT_H 1
#cmakedefine HAVE_SYS_TIME_H 1
#cmakedefine HAVE_SYS_TIMES_H 1
#cmakedefine HAVE_SYS_TYPES_H 1
#cmakedefine HAVE_SYS_UCONTEXT_H 1
/* #undef  HAVE_SYS_UN_H (not used) */
#cmakedefine HAVE_SYS_WAIT_H 1
#cmakedefine HAVE_TIME_H 1
#cmakedefine HAVE_UNISTD_H 1
#cmakedefine HAVE_UTIME_H 1
#cmakedefine HAVE_UTIL_H 1
#cmakedefine HAVE_WCTYPE_H 1
/* #undef  HAVE_WINSOCK_H (not used) */
/* #undef  HAVE_WINSOCK2_H (not used) */

#if __MINGW32__
#define __WINDOWS__ 1
#endif

/* Do we have restartable syscalls */
/* #undef  HAVE_RESTARTABLE_SYSCALLS (not used) */

/* is 'tms' defined in <sys/time.h> ? */
/* #undef  TM_IN_SYS_TIME (not used) */

/* define type of prt returned by malloc: char or void */
#cmakedefine MALLOC_T 1

/* Define byte order			*/
/* #undef WORDS_BIGENDIAN (used but never defined) */

#include "YapTermConfig.h"

/* Define representation of floats      */
/* only one of the following shoud be set */
/* to add a new representation you must edit FloatOfTerm and MkFloatTerm
  in adtdefs.c
*/
#define  FFIEEE 1
/*manual */
#cmakedefine  1

/* Define the standard type of a float argument to a function */
/*manual */
#define  FAFloat double	

/* Set the minimum and default heap, trail and stack size */
#cmakedefine MinTrailSpace 1
#cmakedefine MinStackSpace 1
#cmakedefine MinHeapSpace 1

#cmakedefine DefTrailSpace 1
#cmakedefine DefStackSpace 1
#cmakedefine DefHeapSpace 1


/* Define return type for signal	*/
#define RETSIGTYPE @RETSIGTYPE@ 

#cmakedefine HAVE__CHSIZE_S 1
#cmakedefine HAVE__NSGETENVIRON 1
#cmakedefine HAVE_ACCESS 1
#cmakedefine HAVE_ACOSH 1
#cmakedefine HAVE_ALARM 1
#cmakedefine HAVE_ALLOCA 1
#cmakedefine HAVE_ASINH 1
#cmakedefine HAVE_ATANH 1
/* #undef  HAVE_CHDIR (not used) */
#cmakedefine HAVE_CLOCK 1
#cmakedefine HAVE_CLOCK_GETTIME 1
/* #undef  HAVE_CTIME (never defined) */
#cmakedefine HAVE_DLOPEN 1
/* #undef  HAVE_DUP2 (not used) */
#cmakedefine HAVE_ERF 1
/* #undef  HAVE_FECLEAREXCEPT (never defined) */
#cmakedefine HAVE_FESETTRAPENABLE 1
#cmakedefine HAVE_FETESTEXCEPT 1
/* #undef  HAVE_FGETPOS (never defined) */
#cmakedefine HAVE_FINITE 1
#cmakedefine HAVE_FPCLASS 1
#cmakedefine HAVE_FTIME 1
#cmakedefine HAVE_GETCWD 1
#cmakedefine HAVE_GETENV 1
/* #undef  HAVE_GETHOSTBYNAME (not used) */
/* #undef  HAVE_GETHOSTENT (never defined) */
#cmakedefine HAVE_GETHOSTID 1
#cmakedefine HAVE_GETHOSTNAME 1
#cmakedefine HAVE_GETHRTIME 1
#cmakedefine HAVE_GETPAGESIZE 1
#cmakedefine HAVE_GETPWNAM 1
#cmakedefine HAVE_GETRLIMIT 1
#cmakedefine HAVE_GETRUSAGE 1
#cmakedefine HAVE_GETTIMEOFDAY 1
#cmakedefine HAVE_GETWD 1
#cmakedefine HAVE_ISATTY 1
#cmakedefine HAVE_ISINF 1
#cmakedefine HAVE_ISNAN 1
/* #undef  HAVE_KILL (not used) */
/* #undef  HAVE_LABS (not used) */
#cmakedefine HAVE_LGAMMA 1
#cmakedefine HAVE_LINK 1
#cmakedefine HAVE_LOCALTIME 1
#cmakedefine HAVE_LSTAT 1
#cmakedefine HAVE_MALLINFO 1
#cmakedefine HAVE_MBSCASECOLL 1
#cmakedefine HAVE_MBSCOLL 1
#cmakedefine HAVE_MBSNRTOWCS 1
#cmakedefine HAVE_MEMCPY 1
#cmakedefine HAVE_MEMMOVE 1
#cmakedefine HAVE_MKSTEMP 1
#cmakedefine HAVE_MKTEMP 1
#cmakedefine HAVE_MKTIME 1
#cmakedefine HAVE_MMAP 1
#cmakedefine HAVE_NANOSLEEP 1
#cmakedefine HAVE_NSLINKMODULE 1
#cmakedefine HAVE_OPENDIR 1
#cmakedefine HAVE_POPEN 1
#cmakedefine HAVE_PTHREAD_MUTEXATTR_SETKIND_NP 1
#cmakedefine HAVE_PTHREAD_MUTEXATTR_SETTYPE 1
#cmakedefine HAVE_PUTENV 1
#cmakedefine HAVE_RAND 1
#cmakedefine HAVE_RANDOM 1
#cmakedefine HAVE_READLINK 1
#cmakedefine HAVE_REGEXEC 1
#cmakedefine HAVE_RENAME 1
#cmakedefine HAVE_RINT 1
/* #undef  HAVE_RL_CLEAR_PENDING_INPUT (never defined) */
/* #undef  HAVE_RL_CLEANUP_AFTER_SIGNAL (never defined) */
#cmakedefine HAVE_RL_COMPLETION_MATCHES 1
#cmakedefine HAVE_RL_EVENT_HOOK 1
#cmakedefine HAVE_RL_FILENAME_COMPLETION_FUNCTION 1
/* #undef  HAVE_RL_FREE_LINE_STATE (never defined) */
#cmakedefine HAVE_RL_INSERT_CLOSE 1
#cmakedefine HAVE_RL_SET_PROMPT 1
/* #undef  HAVE_RL_STATE_INITIALIZED (never defined) */
/* #undef  HAVE_SBRK (not used) */
#cmakedefine HAVE_SELECT 1
#cmakedefine HAVE_SETBUF 1
#cmakedefine HAVE_SETITIMER 1
/* #undef  HAVE_SETLINEBUF (not used) */
#cmakedefine HAVE_SETLOCALE 1
#cmakedefine HAVE_SETSID 1
/* #undef  HAVE_SHMAT (not used) */
#cmakedefine HAVE_SIGACTION 1
/* #undef  HAVE_SIGGETMASK (not used) */
/* #undef  HAVE_SIGINTERRUPT (not used) */
#cmakedefine HAVE_SIGNAL 1
#cmakedefine HAVE_SIGPROCMASK 1
#cmakedefine HAVE_SIGSETJMP 1
#cmakedefine HAVE_SLEEP 1
#cmakedefine HAVE_SNPRINTF 1
/* #undef  HAVE_SOCKET (not used) */
#cmakedefine HAVE_STAT 1
/* #undef  HAVE_STRCHR (not used) */
#cmakedefine HAVE_STRERROR 1
#cmakedefine HAVE_STRICMP 1
#cmakedefine HAVE_STRLWR 1
#cmakedefine HAVE_STRNCAT 1
#cmakedefine HAVE_STRNCPY 1
/* #undef  HAVE_STRTOD (not used) */
#cmakedefine HAVE_SYSTEM 1
#cmakedefine HAVE_TIME 1
#cmakedefine HAVE_TIMES 1
#cmakedefine HAVE_TMPNAM 1
/* #undef  HAVE_TTYNAME (never defined) */
#cmakedefine HAVE_USLEEP 1
#cmakedefine HAVE_UTIME 1
#cmakedefine HAVE_VSNPRINTF 1
#cmakedefine HAVE_WAITPID 1
#cmakedefine HAVE_MPZ_XOR 1

#if HAVE_GETHOSTNAME==1
#define HAS_GETHOSTNAME 1
#endif

#cmakedefine HAVE_SIGINFO 1
#cmakedefine HAVE_SIGSEGV 1
#cmakedefine HAVE_SIGPROF 1

#cmakedefine HAVE_ENVIRON 1

#cmakedefine HAVE_VAR_TIMEZONE 1

#cmakedefine HAVE_STRUCT_TIME_TM_GMTOFF 1

#define  SELECT_TYPE_ARG1    
#define  SELECT_TYPE_ARG234  
#define  SELECT_TYPE_ARG5    

#define  TYPE_SELECT_
#define  MYTYPE(X) MYTYPE1#X

#cmakedefine HAVE_VAR_TIMEZONE 1
#cmakedefine HAVE_STRUCT_TIME_TM_GMTOFF 1

/* define how to pass the address of a function */
#define FunAdr(Fn)  Fn

#define  ALIGN_LONGS 1
#define  LOW_ABSMI 0

#define  MSHIFTOFFS 1

#cmakedefine USE_DL_MALLOC 1
#cmakedefine USE_MALLOC 1
#cmakedefine USE_SYSTEM_MALLOC 1
#define USE_MMAP    (HAVE_MMAP  & !USE_MALLOC & !USE_SYSTEM_MALLOC)
#define USE_SHM	    (HAVE_SHMAT & !HAVE_MMAP & !USE_MALLOC & !USE_SYSTEM_MALLOC)
#define USE_SBRK    (HAVE_SBRK  & !HAVE_MMAP & !HAVE_SHMAT & !USE_MALLOC & !USE_SYSTEM_MALLOC)

/* for OSes that do not allow user access to the first
   quadrant of the memory space */
#cmakedefine FORCE_SECOND_QUADRANT 1

#if (HAVE_SOCKET || defined(__MINGW32__)) && !defined(SIMICS)
#define USE_SOCKET 1
#endif

#if defined(__hpux)
/* HP-UX requires extra definitions for X/Open networking */
#cmakedefine _XOPEN_SOURCE 1
#define _XOPEN_SOURCE_EXTENDED 0
#endif

/* #if HAVE_GMP_H && HAVE_LIBGMP */
#cmakedefine USE_GMP 1
/* #endif */

/* Should we use MPI ? */
#if defined(HAVE_MPI_H) && (defined(HAVE_LIBMPI) || defined(HAVE_LIBMPICH))
 #define HAVE_MPI 1
#else
 #define HAVE_MPI 0
#endif

/* Should we use MPE ? */
#if defined(HAVE_MPI_H) && HAVE_LIBMPE &&  HAVE_MPI
 #define HAVE_MPE 1
#else
 #define HAVE_MPE 0
#endif

/* should we avoid realloc() in mpi.c? */
#define MPI_AVOID_REALLOC 0

/* Is fflush(NULL) clobbering input streams? */
/* #undef BROKEN_FFLUSH_NULL (not used) */

/* sunpro cc */
#ifdef __SUNPRO_CC
#ifdef HAVE_GCC
#cmakedefine HAVE_GCC 1
#endif
#endif

#cmakedefine GC_NO_TAGS 1

#cmakedefine MAX_WORKERS 1

#cmakedefine MAX_THREADS 1

#endif /* YAP_CONFIG_H */

