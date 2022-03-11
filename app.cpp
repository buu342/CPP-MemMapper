#include "app.h"

// Icons
#include "resources/icon_prog.h"
#include "resources/icon_new.h"
#include "resources/icon_open.h"
#include "resources/icon_save.h"
#include "resources/icon_export.h"
#include "resources/icon_newmem.h"
#include "resources/icon_preferences.h"	
#include "resources/icon_font.h"
#include "resources/icon_fill.h"
#include "resources/icon_up.h"
#include "resources/icon_up_disabled.h"
#include "resources/icon_down.h"
#include "resources/icon_down_disabled.h"
#include "resources/icon_delete.h"

wxIMPLEMENT_APP(App);

wxIcon   iconbm_prog = wxNullIcon;
wxBitmap iconbm_new = wxNullBitmap;
wxBitmap iconbm_open = wxNullBitmap;
wxBitmap iconbm_save = wxNullBitmap;
wxBitmap iconbm_export = wxNullBitmap;
wxBitmap iconbm_newmem = wxNullBitmap;
wxBitmap iconbm_preferences = wxNullBitmap;
wxBitmap iconbm_font = wxNullBitmap;
wxBitmap iconbm_fill = wxNullBitmap;
wxBitmap iconbm_up = wxNullBitmap;
wxBitmap iconbm_up_disabled = wxNullBitmap;
wxBitmap iconbm_down = wxNullBitmap;
wxBitmap iconbm_down_disabled = wxNullBitmap;
wxBitmap iconbm_delete = wxNullBitmap;

App::App()
{
	// Nothing
}

App::~App()
{
	// Nothing
}

bool App::OnInit()
{
	if (!wxApp::OnInit())
		return false;
	wxInitAllImageHandlers();
	wxBitmap temp = wxBITMAP_PNG_FROM_DATA(icon_prog);
	iconbm_prog.CopyFromBitmap(temp);
	iconbm_new = wxBITMAP_PNG_FROM_DATA(icon_new);
	iconbm_open = wxBITMAP_PNG_FROM_DATA(icon_open);
	iconbm_save = wxBITMAP_PNG_FROM_DATA(icon_save);
	iconbm_export = wxBITMAP_PNG_FROM_DATA(icon_export);
	iconbm_newmem = wxBITMAP_PNG_FROM_DATA(icon_newmem);
	iconbm_preferences = wxBITMAP_PNG_FROM_DATA(icon_preferences);
	iconbm_font = wxBITMAP_PNG_FROM_DATA(icon_font);
	iconbm_fill = wxBITMAP_PNG_FROM_DATA(icon_fill);
	iconbm_up = wxBITMAP_PNG_FROM_DATA(icon_up);
	iconbm_up_disabled = wxBITMAP_PNG_FROM_DATA(icon_up_disabled);
	iconbm_down = wxBITMAP_PNG_FROM_DATA(icon_down);
	iconbm_down_disabled = wxBITMAP_PNG_FROM_DATA(icon_down_disabled);
	iconbm_delete = wxBITMAP_PNG_FROM_DATA(icon_delete);
	m_ProgramFrame = new Main();
	m_ProgramFrame->SetIcon(iconbm_prog);
	m_ProgramFrame->Show();
	SetTopWindow(m_ProgramFrame);
	return true;
}