//**********************************************************************
//                                                                     *
//    Filename:	     monwwrd.cpp                                       *
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
#include  <stdio.h>

#include "monwwrd.h"
#include "mondocwr.h"


MonWordWiseReader::MonWordWiseReader(
  ifstream      *source,
  MonDocWriter  *writer,
  void          *traceObj,
  void          (*traceFunc)(void*, const char*))  :
  MonDocReader(source, writer, traceObj, traceFunc),
  poundSign('£'), padChar('|'), linesPerInch(6.0), charactersPerInch(10.0),
  pageWidth(8.19), pageLength(11.583), leftMargin(0.0)
{
}


void
MonWordWiseReader::convert()
{
  int   inputInt  = EOF;
  char  inputChar = '\0';

  writer->Begin();

  while (EOF != (inputInt = source->get()))
  {
	 inputChar = (inputInt &= 0xFF);

	 if (!iscntrl(inputInt))
	 {
		if (inputChar == padChar)
		{
		  writer->writeHardSpace();
		  traceAdd(' ');
		}
		else
		{
		  writer->write(inputChar);
		  traceAdd(inputChar);
		}
	 }
	 else
	 {
		switch (inputInt)
		{
		case 0x0D:
		  writer->endParagraph();
		  traceWrite();
		  break;
		case 0x02:
		  convertCommand();
		  break;
		default:
		  traceAdd(inputInt);
		  break;
		}
	 }
  }
  traceWrite();

  writer->End();
}


void
MonWordWiseReader::convertCommand()
{
  int   inputInt = EOF;

  while ((EOF != (inputInt = source->get())) &&
			(0x0D != inputInt) && (0x07 != inputInt))
  {
	 switch ((char)inputInt)
	 {
	 case 'B':
		switch((char)source->get())
		{
		case 'P':
		  traceWrite("BP == Begin new Page");
		  writer->endPage();
		  break;
		case 'S':
		{
		  traceWrite("BS == Bottom Space");
		  float  marginLines = (float)convertInteger();
		  writer->bottomMargin(marginLines / linesPerInch);
		  break;
		}
		}
		break;
	 case 'C':
		switch((char)source->get())
		{
		case 'I':
		  traceWrite("CI == Cancel all Indents");
		  writer->leftIndent(0.0);
		  break;
		case 'O':
		  traceWrite("CO == Continuous Output (no paging), ignored");
		  break;
		}
		break;
	 case 'D':
		switch((char)source->get())
		{
		case 'F':
		  traceWrite("DF == Define footing, ignored");
		  break;
		case 'H':
		  traceWrite("DH == Define heading, ignored");
		  break;
		case 'M':
		  traceWrite("DM == Disable Paper Message, ignored");
		  break;
		}
		break;
	 case 'E':
		switch((char)source->get())
		{
		case 'M':
		  traceWrite("EM == Enable Paper Message, ignored");
		  break;
		case 'P':
		  traceWrite("EP == Enable Paging, ignored");
		  break;
		}
		break;
	 case 'F':
		switch((char)source->get())
		{
		case 'P':
		  traceWrite("FP == Footing position, ignored");
		  break;
		}
		break;
	 case 'G':
		switch((char)source->get())
		{
		case 'F':
		  traceWrite("GF == Get file, ignored");
		  break;
		}
		break;
	 case 'H':
		switch((char)source->get())
		{
		case 'P':
		  traceWrite("HP == Heading position, ignored");
		  break;
		}
		break;
	 case 'I':
		switch((char)source->get())
		{
		case 'N':
		{
		  traceWrite("IN == Indent");
		  float  indentSpaces = (float)convertInteger();
		  writer->leftIndent(indentSpaces / charactersPerInch);
		  break;
		}
		}
		break;
	 case 'J':
		switch((char)source->get())
		{
		case 'O':
		  traceWrite("JO == Justification On");
		  writer->justify();
		  break;
		}
		break;
	 case 'L':
		switch((char)source->get())
		{
		case 'M':
		  traceWrite("LM == Left Margin");
		  leftMargin = ((float)convertInteger()) / charactersPerInch;
		  writer->leftMargin(leftMargin);
		  break;
		case 'L':
		{
		  traceWrite("LL == Line Length");
		  float  lineLength = (float)convertInteger();
		  writer->rightMargin(pageWidth -
									 (leftMargin + (lineLength / charactersPerInch)));
		  break;
		}
		case 'LS':
		  traceWrite("LS == Line spacing, ignored");
		  break;
		}
		break;
	 case 'N':
		switch((char)source->get())
		{
		case 'J':
		  traceWrite("NJ == No Justification");
		  writer->leftJustify();
		  break;
		}
		break;
	 case 'O':
		switch((char)source->get())
		{
		case 'C':
		  traceWrite("OC == Output Control Code(s), ignored");
		  break;
		}
		break;
	 case 'P':
		switch((char)source->get())
		{
		case 'C':
		  traceWrite("PC == Define Pad Character");
		  padChar = (char)source->get();
		  break;
		case 'L':
		  traceWrite("PL == Page Length, ignored");
		  break;
		case 'N':
		  traceWrite("PN == Set page number, ignored");
		  break;
		case 'P':
		  traceWrite("PP == Print page number, ignored");
		  break;
		}
		break;
	 case 'S':
		switch((char)source->get())
		{
		case 'S':
		  traceWrite("SS == Single Spacing, ignored");
		  break;
		case 'P':
		{
		  traceWrite("SP == Space with blank lines");
		  int  blankLines = convertInteger();
		  while (blankLines > 0)
		  {
			 writer->endParagraph();
			 blankLines--;
		  }
		  break;
		}
		}
		break;
	 case 'T':
		switch((char)source->get())
		{
		case 'I':
		{
		  traceWrite("TI == Temporary indent");
		  float  indentSpaces = (float)convertInteger();
		  writer->firstLineIndent(indentSpaces / charactersPerInch);
		  break;
		}
		case 'S':
		{
		  traceWrite("TS == Top Space");
		  float  marginLines = (float)convertInteger();
		  writer->topMargin(marginLines / linesPerInch);
		  break;
		}
		}
		break;
	 }  // End of switch ((char)inputInt)
  }  // End of while ((EOF != (inputInt = source->get())) &&
}

