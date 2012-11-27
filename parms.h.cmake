#define YAP_ROOTDIR      "@ROOTDIR@"
#define YAP_BINDIR      "@BINDIR@"
#define YAP_LIBDIR       "@YAPLIBDIR@"
#define YAP_SHAREDIR     "@SHAREDIR@"
#define YAP_PL_SRCDIR    "@SHAREDIR@/Yap/pl"
#define YAP_STARTUP      "@YAPSTARTUP@"
#define YAP_VERSION      60302
//@echo $(VERSION) | $(AWK) -F. '{ printf("#cmakedefine YAP_VERSION %d\n", $$1 * 10000 + $$2 * 100 + $$3); }' >> $@%
#define MYDDAS_VERSION   "BLHAH"
//@MYDDAS_VERSION@
#define YAP_ARCH	 "i386-darwin12.2.0"
//@ARCH@
#define YAP_LIBS         "@LIBS@"
#define YAP_YAPLIB	      "@YAPLIB@"
#define YAP_CC	      "@CC@"
#define YAP_CFLAGS	      "@CFLAGS@"
#define YAP_LDFLAGS      "@LDFLAGS@"
#define YAP_SHLIB_SUFFIX "@SHLIB_SUFFIX@"
#define YAP_TIMESTAMP    "1349352409" 
//\"`date +%s`\"
#define YAP_SVERSION     "YAP 6.3.2 (i386-darwin12.2.0): Thu Oct  4 13:06:49 WEST 2012"
//\"YAP $(VERSION) ($(ARCH)): `date`\""