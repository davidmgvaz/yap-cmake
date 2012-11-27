SET(SOURCES
  BEAM/eamamasm.c
  BEAM/eam_showcode.c
  BEAM/eamindex.c 
  BEAM/eam_am.c  
  # BEAM/eam_gc.c
  # BEAM/eam_split.c 
  )

ADD_LIBRARY(beam ${SOURCES})