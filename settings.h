#pragma once

#define DEFAULTSETTING_MEMSTART    0x00000000
#define DEFAULTSETTING_MEMSIZE     0x00400000
#define DEFAULTSETTING_MEMSEGMENTS 1

extern int settings_memstart;
extern int settings_memsize;
extern int settings_memsegments;

class Settings : public wxFrame
{
	private:

	protected:
		wxStaticText* m_SettingsElem_LabelMemSize;
		wxSpinCtrl* m_SettingsElem_SpinMemSize;
		wxStaticText* m_SettingsElem_LabelMemSegments;
		wxSpinCtrl* m_SettingsElem_SpinMemSegments;
		wxButton* m_SettingsElem_CloseButton;
		void m_SettingsElem_ButtonCloseOnButtonClick(wxCommandEvent& event);
		void m_SettingsElem_SpinMemSizeOnSpinCtrl(wxSpinEvent& event);
		void m_SettingsElem_SpinMemSegmentsOnSpinCtrl(wxSpinEvent& event);

	public:

		Settings( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~Settings();

};