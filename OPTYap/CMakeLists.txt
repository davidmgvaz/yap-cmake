SET(SOURCES
  or.memory.c
  opt.init.c 
  opt.preds.c
  or.copy_engine.c 
  or.cow_engine.c
  or.sba_engine.c 
  or.thread_engine.c 
  or.scheduler.c
  or.cut.c 
  tab.tries.c
  tab.completion.c
  )

ADD_LIBRARY(optyap ${SOURCES})