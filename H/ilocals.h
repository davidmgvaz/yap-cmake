
  /* This file, ilocals.h, was generated automatically by "yap -L misc/buildlocalglobal"
     please do not update, update misc/LOCALS instead */


static void InitWorker(int wid) {

  REMOTE_c_input_stream(wid) = 0;
  REMOTE_c_output_stream(wid) = 1;
  REMOTE_c_error_stream(wid) = 2;

  REMOTE_OldASP(wid) = NULL;
  REMOTE_OldLCL0(wid) = NULL;
  REMOTE_OldTR(wid) = NULL;
  REMOTE_OldGlobalBase(wid) = NULL;
  REMOTE_OldH(wid) = NULL;
  REMOTE_OldH0(wid) = NULL;
  REMOTE_OldTrailBase(wid) = NULL;
  REMOTE_OldTrailTop(wid) = NULL;
  REMOTE_OldHeapBase(wid) = NULL;
  REMOTE_OldHeapTop(wid) = NULL;
  REMOTE_ClDiff(wid) = 0L;
  REMOTE_GDiff(wid) = 0L;
  REMOTE_HDiff(wid) = 0L;
  REMOTE_GDiff0(wid) = 0L;
  REMOTE_GSplit(wid) = NULL;
  REMOTE_LDiff(wid) = 0L;
  REMOTE_TrDiff(wid) = 0L;
  REMOTE_XDiff(wid) = 0L;
  REMOTE_DelayDiff(wid) = 0L;
  REMOTE_BaseDiff(wid) = 0L;

  REMOTE_ReductionsCounter(wid) = 0L;
  REMOTE_PredEntriesCounter(wid) = 0L;
  REMOTE_RetriesCounter(wid) = 0L;
  REMOTE_ReductionsCounterOn(wid) = 0L;
  REMOTE_PredEntriesCounterOn(wid) = 0L;
  REMOTE_RetriesCounterOn(wid) = 0L;


  REMOTE_ConsultSp(wid) = NULL;



  REMOTE_ConsultBase(wid) = NULL;

  REMOTE_ConsultLow(wid) = NULL;

  REMOTE_GlobalArena(wid) = 0L;
  REMOTE_GlobalArenaOverflows(wid) = 0L;
  REMOTE_ArenaOverflows(wid) = 0L;
  REMOTE_DepthArenas(wid) = 0;
  REMOTE_ArithError(wid) = FALSE;
  REMOTE_LastAssertedPred(wid) = NULL;
  REMOTE_DebugOn(wid) = FALSE;
  REMOTE_ScannerStack(wid) = NULL;
  REMOTE_ScannerExtraBlocks(wid) = NULL;
  REMOTE_BallTerm(wid) = NULL;
  REMOTE_ActiveSignals(wid) = 0L;
  REMOTE_IPredArity(wid) = 0L;
  REMOTE_ProfEnd(wid) = NULL;
  REMOTE_UncaughtThrow(wid) = FALSE;
  REMOTE_DoingUndefp(wid) = FALSE;
  REMOTE_StartLine(wid) = 0L;
  InitScratchPad(wid);
#ifdef  COROUTINING
  REMOTE_WokenGoals(wid) = 0L;
  REMOTE_AttsMutableList(wid) = 0L;
#endif

  REMOTE_GcGeneration(wid) = 0L;
  REMOTE_GcPhase(wid) = 0L;
  REMOTE_GcCurrentPhase(wid) = 0L;
  REMOTE_GcCalls(wid) = 0L;
  REMOTE_TotGcTime(wid) = 0L;
  REMOTE_TotGcRecovered(wid) = 0L;
  REMOTE_LastGcTime(wid) = 0L;
  REMOTE_LastSSTime(wid) = 0L;
  REMOTE_OpenArray(wid) = NULL;

  REMOTE_total_marked(wid) = 0L;
  REMOTE_total_oldies(wid) = 0L;
  REMOTE_current_B(wid) = NULL;
  REMOTE_prev_HB(wid) = NULL;
  REMOTE_HGEN(wid) = NULL;
  REMOTE_iptop(wid) = NULL;
#if defined(GC_NO_TAGS)
  REMOTE_bp(wid) = NULL;
#endif
  REMOTE_sTR(wid) = NULL;
  REMOTE_sTR0(wid) = NULL;
  REMOTE_new_TR(wid) = NULL;
  REMOTE_cont_top0(wid) = NULL;
  REMOTE_cont_top(wid) = NULL;
  REMOTE_discard_trail_entries(wid) = 0;

  REMOTE_gc_ma_h_top(wid) = NULL;
  REMOTE_gc_ma_h_list(wid) = NULL;
  REMOTE_gc_timestamp(wid) = 0L;
  REMOTE_db_vec(wid) = NULL;
  REMOTE_db_vec0(wid) = NULL;
  REMOTE_db_root(wid) = NULL;
  REMOTE_db_nil(wid) = NULL;




  REMOTE_extra_gc_cells_size(wid) = 256;
  REMOTE_DynamicArrays(wid) = NULL;
  REMOTE_StaticArrays(wid) = NULL;
  REMOTE_GlobalVariables(wid) = NULL;
  REMOTE_AllowRestart(wid) = FALSE;

  REMOTE_CMemFirstBlock(wid) = NULL;
  REMOTE_CMemFirstBlockSz(wid) = 0L;

  REMOTE_nperm(wid) = 0L;

  REMOTE_LabelFirstArray(wid) = NULL;
  REMOTE_LabelFirstArraySz(wid) = 0L;

  REMOTE_PL_local_data_p(wid) = Yap_InitThreadIO(wid);
#ifdef THREADS
  InitThreadHandle(wid);
#endif /* THREADS */
#if defined(YAPOR) || defined(TABLING)
  Yap_init_local_optyap_data(wid);
#endif /* YAPOR || TABLING */
  REMOTE_InterruptsDisabled(wid) = FALSE;
  REMOTE_execution(wid) = NULL;
#if LOW_LEVEL_TRACER
  REMOTE_total_choicepoints(wid) = 0;
#endif
  REMOTE_consult_level(wid) = 0;
#if defined(YAPOR) || defined(THREADS)
  INIT_LOCK(REMOTE_SignalLock(wid));
#endif







#ifdef THREADS

#else

#endif	

















  REMOTE_PrologMode(wid) = BootMode;
  REMOTE_CritLocks(wid) = 0;


#ifdef ANALYST


#endif /* ANALYST */



  REMOTE_matherror(wid) = YAP_NO_ERROR;

  REMOTE_heap_overflows(wid) = 0;
  REMOTE_total_heap_overflow_time(wid) = 0;
  REMOTE_stack_overflows(wid) = 0;
  REMOTE_total_stack_overflow_time(wid) = 0;
  REMOTE_delay_overflows(wid) = 0;
  REMOTE_total_delay_overflow_time(wid) = 0;
  REMOTE_trail_overflows(wid) = 0;
  REMOTE_total_trail_overflow_time(wid) = 0;
  REMOTE_atom_table_overflows(wid) = 0;
  REMOTE_total_atom_table_overflow_time(wid) = 0;

#ifdef LOAD_DYLD
  REMOTE_dl_errno(wid) = 0;
#endif

#ifdef LOW_LEVEL_TRACER
  REMOTE_do_trace_primitives(wid) = TRUE;
#endif

  REMOTE_ExportAtomHashChain(wid) = NULL;
  REMOTE_ExportAtomHashTableSize(wid) = 0;
  REMOTE_ExportAtomHashTableNum(wid) = 0;
  REMOTE_ExportFunctorHashChain(wid) = NULL;
  REMOTE_ExportFunctorHashTableSize(wid) = 0;
  REMOTE_ExportFunctorHashTableNum(wid) = 0;
  REMOTE_ExportPredEntryHashChain(wid) = NULL;
  REMOTE_ExportPredEntryHashTableSize(wid) = 0;
  REMOTE_ExportPredEntryHashTableNum(wid) = 0;
  REMOTE_ExportDBRefHashChain(wid) = NULL;
  REMOTE_ExportDBRefHashTableSize(wid) = 0;
  REMOTE_ExportDBRefHashTableNum(wid) = 0;
  REMOTE_ImportAtomHashChain(wid) = NULL;
  REMOTE_ImportAtomHashTableSize(wid) = 0;
  REMOTE_ImportAtomHashTableNum(wid) = 0;
  REMOTE_ImportFunctorHashChain(wid) = NULL;
  REMOTE_ImportFunctorHashTableSize(wid) = 0;
  REMOTE_ImportFunctorHashTableNum(wid) = 0;
  REMOTE_ImportOPCODEHashChain(wid) = NULL;
  REMOTE_ImportOPCODEHashTableSize(wid) = 0;
  REMOTE_ImportPredEntryHashChain(wid) = NULL;
  REMOTE_ImportPredEntryHashTableSize(wid) = 0;
  REMOTE_ImportPredEntryHashTableNum(wid) = 0;
  REMOTE_ImportDBRefHashChain(wid) = NULL;
  REMOTE_ImportDBRefHashTableSize(wid) = 0;
  REMOTE_ImportDBRefHashTableNum(wid) = 0;
  REMOTE_ImportFAILCODE(wid) = NULL;











  REMOTE_DIRNAME(wid) = NULL;
#if LOW_PROF
  REMOTE_ProfilerOn(wid) = FALSE;
  REMOTE_FProf(wid) = NULL;
  REMOTE_FPreds(wid) = NULL;
#endif /* LOW_PROF */
  REMOTE_FunctorVar(wid) = FunctorVar;
}
