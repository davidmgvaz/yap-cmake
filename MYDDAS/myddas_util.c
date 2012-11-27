#if defined MYDDAS_ODBC || defined MYDDAS_MYSQL 

#include "Yap.h"
#include <string.h>
#include <stdlib.h>
#include "cut_c.h"
#include "myddas.h"
#include "myddas_structs.h"
#ifdef MYDDAS_STATS
#include "myddas_statistics.h"
#endif
#ifdef MYDDAS_ODBC
#include <sql.h>
#endif /*MYDDAS_ODBC*/
#ifdef MYDDAS_MYSQL
#include <mysql/mysql.h>
#endif /*MYDDAS_MYSQL*/



/* Search for the predicate in the given predicate list*/
static MYDDAS_UTIL_PREDICATE
myddas_util_find_predicate(char *, Int , char *, MYDDAS_UTIL_PREDICATE);
/* Deletes a predicate list */
static void 
myddas_util_delete_predicate_list(MYDDAS_UTIL_PREDICATE);

/* Prints a error message */
static void
myddas_util_error_message(char *,Int,char *);


#ifdef MYDDAS_MYSQL
/* Auxilary function to table_write*/
static void
n_print(Int , char );
#endif

/* Type: MYSQL->1 ODBC->2*/
Short
myddas_util_connection_type(void *con){
  
  MYDDAS_UTIL_CONNECTION con_node =
    myddas_util_search_connection(con);
  
  if (con_node == NULL)
    return 0;

  if (con_node->odbc_enviromment != NULL) /* ODBC */ 
    return 2;
  else
    return 1;
}


MYDDAS_UTIL_PREDICATE
myddas_util_search_predicate(char *pred_name, Int pred_arity, 
			     char *pred_module){
  CACHE_REGS
  MYDDAS_UTIL_PREDICATE pred=NULL;
  MYDDAS_UTIL_CONNECTION top = Yap_REGS.MYDDAS_GLOBAL_POINTER->myddas_top_connections;

  for (;top!=NULL;top=top->next)
    {
      if ((pred=myddas_util_find_predicate(pred_name,pred_arity,pred_module,top->predicates)))
	return pred; 
    }
  return NULL;
}

/* When using this function, we must guarante that this predicate
 it's unique */
MYDDAS_UTIL_CONNECTION 
myddas_util_add_predicate(char *pred_name, Int pred_arity, 
			   char *pred_module, void *con){
  
  MYDDAS_UTIL_CONNECTION node_con = 
    myddas_util_search_connection(con);
  
  MYDDAS_UTIL_PREDICATE new = 
    myddas_init_initialize_predicate(pred_name,pred_arity,pred_module,node_con->predicates);
  
  if (new == NULL)
    {
      myddas_util_error_message("Could not initialize predicate node",__LINE__,__FILE__);
      return NULL;
    }
  
  node_con->predicates=new;
  return node_con;
} 

void
myddas_util_delete_predicate(MYDDAS_UTIL_PREDICATE to_delete){
  CACHE_REGS
  if (to_delete->next != NULL)
    to_delete->next->previous = to_delete->previous;
  if (to_delete->previous != NULL)
    to_delete->previous->next = to_delete->next;
  else //First predicate of the predicate list
    {
      MYDDAS_UTIL_CONNECTION con_node = Yap_REGS.MYDDAS_GLOBAL_POINTER->myddas_top_connections;
      for(;con_node != NULL; con_node = con_node->next)
	if (con_node->predicates == to_delete)
	  break;
      con_node->predicates = to_delete->next;
    }
  MYDDAS_FREE(to_delete,struct myddas_list_preds);
}

void 
myddas_util_delete_connection(void *conn){
  CACHE_REGS
  MYDDAS_UTIL_CONNECTION to_delete = myddas_util_search_connection(conn);
    
  if (to_delete == NULL) 
    return;
  else
    {
      /* Removes the predicates list */
      myddas_util_delete_predicate_list(to_delete->predicates);
      
#ifdef MYDDAS_STATS
      /* Removes the stats list */
      myddas_stats_delete_stats_list(to_delete->stats);
#endif
      /* List Integrety */
      /* Is the last element of the list */
      if ((to_delete->next) != NULL)
	to_delete->next->previous = to_delete->previous;
      
      /* Is the first element of the list */
      if (to_delete == (Yap_REGS.MYDDAS_GLOBAL_POINTER->myddas_top_connections))
	Yap_REGS.MYDDAS_GLOBAL_POINTER->myddas_top_connections = to_delete->next;
      else 
	to_delete->previous->next=to_delete->next;
      
      MYDDAS_FREE(to_delete,struct myddas_list_connection);
      return;
    }
}

MYDDAS_UTIL_CONNECTION 
myddas_util_search_connection(void *conn){
  CACHE_REGS
  MYDDAS_UTIL_CONNECTION list = Yap_REGS.MYDDAS_GLOBAL_POINTER->myddas_top_connections;
  
#ifdef MYDDAS_STATS
  if (conn == 0) { /* We want all the statistics */
    return list;
  }
#endif
  
  for (;list!=NULL;list=list->next)
    if (list->connection == conn)
      return list;
  return NULL;
}
 
MYDDAS_UTIL_CONNECTION 
myddas_util_add_connection(void *conn, void *enviromment){
  CACHE_REGS
  MYDDAS_UTIL_CONNECTION node=NULL;
  MYDDAS_UTIL_CONNECTION temp=NULL;

  if ((node = myddas_util_search_connection(conn)) != NULL)
    {
      return node;
    }
  //put the new connection node on the top of the list
  temp = myddas_init_initialize_connection(conn,enviromment,Yap_REGS.MYDDAS_GLOBAL_POINTER->myddas_top_connections);
  if (temp == NULL)
    {
#ifdef DEBUG
      myddas_util_error_message("Could not initialize connection node",__LINE__,__FILE__);
#endif 
      return NULL;
    }
  Yap_REGS.MYDDAS_GLOBAL_POINTER->myddas_top_connections = temp;
  return Yap_REGS.MYDDAS_GLOBAL_POINTER->myddas_top_connections;
}

#ifdef MYDDAS_ODBC
/* This function searches the MYDDAS list for odbc connections 
 If there isn't any, it returns NULL. This is a nice way to know 
 if there is any odbc connections left on the list*/
SQLHENV
myddas_util_get_odbc_enviromment(SQLHDBC connection){
  CACHE_REGS
  MYDDAS_UTIL_CONNECTION top = Yap_REGS.MYDDAS_GLOBAL_POINTER->myddas_top_connections;
  
  for (;top != NULL;top=top->next)
    if (top->connection == ((void *)connection))
      return top->odbc_enviromment;
  
  return NULL;
}
#endif

UInt
myddas_util_get_total_multi_queries_number(MYDDAS_UTIL_CONNECTION con){
  return con->total_number_queries;
}

void
myddas_util_set_total_multi_queries_number(MYDDAS_UTIL_CONNECTION con,
					   UInt number){
  con->total_number_queries = number;
}

#ifdef MYDDAS_MYSQL
/* Auxilary function to table_write*/
static void
n_print(Int n, char c)
{
  for(;n>0;n--) printf("%c",c);
}
#endif

static
void myddas_util_error_message(char *message ,Int line,char *file){
#ifdef DEBUG
  printf ("ERROR: %s at line %d in file %s\n",message,(int)line,file);
#else
  printf ("ERROR: %s\n",message);
#endif
}

static MYDDAS_UTIL_PREDICATE
myddas_util_find_predicate(char *pred_name, Int pred_arity, 
			   char *pred_module, MYDDAS_UTIL_PREDICATE list){

  for(;list != NULL ; list = list->next)
    if (pred_arity == list->pred_arity && 
	!strcmp(pred_name,list->pred_name) && 
	!strcmp(pred_module,list->pred_module))
      return list;
  
  return NULL;
}

static void 
myddas_util_delete_predicate_list(MYDDAS_UTIL_PREDICATE preds_list){
  CACHE_REGS
  MYDDAS_UTIL_PREDICATE to_delete = NULL;
  
  for (;preds_list != NULL;)
    {
      to_delete = preds_list;
      preds_list = preds_list->next;

      MYDDAS_FREE(to_delete,struct myddas_list_preds);
    }
  return;
}

#ifdef MYDDAS_MYSQL
void
myddas_util_table_write(MYSQL_RES *res_set){
  
  MYSQL_ROW row;
  MYSQL_FIELD *fields;
  Int i,f;

  if (mysql_num_rows(res_set) == 0)
    {
      printf ("Empty Set\n");
      return;
    }

  f = mysql_num_fields(res_set);

  fields = mysql_fetch_field(res_set);
  for(i=0;i<f;i++) 
  {
    printf("+");
    if (strlen(fields[i].name)>fields[i].max_length) fields[i].max_length=strlen(fields[i].name);
    n_print(fields[i].max_length+2,'-');
  }
  printf("+\n");
  
  for(i=0;i<f;i++) 
    {
    printf("|");
    printf(" %s ",fields[i].name);
    n_print(fields[i].max_length - strlen(fields[i].name),' ');
    }
  printf("|\n");
  
  for(i=0;i<f;i++) 
  {
    printf("+");
    n_print(fields[i].max_length+2,'-');
  }
  printf("+\n");
  
  while ((row = mysql_fetch_row(res_set)) != NULL)
    {
      for(i=0;i<f;i++) 
	{
	  printf("|");
	  if (row[i] != NULL) 
	    {
	      printf(" %s ",row[i]);
	      n_print(fields[i].max_length - strlen(row[i]),' ');
	    }
	  else 
	    {
	      printf(" NULL ");
	      n_print(fields[i].max_length - 4,' ');
	    }
	}
      printf("|\n");
    }
  
  for(i=0;i<f;i++) 
    {
      printf("+");
      n_print(fields[i].max_length+2,'-');
    }
  printf("+\n");

}
#endif

//DELETE THIS WHEN DB_STATS  IS COMPLETED
MyddasInt
get_myddas_top( void ){
  CACHE_REGS
  if (Yap_REGS.MYDDAS_GLOBAL_POINTER == NULL)
    return 0;
  return (Int)Yap_REGS.MYDDAS_GLOBAL_POINTER->myddas_top_connections;
}

void *
myddas_util_get_pred_next(void *pointer){
  MYDDAS_UTIL_PREDICATE temp = (MYDDAS_UTIL_PREDICATE) pointer;
  return (void *) (temp->next);
}

MyddasInt 
myddas_util_get_pred_arity(void *pointer){
  MYDDAS_UTIL_PREDICATE temp = (MYDDAS_UTIL_PREDICATE) pointer;
  return temp->pred_arity;
}

char *
myddas_util_get_pred_name(void *pointer){
  MYDDAS_UTIL_PREDICATE temp = (MYDDAS_UTIL_PREDICATE) pointer;
  return temp->pred_name;
}

char *
myddas_util_get_pred_module(void *pointer){
  MYDDAS_UTIL_PREDICATE temp = (MYDDAS_UTIL_PREDICATE) pointer;
  return temp->pred_module;
}

void *
myddas_util_get_list_pred(MYDDAS_UTIL_CONNECTION node){
  return (void *)(node->predicates);
}

#ifdef DEBUG
void check_int( void ){
  CACHE_REGS
  Int i;
  MYDDAS_UTIL_PREDICATE pred = NULL;
  MYDDAS_UTIL_CONNECTION top = Yap_REGS.MYDDAS_GLOBAL_POINTER->myddas_top_connections;
  for (i=1 ; top!=NULL ; top=top->next)
    {
      printf ("***************\n");
      printf ("===== top =====\n");
      printf ("======= %p =====\n",top);
      printf ("CONN: = %p =====\n",top->connection);
      printf ("ENV : = %p =====\n",top->odbc_enviromment);
      printf ("PRED: = %p =====\n",top->predicates);
      printf ("======= %p =====\n",top->previous);
      printf ("======= %p =====\n",top->next);
      if (top->predicates != NULL)
	{
	  printf ("\t******\n");
	  printf ("\t===== PREDICADOS =====\n");
	  for (pred = top->predicates ; pred != NULL ; pred = pred->next)
	    {
	      printf ("\t--------------\n");
	      printf ("\t===== %p =====\n",pred);
	      printf ("\t===== %s =====\n",pred->pred_name);
	      printf ("\t===== %d =====\n",pred->pred_arity);
	      printf ("\t===== %s =====\n",pred->pred_module);
	      printf ("\t===== %p =====\n",pred->previous);
	      printf ("\t===== %p =====\n",pred->next);
	    }
	}
      
    }
  
  return;
}
#endif


#endif /*defined MYDDAS_ODBC || defined MYDDAS_MYSQL*/


