LIBRARY := SUHH2ZprimeSemiLeptonic
LWTNNLIB= $(shell scram tool tag lwtnn LIBDIR)
LWTNNINC= $(shell scram tool tag lwtnn INCLUDE)
USERCXXFLAGS := -I${LWTNNINC}
USERLDFLAGS := -lSUHH2core -lSUHH2common -lGenVector -lTMVA -L${LWTNNLIB} -llwtnn
# enable par creation; this is necessary for all packages containing AnalysisModules
# to be loaded from by AnalysisModuleRunner.
PAR := 1
include ../Makefile.common
