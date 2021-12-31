#include "app.h"

wxIMPLEMENT_APP(App);

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
	m_ProgramFrame = new Main();
	m_ProgramFrame->SetIcon(wxIcon(wxT("resources/prog.ico"), wxBITMAP_TYPE_ICO));
	m_ProgramFrame->Show();
	SetTopWindow(m_ProgramFrame);
	return true;
}