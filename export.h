#pragma once

#include <utility>

typedef struct IUnknown IUnknown;
#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/spinctrl.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/sizer.h>
#include <wx/dialog.h>
#include <wx/msgdlg.h>
#include <wx/dcbuffer.h>
#include <wx/filedlg.h>
#include <wx/rawbmp.h>

class Export : public wxDialog
{
	private:
		int imagewidth;
		int imageheight;

	protected:
		wxStaticText* m_Label_Width;
		wxStaticText* m_Label_Height;
		wxSpinCtrl* m_SpinCtrl_Width;
		wxSpinCtrl* m_SpinCtrl_Height;
		wxButton* m_Button_Export;
		wxButton* m_Button_Cancel;

	public:
		Export(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Image Export"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE);
		~Export();
		void m_SpinCtrl_WidthOnSpinCtrl(wxSpinEvent& event);
		void m_SpinCtrl_HeightOnSpinCtrl(wxSpinEvent& event);
		void m_Button_ExportOnButtonClick(wxCommandEvent& event);
		void m_Button_CancelOnButtonClick(wxCommandEvent& event);
		void ShowExport();
};