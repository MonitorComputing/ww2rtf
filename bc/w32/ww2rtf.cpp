//**********************************************************************
//                                                                     *
//    Filename:      ww2rtf.cpp                                        *
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

#include <dir.h>
#include <stdlib.h>
#include <string.h>

#include <classlib\arrays.h>
#include <owl\applicat.h>
#include <owl\edit.h>
#include <owl\framewin.h>
#include <owl\inputdia.h>
#include <owl\opensave.h>
#include <owl\owlpch.h>
#include <owl\scroller.h>

#include "ww2rtf.rc"
#include "monrtfwr.h"
#include "monwwrd.h"

class TMyWindow : public TWindow
{
  public:
     TMyWindow(TWindow *parent = 0);
     virtual  ~TMyWindow();

  protected:
     void  CmFileOpen();
     void  CmFileDirectory();
     void  CmFileExit();
     void  CmAbout();
     DECLARE_RESPONSE_TABLE(TMyWindow);

     void  ConvertFile(const char*    fileName, ifstream&    fileStream);
     void  OpenFile();
     void  OpenDirectory();

     static void  traceConversionCb(void  *traceObj, const char  *traceText);
     void         traceConversion(const char  *traceText);

     TEdit                   *textArea;
     TOpenSaveDialog::TData  *fileData;
};

DEFINE_RESPONSE_TABLE1(TMyWindow,TWindow)
  EV_COMMAND(CM_FILEOPEN, CmFileOpen),
  EV_COMMAND(CM_FILEDIRECTORY, CmFileDirectory),
  EV_COMMAND(CM_FILEEXIT, CmFileExit),
  EV_COMMAND(CM_ABOUT, CmAbout),
END_RESPONSE_TABLE;


TMyWindow::TMyWindow(TWindow *parent)
{
    Init(parent, 0, 0);
    fileData = new TFileOpenDialog::TData(OFN_HIDEREADONLY|OFN_FILEMUSTEXIST,
                                          "Wordwise Files (*.BBC)|*.bbc|",
                                          0,
                                          "",
                                          "BBC");
    textArea = new TEdit(this, 0, "", 0, 0, Attr.W, Attr.H, 0, TRUE);
    textArea->SetReadOnly(TRUE);
    textArea->FormatLines(TRUE);
}


TMyWindow::~TMyWindow()
{
  delete fileData;
  delete textArea;
}


void
TMyWindow::CmFileOpen()
{
  if (TFileOpenDialog(this, *fileData).Execute() == IDOK)
  {
     OpenFile();
  }
}


void
TMyWindow::CmFileDirectory()
{
    if (TFileOpenDialog(this, *fileData).Execute() == IDOK)
    {
        OpenDirectory();
    }
}


void
TMyWindow::CmFileExit()
{
EvClose();
//  CloseWindow();
}


void
TMyWindow::CmAbout()
{
    TDialog(this, IDD_ABOUT).Execute();
}


void
TMyWindow::ConvertFile(const char*    fileName, ifstream&    fileStream)
{
    MonRtfWriter       writer(fileName);
    MonWordWiseReader  reader(&fileStream, &writer, this, traceConversionCb);

    textArea->SetWindowPos(0, 0, 0, Attr.W, Attr.H, SWP_NOZORDER);
    textArea->Clear();
    reader.convert();
}



void
TMyWindow::OpenFile()
{
    ifstream  is(fileData->FileName, ios::in | ios::binary);

    if (!is)
    {
        MessageBox("Unable to open file",
                   "File Error",
                   MB_OK | MB_ICONEXCLAMATION);
    }
    else
    {
        ConvertFile(fileData->FileName, is);
        MessageBox(fileData->FileName,
                   "Converted file",
                   MB_OK);
        is.close();
    }
}


void
TMyWindow::OpenDirectory()
{
    const char    dirSepChar = '\\';


    if (0 != strchr(fileData->FileName, dirSepChar))
    {
        char*    fileName = strchr(fileData->FileName, '\0');


        while (*fileName != dirSepChar)
        {
            *fileName = '\0';
            --fileName;
        }

        ++fileName;
        strcpy(fileName, "*.bbc");


        ffblk    findBlock;


        if (0 == findfirst(fileData->FileName, &findBlock, 0))
        {
            do
            {
                ifstream    is(findBlock.ff_name, ios::in | ios::binary);

                if (is)
                {
                    ConvertFile(findBlock.ff_name, is);
                }

                is.close();

            } while (0 == findnext(&findBlock));

            MessageBox(fileData->FileName,
                       "Converted files",
                       MB_OK);
        }
    }
}



void
TMyWindow::traceConversionCb(void  *traceObj, const char  *traceText)
{
  if (0 != traceObj)
  {
     ((TMyWindow*)traceObj)->traceConversion(traceText);
  }
}


void
TMyWindow::traceConversion(const char  *traceText)
{
  textArea->Insert(traceText);
}


class TMyApp : public TApplication {
  public:
     TMyApp() : TApplication() {}

     void InitMainWindow()
     {
        SetMainWindow(new TFrameWindow(0,
                                                 "Wordwise to RTF filter",
                                                 new TMyWindow));
        GetMainWindow()->AssignMenu("COMMANDS");
     }
};


int OwlMain(int /*argc*/, char* /*argv*/ [])
{
  return TMyApp().Run();
}
