//**********************************************************************
//                                                                     *
//    Filename:	     mondocrd.cpp                                      *
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

#include  <ctype.h>
#include  <fstream.h>


#include "mondocrd.h"


MonDocReader::MonDocReader(
  ifstream            *newSource,
  class MonDocWriter  *newWriter,
  void                *newTraceObj,
  void                (*newTraceFunc)(void*, const char*)) :
  source(newSource), writer(newWriter), traceObj(newTraceObj),
  traceFunc(newTraceFunc)
{;}


int
MonDocReader::convertInteger()
{
  int  outputInt = 0;

  while(isdigit(source->peek()))
  {
	 outputInt *= 10;
	 outputInt += (0x0F & source->get());
  }

  return outputInt;
}


void
MonDocReader::traceAdd(char  newChar)
{
  if (0 != traceObj)
  {
	 static char  traceText[] = {'\0', '\0'};

	 *traceText  =  newChar;
	 traceString += traceText;
  }
}


void
MonDocReader::traceAdd(int  newChar)
{
  if (0 != traceObj)
  {
	 static  char  traceText[] = {'\0', '\0'};

	 traceString += " ";
	 *traceText = ((newChar >> 4) & 0xF) | 0x30;
	 if ('9' < *traceText)
	 {
		*traceText += 7;
	 }
	 traceString += traceText;

	 *traceText = (newChar & 0xF) | 0x30;
	 if ('9' < *traceText)
	 {
		*traceText += 7;
	 }
	 traceString += traceText;
	 traceString += " ";
  }
}


void
MonDocReader::traceWrite()
{
  if ((0 != traceObj) && (0 != traceFunc))
  {
	 traceString += "\r\n";
	 traceFunc(traceObj, traceString.c_str());
	 traceString.resize(0);
  }
}

void
MonDocReader::traceWrite(char  *traceText)
{
  if ((0 != traceObj) && (0 != traceFunc))
  {
	 traceString += "\r\n";
	 traceFunc(traceObj, traceString.c_str());
	 traceFunc(traceObj, traceText);
	 traceFunc(traceObj, "\r\n");
	 traceString.resize(0);
  }
}
