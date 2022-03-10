#include "main.h"
#include "settings.h"

int settings_memstart    = 0x00000000;
int settings_memsize     = 0x00400000;
int settings_memsegments = 1;

Settings::Settings( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	this->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENU));

	// Create the sizers to hold our elements
	wxBoxSizer* m_SettingsElem_Sizer0;
	m_SettingsElem_Sizer0 = new wxBoxSizer(wxVERTICAL);
	wxGridSizer* m_SettingsElem_Sizer1;
	m_SettingsElem_Sizer1 = new wxGridSizer(0, 2, 0, 0);

	// Memory size label and spin control
	m_SettingsElem_LabelMemSize = new wxStaticText(this, wxID_ANY, wxT("Memory Size"), wxDefaultPosition, wxDefaultSize, 0);
	m_SettingsElem_LabelMemSize->Wrap(-1);
	m_SettingsElem_Sizer1->Add(m_SettingsElem_LabelMemSize, 0, wxALL, 5);
	m_SettingsElem_SpinMemSize = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 0x7FFFFFFF, settings_memsize);
	m_SettingsElem_SpinMemSize->SetBase(16);
	m_SettingsElem_Sizer1->Add(m_SettingsElem_SpinMemSize, 0, wxALL, 5);

	// Memory segments label and spin control
	m_SettingsElem_LabelMemSegments = new wxStaticText(this, wxID_ANY, wxT("Memory Segments"), wxDefaultPosition, wxDefaultSize, 0);
	m_SettingsElem_LabelMemSegments->Wrap(-1);
	m_SettingsElem_Sizer1->Add(m_SettingsElem_LabelMemSegments, 0, wxALL, 5);
	m_SettingsElem_SpinMemSegments = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 0x7FFFFFFF, settings_memsegments);
	m_SettingsElem_Sizer1->Add(m_SettingsElem_SpinMemSegments, 0, wxALL, 5);

	// Add all the options to the first sizer
	m_SettingsElem_Sizer0->Add(m_SettingsElem_Sizer1, 1, wxEXPAND, 5);

	// Add the close button
	m_SettingsElem_CloseButton = new wxButton(this, wxID_ANY, wxT("Close"), wxDefaultPosition, wxDefaultSize, 0);
	m_SettingsElem_Sizer0->Add(m_SettingsElem_CloseButton, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	// Add events
	this->m_SettingsElem_CloseButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Settings::m_SettingsElem_ButtonCloseOnButtonClick), NULL, this);
	this->m_SettingsElem_SpinMemSize->Connect(wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler(Settings::m_SettingsElem_SpinMemSizeOnSpinCtrl), NULL, this);
	this->m_SettingsElem_SpinMemSize->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxSpinEventHandler(Settings::m_SettingsElem_SpinMemSizeOnSpinCtrl), NULL, this);
	this->m_SettingsElem_SpinMemSegments->Connect(wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler(Settings::m_SettingsElem_SpinMemSegmentsOnSpinCtrl), NULL, this);
	this->m_SettingsElem_SpinMemSegments->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxSpinEventHandler(Settings::m_SettingsElem_SpinMemSizeOnSpinCtrl), NULL, this);

	// Initialize the rest of the frame
	this->SetSizer(m_SettingsElem_Sizer0);
	this->Layout();
	m_SettingsElem_Sizer0->Fit(this);
	this->Centre(wxBOTH);
}

Settings::~Settings()
{
	this->m_SettingsElem_CloseButton->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Settings::m_SettingsElem_ButtonCloseOnButtonClick), NULL, this);
	this->m_SettingsElem_SpinMemSize->Disconnect(wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler(Settings::m_SettingsElem_SpinMemSizeOnSpinCtrl), NULL, this);
	this->m_SettingsElem_SpinMemSize->Disconnect(wxEVT_COMMAND_TEXT_UPDATED, wxSpinEventHandler(Settings::m_SettingsElem_SpinMemSizeOnSpinCtrl), NULL, this);
	this->m_SettingsElem_SpinMemSegments->Disconnect(wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler(Settings::m_SettingsElem_SpinMemSegmentsOnSpinCtrl), NULL, this);
	this->m_SettingsElem_SpinMemSegments->Disconnect(wxEVT_COMMAND_TEXT_UPDATED, wxSpinEventHandler(Settings::m_SettingsElem_SpinMemSegmentsOnSpinCtrl), NULL, this);
}

void Settings::m_SettingsElem_SpinMemSizeOnSpinCtrl(wxSpinEvent& event)
{
	settings_memsize = this->m_SettingsElem_SpinMemSize->GetValue();
	((Main*)this->GetParent())->RefreshDrawing();
}

void Settings::m_SettingsElem_SpinMemSegmentsOnSpinCtrl(wxSpinEvent& event)
{
	settings_memsegments = this->m_SettingsElem_SpinMemSegments->GetValue();
	((Main*)this->GetParent())->RefreshDrawing();
}

void Settings::m_SettingsElem_ButtonCloseOnButtonClick(wxCommandEvent& event)
{
	delete this; // Commit sudoku
}
