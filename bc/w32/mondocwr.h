#ifndef _MONDOCWR_H_INCLUDED_
#define _MONDOCWR_H_INCLUDED_
//**********************************************************************
//                                                                     *
//    Filename:	     mondocwr.h                                        *
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

class MonDocWriter
{
public:

  virtual  ~MonDocWriter() {;}

  virtual void  Begin() = 0;
  virtual void  leftMargin(float  inches) = 0;
  virtual void  rightMargin(float  inches) = 0;
  virtual void  topMargin(float  inches) = 0;
  virtual void  bottomMargin(float  inches) = 0;
  virtual void  leftIndent(float  inches) = 0;
  virtual void  firstLineIndent(float  inches) = 0;
  virtual void  write(char  charToWrite) = 0;
  virtual void  writeHardSpace() = 0;
  virtual void  justify() = 0;
  virtual void  leftJustify() = 0;
  virtual void  endParagraph() = 0;
  virtual void  endPage() = 0;
  virtual void  End() = 0;

protected:

  MonDocWriter() {;}
  MonDocWriter(MonDocWriter&) {;}
  MonDocWriter(MonDocWriter*) {;}
};


#endif
