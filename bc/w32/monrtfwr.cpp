//**********************************************************************
//                                                                     *
//    Filename:	     monrtfwr.cpp                                      *
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

#include <cstring.h>
#include <fstream.h>

#include "monrtfwr.h"


const float  MonRtfWriter::twipsPerInch = 1440.0;


MonRtfWriter::MonRtfWriter(const char  *inFileName)
{
  static const string  extSep(".");
  static const char    *outExt = ".rtf";
  string               outFileName(inFileName);
  int                  extSepAt = outFileName.find_last_of(extSep);

  if (0 != extSepAt)
  {
	 outFileName.resize(extSepAt);
  }
  outFileName += outExt;

  output = new ofstream(outFileName.c_str());
}


MonRtfWriter::~MonRtfWriter()
{
  delete  output;
  output = 0;
}


void
MonRtfWriter::Begin()
{
  *output << "{\\rtf1\\ansi" << endl <<
				 "{\\fonttbl{\\f0\\froman Times New Roman}}" << endl <<
				 "\\fs24 ";
}


void
MonRtfWriter::leftMargin(float  inches)
{
  *output << "\\margl" << (int)(twipsPerInch * inches) << " ";
}


void
MonRtfWriter::rightMargin(float  inches)
{
  *output << "\\margr" << (int)(twipsPerInch * inches) << " ";
}


void
MonRtfWriter::topMargin(float  inches)
{
  *output << "\\margt" << (int)(twipsPerInch * inches) << " ";
}


void
MonRtfWriter::bottomMargin(float  inches)
{
  *output << "\\margb" << (int)(twipsPerInch * inches) << " ";
}


void
MonRtfWriter::leftIndent(float  inches)
{
  *output << "\\li" << (int)(twipsPerInch * inches) << " ";
}


void
MonRtfWriter::firstLineIndent(float  inches)
{
  *output << "\\fi" << (int)(twipsPerInch * inches) << " ";
}


void
MonRtfWriter::write(char  charToWrite)
{
  switch (charToWrite)
  {
  case '\\':
	 *output << "\\\\";
	 break;
  case '{':
	 *output << "\\{";
	 break;
  case '}':
	 *output << "\\}";
	 break;
  default:
	 *output << charToWrite;
	 break;
  }
}


void
MonRtfWriter::writeHardSpace()
{
  *output << "\\~ ";
}


void
MonRtfWriter::justify()
{
  *output << "\\qj ";
}


void
MonRtfWriter::leftJustify()
{
  *output << "\\ql ";
}


void
MonRtfWriter::endParagraph()
{
  *output << "\\par" << endl;
}


void
MonRtfWriter::endPage()
{
  *output << "\\page " << endl;
}


void
MonRtfWriter::End()
{
  endParagraph();
  *output << endl << "}" << endl;

  output->close();
}

