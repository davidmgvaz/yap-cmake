
  /* This file, dglobals.h, was generated automatically by "yap -L misc/buildlocalglobal"
     please do not update, update misc/GLOBALS instead */



















#define GLOBAL_Initialised Yap_global->Initialised_
#define GLOBAL_InitialisedFromPL Yap_global->InitialisedFromPL_
#define GLOBAL_PL_Argc Yap_global->PL_Argc_
#define GLOBAL_PL_Argv Yap_global->PL_Argv_

#define GLOBAL_HaltHooks Yap_global->HaltHooks_

#define GLOBAL_AllowLocalExpansion Yap_global->AllowLocalExpansion_
#define GLOBAL_AllowGlobalExpansion Yap_global->AllowGlobalExpansion_
#define GLOBAL_AllowTrailExpansion Yap_global->AllowTrailExpansion_
#define GLOBAL_SizeOfOverflow Yap_global->SizeOfOverflow_

#define GLOBAL_AGcThreshold Yap_global->AGcThreshold_
#define GLOBAL_AGCHook Yap_global->AGCHook_

#if THREADS

#define GLOBAL_NOfThreads Yap_global->NOfThreads_

#define GLOBAL_NOfThreadsCreated Yap_global->NOfThreadsCreated_

#define GLOBAL_ThreadsTotalTime Yap_global->ThreadsTotalTime_

#define GLOBAL_ThreadHandlesLock Yap_global->ThreadHandlesLock_
#endif	
#if defined(YAPOR) || defined(THREADS)

#define GLOBAL_BGL Yap_global->BGL_
#endif
#if defined(YAPOR) || defined(TABLING)
#define GLOBAL_optyap_data Yap_global->optyap_data_
#endif /* YAPOR || TABLING */

#define GLOBAL_PrologShouldHandleInterrupts Yap_global->PrologShouldHandleInterrupts_

#if defined(THREADS)
#define GLOBAL_master_thread Yap_global->master_thread_
#endif /* THREADS */

#define GLOBAL_stdout Yap_global->stdout_
#define GLOBAL_stderr Yap_global->stderr_

#define GLOBAL_argv Yap_global->argv_
#define GLOBAL_argc Yap_global->argc_

#ifdef COROUTINING

#define GLOBAL_attas Yap_global->attas_
#endif

#define GLOBAL_agc_calls Yap_global->agc_calls_
#define GLOBAL_agc_collected Yap_global->agc_collected_

#define GLOBAL_tot_agc_time Yap_global->tot_agc_time_

#define GLOBAL_tot_agc_recovered Yap_global->tot_agc_recovered_

#if HAVE_MMAP
#define GLOBAL_mmap_arrays Yap_global->mmap_arrays_
#endif
#ifdef DEBUG

#define GLOBAL_Option Yap_global->Option_
#define GLOBAL_logfile Yap_global->logfile_


#endif
#if defined(COFF)  || defined(A_OUT)

#define GLOBAL_Executable Yap_global->Executable_
#endif
#define GLOBAL_OpaqueHandlersCount Yap_global->OpaqueHandlersCount_
#define GLOBAL_OpaqueHandlers Yap_global->OpaqueHandlers_
#if  __simplescalar__
#define GLOBAL_pwd Yap_global->pwd_
#endif



