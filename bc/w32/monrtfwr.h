#ifndef _MONRTFWR_H_INCLUDED_
#define _MONRTFWR_H_INCLUDED_
//**********************************************************************
//                                                                     *
//    Filename:	     monrtfwr.h                                        *
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

#include "mondocwr.h"


class MonRtfWriter : public MonDocWriter
{
public:

  MonRtfWriter(const char  *inFileName);
  virtual ~MonRtfWriter();

  virtual void  Begin();
  virtual void  leftMargin(float  inches);
  virtual void  rightMargin(float  inches);
  virtual void  topMargin(float  inches);
  virtual void  bottomMargin(float  inches);
  virtual void  leftIndent(float  inches);
  virtual void  firstLineIndent(float  inches);
  virtual void  write(char  charToWrite);
  virtual void  writeHardSpace();
  virtual void  justify();
  virtual void  leftJustify();
  virtual void  endParagraph();
  virtual void  endPage()	;
  virtual void  End();

protected:

  class ofstream      *output;
  static const float  twipsPerInch;
};


#endif
