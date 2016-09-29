#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/fl_draw.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Slider.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Secret_Input.H>
#include <FL/fl_ask.H>

#include "SLF.h"
#include "Grahpics.h"
#include "DownloadManager.h"
#include "RegistrationWindow.h"
#include "LoginWindow.h"
#include "MainWindow.h"
#include "StockDatabase.h"

#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

#include "Profile.h"
#include "Calendar.h"

int main()
{
	LoginWindow* t = new LoginWindow("LOGIN!");

	return Fl::run();

}