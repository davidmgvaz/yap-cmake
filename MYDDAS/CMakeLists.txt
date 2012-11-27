SET(MYDDAS_SOURCES
  myddas_mysql.c 
  myddas_odbc.c 
  myddas_util.c 
  myddas_initialization.c 
  myddas_shared.c 
  myddas_statistics.c 
  myddas_top_level.c 
  myddas_wkb2prolog.c
  )

ADD_LIBRARY(myddas ${MYDDAS_SOURCES})