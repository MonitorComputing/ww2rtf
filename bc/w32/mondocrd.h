#ifndef _MONDOCRD_H_INCLUDED_
#define _MONDOCRD_H_INCLUDED_
//**********************************************************************
//                                                                     *
//    Filename:	     mondocrd.h                                        *
//    Date:          16 Feb 2002                                       *
//    File Version:  1                                                 *
//                                                                     *
//    Author:        Chris White (whitecf@bcs.org.uk)                  *
//    Company:       Monitor Computing Services Ltd.                   *
//                                                                     *
//**********************************************************************
//                                                                     *
//    Copyright (C) 2002  Monitor Computing Services Ltd.              *
//                                                                     *
//    This program is free software; you can redistribute it and/or    *
//    modify it under the terms of the GNU General Public License      *
//    as published by the Free Software Foundation; either version 2   *
//    of the License, or any later version.                            *
//                                                                     *
//    This program is distributed in the hope that it will be useful,  *
//    but WITHOUT ANY WARRANTY; without even the implied warranty of   *
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the    *
//    GNU General Public License for more details.                     *
//                                                                     *
//    You should have received a copy of the GNU General Public        *
//    License (http://www.gnu.org/copyleft/gpl.html) along with this   *
//    program; if not, write to:                                       *
//       The Free Software Foundation Inc.,                            *
//       59 Temple Place - Suite 330,                                  *
//       Boston, MA  02111-1307,                                       *
//       USA.                                                          *
//                                                                     *
//**********************************************************************
//                                                                     *
//    Notes:                                                           *
//                                                                     *
//**********************************************************************

#include  <cstring.h>


class MonDocReader
{
public:

  virtual ~MonDocReader() {;}

  virtual void  convert() = 0;
  virtual void  convertCommand() = 0;

protected:

  MonDocReader(class ifstream      *newSource,
					class MonDocWriter  *newWriter,
					void                *newTraceObj = 0,
					void                (*newTraceFunc)(void*, const char*) = 0);
  MonDocReader(MonDocReader&) {;}
  MonDocReader(MonDocReader*) {;}

  int  convertInteger();

  void  traceAdd(char  newChar);
  void  traceAdd(int  newChar);
  void  traceWrite();
  void  traceWrite(char  *traceText);

  class ifstream      *source;
  class MonDocWriter  *writer;
  void                *traceObj;
  void                (*traceFunc)(void*, const char*);
  string              traceString;


};


#endif
