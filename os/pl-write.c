/*  $Id$

    Part of SWI-Prolog

    Author:        Jan Wielemaker
    E-mail:        J.Wielemaker@cs.vu.nl
    WWW:           http://www.swi-prolog.org
    Copyright (C): 1985-2010, University of Amsterdam
			      Vu University Amsterdam

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <math.h>
#include "pl-incl.h"
#include "pl-dtoa.h"
#include "pl-ctype.h"
#include <stdio.h>			/* sprintf() */
#ifdef HAVE_LOCALE_H
#include <locale.h>
#endif
#ifdef HAVE_FLOAT_H
#include <float.h>
#endif
#ifdef HAVE_IEEEFP_H
#include <ieeefp.h>
#endif

#ifdef fpclassify
#define HAVE_FPCLASSIFY 1
#endif

#if __YAP_PROLOG__

#define _PL_WRITE_ 1

#include "yapio.h"

#endif

typedef struct visited
{ Word address;				/* we have done this address */
  struct visited *next;			/* next already visited */
} visited;

typedef struct
{ int   flags;				/* PL_WRT_* flags */
  int   max_depth;			/* depth limit */
  int   depth;				/* current depth */
  atom_t spacing;			/* Where to insert spaces */
  Term   module;			/* Module for operators */
  IOSTREAM *out;			/* stream to write to */
  visited *visited;			/* visited (attributed-) variables */
} write_options;

word
pl_nl1(term_t stream)
{ IOSTREAM *s;

  if ( getOutputStream(stream, &s) )
  { Sputcode('\n', s);
    return streamStatus(s);
  }

  fail;
}

word
pl_nl(void)
{ return pl_nl1(0);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
Formatting a float. This used  to  use   sprintf(),  but  there  are two
problems with this. First of all, this uses the current locale, which is
complicated to avoid. Second, it does not provide a mode that guarantees
reliable read-back. Using %g gets closest,   but %.15g doesn't guarantee
read-back and %.17g does, but prints 0.1 as 0.100..001, etc.

This uses dtoa.c. See pl-dtoa.c for how this is packed into SWI-Prolog.

TBD: The number of cases are large. We should see whether it is possible
to clean this up a bit. The 5 cases   as  such are real: there is no way
around these.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

char *
format_float(double f, char *buf)
{ char *end, *o=buf;
  int decpt, sign;
  char *s = dtoa(f, 0, 30, &decpt, &sign, &end);

  DEBUG(2, Sdprintf("decpt=%d, sign=%d, len = %d, '%s'\n",
		    decpt, sign, end-s, s));

  if ( sign )
    *o++ = '-';

  if ( decpt <= 0 )			/* decimal dot before */
  { if ( decpt <= -4 )
    { *o++ = s[0];
      *o++ = '.';
      if ( end-s > 1 )
      { memcpy(o, s+1, end-s-1);
	o += end-s-1;
      } else
	*o++ = '0';
      sprintf(o, "e%d", decpt-1);
    } else
    { int i;

      *o++ = '0';
      *o++ = '.';
      for(i=0; i < -decpt; i++)
	*o++ = '0';
      memcpy(o, s, end-s);
      o[end-s] = 0;
    }
  } else if ( end-s > decpt )		/* decimal dot inside */
  { memcpy(o, s, decpt);
    o += decpt;
    *o++ = '.';
    memcpy(o, s+decpt, end-s-decpt);
    o[end-s-decpt] = 0;
  } else				/* decimal dot after */
  { int i;
    int trailing = decpt-(int)(end-s);

    if ( decpt > 15 )			/* over precision: use eE */
    { *o++ = s[0];
      *o++ = '.';
      if ( end-s > 1 )
      { trailing += (int)(end-s)-1;
	memcpy(o, s+1, end-s-1);
	o += end-s-1;
      } else
	*o++ = '0';
      sprintf(o, "e+%d", trailing);
    } else				/* within precision trail with .0 */
    { memcpy(o, s, end-s);
      o += end-s;

      for(i=(int)(end-s); i<decpt; i++)
	*o++ = '0';
      *o++ = '.';
      *o++ = '0';
      *o = 0;
    }
  }

  freedtoa(s);

  return buf;
}


char *
varName(term_t t, char *name)
{ 
  CACHE_REGS
  CELL *adr = (CELL *)Yap_GetFromSlot(t PASS_REGS);

  if (IsAttVar(adr)) {
    Ssprintf(name, "_D%ld", (CELL)adr - (CELL)H0);
  } else {
    Ssprintf(name, "_%ld", (CELL)adr - (CELL)H0);
  }

  return name;
}


static bool
writeTerm(term_t t, int prec, write_options *options)
{
  CACHE_REGS
  UInt yap_flag = Use_SWI_Stream_f;
  int flags = options->flags;
  Term old_module;
  
  if (flags & PL_WRT_QUOTED)
    yap_flag |= Quote_illegal_f;
  if (options->flags & PL_WRT_NUMBERVARS)
    yap_flag |=  Handle_vars_f;
  if (options->flags & PL_WRT_IGNOREOPS)
    yap_flag |= Ignore_ops_f;
  if (flags & PL_WRT_PORTRAY)
    yap_flag |= Use_portray_f;
  if (flags & PL_WRT_BACKQUOTED_STRING)
    yap_flag |= BackQuote_String_f;
  if (flags & PL_WRT_ATTVAR_IGNORE)
    yap_flag |= 0L;
  if (flags & PL_WRT_ATTVAR_DOTS)
    yap_flag |= AttVar_Dots_f;
  if (flags & PL_WRT_ATTVAR_PORTRAY)
    yap_flag |= AttVar_Portray_f;
  if (flags & PL_WRT_BLOB_PORTRAY)
    yap_flag |= Blob_Portray_f;
  old_module = CurrentModule;
  CurrentModule = options->module;
  Yap_plwrite(Yap_GetFromSlot(t PASS_REGS), options->out, options->max_depth, yap_flag, prec);
  CurrentModule = old_module;
  return TRUE;
}

int
writeAtomToStream(IOSTREAM *s, atom_t atom)
{ Yap_plwrite(MkAtomTerm(YAP_AtomFromSWIAtom(atom)), s, 0, 0, 1200);
  return 1;
}

int
writeAttributeMask(atom_t a)
{ if ( a == ATOM_ignore )
  { return PL_WRT_ATTVAR_IGNORE;
  } else if ( a == ATOM_dots )
  { return PL_WRT_ATTVAR_DOTS;
  } else if ( a == ATOM_write )
  { return PL_WRT_ATTVAR_WRITE;
  } else if ( a == ATOM_portray )
  { return PL_WRT_ATTVAR_PORTRAY;
  } else
    return 0;
}


static int
writeBlobMask(atom_t a)
{ if ( a == ATOM_default )
  { return 0;
  } else if ( a == ATOM_portray )
  { return PL_WRT_BLOB_PORTRAY;
  } else
    return -1;
}


static const opt_spec write_term_options[] =
{ { ATOM_quoted,	    OPT_BOOL },
  { ATOM_ignore_ops,	    OPT_BOOL },
  { ATOM_numbervars,        OPT_BOOL },
  { ATOM_portray,           OPT_BOOL },
  { ATOM_character_escapes, OPT_BOOL },
  { ATOM_max_depth,	    OPT_INT  },
  { ATOM_module,	    OPT_ATOM },
  { ATOM_backquoted_string, OPT_BOOL },
  { ATOM_attributes,	    OPT_ATOM },
  { ATOM_priority,	    OPT_INT },
  { ATOM_partial,	    OPT_BOOL },
  { ATOM_spacing,	    OPT_ATOM },
  { ATOM_blobs,		    OPT_ATOM },
  { NULL_ATOM,	     	    0 }
};

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
PutOpenToken() inserts a space in the output stream if the last-written
and given character require a space to ensure a token-break.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#define TRUE_WITH_SPACE 2		/* OK, and emitted leading space before token */

static bool
Putc(int c, IOSTREAM *s)
{ return Sputcode(c, s) == EOF ? FALSE : TRUE;
}

#define LAST_C_RESERVED		0x110000 /* Above Unicode range */
#define PREFIX_SIGN		(LAST_C_RESERVED+1)

#define isquote(c) ((c) == '\'' || (c) == '"')

static bool
needSpace(int c, IOSTREAM *s)
{ if ( c == EOF )
  { s->lastc = EOF;
    return FALSE;
  }

  if ( s->lastc == PREFIX_SIGN )	/* avoid passing to is*W() functions */
  { if ( isDigit(c) || isSymbolW(c) )
      return TRUE;
    return FALSE;
  }

  if ( s->lastc != EOF &&
       ((isAlphaW(s->lastc) && isAlphaW(c)) ||
	(isSymbolW(s->lastc) && isSymbolW(c)) ||
	(s->lastc != '(' && !isBlank(s->lastc) && c == '(') ||
	(c == '\'' && (isDigit(s->lastc))) ||
	(isquote(c) && s->lastc == c)
       ) )
    return TRUE;

  return FALSE;
}


static int
PutOpenToken(int c, IOSTREAM *s)
{ if ( needSpace(c, s) )
  { TRY(Putc(' ', s));
    return TRUE_WITH_SPACE;
  }

  return TRUE;
}

word
pl_write_term3(term_t stream, term_t term, term_t opts)
{ GET_LD
  bool quoted     = FALSE;
  bool ignore_ops = FALSE;
  bool numbervars = -1;			/* not set */
  bool portray    = FALSE;
  bool bqstring   = truePrologFlag(PLFLAG_BACKQUOTED_STRING);
  bool charescape = -1;			/* not set */
  atom_t mname    = ATOM_user;
  atom_t attr     = ATOM_nil;
  atom_t blobs    = ATOM_nil;
  int  priority   = 1200;
  bool partial    = FALSE;
  IOSTREAM *s;
  write_options options;
  int rc;

  memset(&options, 0, sizeof(options));
  options.spacing = ATOM_standard;

  if ( !scan_options(opts, 0, ATOM_write_option, write_term_options,
		     &quoted, &ignore_ops, &numbervars, &portray,
		     &charescape, &options.max_depth, &mname,
		     &bqstring, &attr, &priority, &partial, &options.spacing,
		     &blobs) )
    fail;

  if ( attr == ATOM_nil )
  { options.flags |= LD->prolog_flag.write_attributes;
  } else
  { int mask = writeAttributeMask(attr);

    if ( !mask )
      return PL_error(NULL, 0, NULL, ERR_DOMAIN, ATOM_write_option, opts);

    options.flags |= mask;
  }
  if ( blobs != ATOM_nil )
  { int mask = writeBlobMask(blobs);

    if ( mask < 0 )
      return PL_error(NULL, 0, NULL, ERR_DOMAIN, ATOM_write_option, opts);

    options.flags |= mask;
  }
  if ( priority < 0 || priority > OP_MAXPRIORITY )
  { term_t t = PL_new_term_ref();
    PL_put_integer(t, priority);

    return PL_error(NULL, 0, NULL, ERR_DOMAIN, ATOM_operator_priority, t);
  }
  switch( options.spacing )
  { case ATOM_standard:
    case ATOM_next_argument:
      break;
    default:
    { term_t t = PL_new_term_ref();
      PL_put_atom(t, options.spacing);

      return PL_error(NULL, 0, NULL, ERR_DOMAIN, ATOM_spacing, t);
    }
  }

  if ( !getOutputStream(stream, &s) )
    fail;

  options.module = lookupModule(mname);
  if ( charescape == TRUE ||
       //       (charescape == -1 && true(options.module, CHARESCAPE)) )
       charEscapeWriteOption(options))
    options.flags |= PL_WRT_CHARESCAPES;
  if ( numbervars == -1 )
    numbervars = (portray ? TRUE : FALSE);

  if ( quoted )     options.flags |= PL_WRT_QUOTED;
  if ( ignore_ops ) options.flags |= PL_WRT_IGNOREOPS;
  if ( numbervars ) options.flags |= PL_WRT_NUMBERVARS;
  if ( portray )    options.flags |= PL_WRT_PORTRAY;
  if ( bqstring )   options.flags |= PL_WRT_BACKQUOTED_STRING;

  options.out = s;
  if ( !partial )
    PutOpenToken(EOF, s);		/* reset this */
  if ( (options.flags & PL_WRT_QUOTED) && !(s->flags&SIO_REPPL) )
  { s->flags |= SIO_REPPL;
    rc = writeTerm(term, priority, &options);
    s->flags &= ~SIO_REPPL;
  } else
  { rc = writeTerm(term, priority, &options);
  }

  return streamStatus(s) && rc;
}


word
pl_write_term(term_t term, term_t options)
{ return pl_write_term3(0, term, options);
}


int
PL_write_term(IOSTREAM *s, term_t term, int precedence, int flags)
{ write_options options;

  memset(&options, 0, sizeof(options));
  options.flags	    = flags;
  options.out	    = s;
  options.module    = USER_MODULE; //MODULE_user;

  PutOpenToken(EOF, s);			/* reset this */
  return writeTerm(term, precedence, &options);
}


static word
do_write2(term_t stream, term_t term, int flags)
{ GET_LD
  IOSTREAM *s;

  if ( getOutputStream(stream, &s) )
  { write_options options;
    int rc;

    memset(&options, 0, sizeof(options));
    options.flags     = flags;
    options.out	      = s;
    options.module    = USER_MODULE; // MODULE_user;
    //    if ( options.module && true(options.module, CHARESCAPE) )
    if (charEscapeWriteOption(options))
      options.flags |= PL_WRT_CHARESCAPES;
    if ( truePrologFlag(PLFLAG_BACKQUOTED_STRING) )
      options.flags |= PL_WRT_BACKQUOTED_STRING;

    PutOpenToken(EOF, s);		/* reset this */
    rc = writeTerm(term, 1200, &options);

    return streamStatus(s) && rc;
  }

  return FALSE;
}


word
pl_write2(term_t stream, term_t term)
{ return do_write2(stream, term, PL_WRT_NUMBERVARS);
}

word
pl_writeq2(term_t stream, term_t term)
{ return do_write2(stream, term, PL_WRT_QUOTED|PL_WRT_NUMBERVARS);
}

word
pl_print2(term_t stream, term_t term)
{ return do_write2(stream, term,
		   PL_WRT_PORTRAY|PL_WRT_NUMBERVARS);
}

word
pl_write_canonical2(term_t stream, term_t term)
{ GET_LD
  fid_t fid;
  nv_options options;
  word rc;

  if ( !(fid = PL_open_foreign_frame()) )
    return FALSE;
  options.functor = FUNCTOR_isovar1;
  options.on_attvar = AV_SKIP;
  options.singletons = TRUE;
#if __YAP_PROLOG__
  LOCAL_FunctorVar = FunctorHiddenVar;
#endif
  numberVars(term, &options, 0 PASS_LD);
  rc = do_write2(stream, term,
		 PL_WRT_QUOTED|PL_WRT_IGNOREOPS|PL_WRT_NUMBERVARS);
#if __YAP_PROLOG__
  LOCAL_FunctorVar = FunctorVar;
#endif
  PL_discard_foreign_frame(fid);

  return rc;
}

word
pl_write(term_t term)
{ return pl_write2(0, term);
}

word
pl_writeq(term_t term)
{ return pl_writeq2(0, term);
}

word
pl_print(term_t term)
{ return pl_print2(0, term);
}

word
pl_write_canonical(term_t term)
{ return pl_write_canonical2(0, term);
}

word					/* for debugging purposes! */
pl_writeln(term_t term)
{ if ( PL_write_term(Serror, term, 1200,
		     PL_WRT_QUOTED|PL_WRT_NUMBERVARS) &&
       Sdprintf("\n") >= 0 )
    succeed;

  fail;
}


		 /*******************************
		 *      PUBLISH PREDICATES	*
		 *******************************/

BeginPredDefs(write)
EndPredDefs

