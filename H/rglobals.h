
  /* This file, rglobals.h, was generated automatically by "yap -L misc/buildlocalglobal"
     please do not update, update misc/GLOBALS instead */

















static void RestoreGlobal(void) {
















#if THREADS







  REINIT_LOCK(GLOBAL_ThreadHandlesLock);
#endif	
#if defined(YAPOR) || defined(THREADS)

  REINIT_LOCK(GLOBAL_BGL);
#endif
#if defined(YAPOR) || defined(TABLING)

#endif /* YAPOR || TABLING */



#if defined(THREADS)

#endif /* THREADS */







#ifdef COROUTINING


#endif








#if HAVE_MMAP

#endif
#ifdef DEBUG





#endif
#if defined(COFF)  || defined(A_OUT)


#endif


#if  __simplescalar__

#endif


}
