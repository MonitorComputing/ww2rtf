#
# Borland C++ IDE generated makefile
# Generated 20/07/03 at 01:07:52 
#
.AUTODEPEND


#
# Borland C++ tools
#
IMPLIB  = Implib
BCC32   = Bcc32 +BccW32.cfg 
TLINK32 = TLink32
TLIB    = TLib
BRC32   = Brc32
TASM32  = Tasm32
#
# IDE macros
#


#
# Options
#
IDE_LinkFLAGS32 =  -LC:\BC5\LIB
IDE_ResFLAGS32 = 
LinkerLocalOptsAtW32_ww2rtfdexe =  -Tpe -aa -V4.0 -c
ResLocalOptsAtW32_ww2rtfdexe = 
BLocalOptsAtW32_ww2rtfdexe = 
CompInheritOptsAt_ww2rtfdexe = -IC:\BC5\INCLUDE -D_RTLDLL;_BIDSDLL;_OWLDLL;STRICT;_OWLPCH;
LinkerInheritOptsAt_ww2rtfdexe = -x
LinkerOptsAt_ww2rtfdexe = $(LinkerLocalOptsAtW32_ww2rtfdexe)
ResOptsAt_ww2rtfdexe = $(ResLocalOptsAtW32_ww2rtfdexe)
BOptsAt_ww2rtfdexe = $(BLocalOptsAtW32_ww2rtfdexe)

#
# Dependency List
#
Dep_ww2rtf = \
   ww2rtf.exe

ww2rtf : BccW32.cfg $(Dep_ww2rtf)
  echo MakeNode

Dep_ww2rtfdexe = \
   ww2rtf.res\
   mondocrd.obj\
   monwwrd.obj\
   monrtfwr.obj\
   ww2rtf.obj

ww2rtf.exe : $(Dep_ww2rtfdexe)
  $(TLINK32) @&&|
 /v $(IDE_LinkFLAGS32) $(LinkerOptsAt_ww2rtfdexe) $(LinkerInheritOptsAt_ww2rtfdexe) +
C:\BC5\LIB\c0w32.obj+
mondocrd.obj+
monwwrd.obj+
monrtfwr.obj+
ww2rtf.obj
$<,$*
C:\BC5\LIB\owlwfi.lib+
C:\BC5\LIB\bidsfi.lib+
C:\BC5\LIB\import32.lib+
C:\BC5\LIB\cw32i.lib

|
   $(BRC32) ww2rtf.res $<

ww2rtf.res :  ww2rtf.rc
  $(BRC32) -R @&&|
 $(IDE_ResFLAGS32) $(ROptsAt_ww2rtfdexe) $(CompInheritOptsAt_ww2rtfdexe)  -FO$@ ww2rtf.rc
|
inputdia.res :  c:\bc5\include\owl\inputdia.rc
  $(BRC32) -R @&&|
 $(IDE_ResFLAGS32) $(ROptsAt_ww2rtfdexe) $(CompInheritOptsAt_ww2rtfdexe)  -FO$@ c:\bc5\include\owl\inputdia.rc
|
except.res :  c:\bc5\include\owl\except.rc
  $(BRC32) -R @&&|
 $(IDE_ResFLAGS32) $(ROptsAt_ww2rtfdexe) $(CompInheritOptsAt_ww2rtfdexe)  -FO$@ c:\bc5\include\owl\except.rc
|
mondocrd.obj :  mondocrd.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_ww2rtfdexe) $(CompInheritOptsAt_ww2rtfdexe) -o$@ mondocrd.cpp
|

monwwrd.obj :  monwwrd.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_ww2rtfdexe) $(CompInheritOptsAt_ww2rtfdexe) -o$@ monwwrd.cpp
|

monrtfwr.obj :  monrtfwr.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_ww2rtfdexe) $(CompInheritOptsAt_ww2rtfdexe) -o$@ monrtfwr.cpp
|

ww2rtf.obj :  ww2rtf.cpp
  $(BCC32) -c @&&|
 $(CompOptsAt_ww2rtfdexe) $(CompInheritOptsAt_ww2rtfdexe) -o$@ ww2rtf.cpp
|

# Compiler configuration file
BccW32.cfg : 
   Copy &&|
-w
-R
-v
-vi
-H
-H=ww2rtf.csm
-W
-H"owl\pch.h"
| $@


