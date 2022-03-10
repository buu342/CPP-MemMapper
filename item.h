#pragma once

#include <list>
#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/bmpbuttn.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/slider.h>
#include <wx/spinctrl.h>
#include <wx/panel.h>
#include <wx/colordlg.h>

class Item : public wxPanel
{
	private:
		Main*   instance;
		int     col_alpha;
		wxColor col_back;
		wxColor col_text;

	protected:
		wxStaticText* m_ItemElem_LabelName;
		wxTextCtrl* m_ItemElem_InputName;
		wxBitmapButton* m_ItemElem_ButtonFontColor;
		wxBitmapButton* m_ItemElem_ButtonColor;
		wxStaticText* m_ItemElem_LabelAlpha;
		wxSlider* m_ItemElem_SliderAlpha;
		wxStaticText* m_ItemElem_LabelStart;
		wxSpinCtrl* m_ItemElem_SpinStart;
		wxStaticText* m_ItemElem_LabelLength;
		wxSpinCtrl* m_ItemElem_SpinLength;
		wxBitmapButton* m_ItemElem_ButtonUp;
		wxBitmapButton* m_ItemElem_ButtonDown;
		wxBitmapButton* m_ItemElem_ButtonDelete;
		void m_ItemElem_ButtonUpOnButtonClick(wxCommandEvent& event);
		void m_ItemElem_ButtonDownOnButtonClick(wxCommandEvent& event);
		void m_ItemElem_ButtonDeleteOnButtonClick(wxCommandEvent& event);
		void m_ItemElem_ButtonColorOnButtonClick(wxCommandEvent& event);
		void m_ItemElem_InputNameOnText(wxCommandEvent& event);
		void m_ItemElem_SliderAlphaOnSlider(wxCommandEvent& event);
		void m_ItemElem_SpinStartOnSpinCtrl(wxSpinEvent& event);
		void m_ItemElem_SpinLengthOnSpinCtrl(wxSpinEvent& event);

	public:
		Item(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(-1,-1), long style = wxBORDER_SIMPLE|wxTAB_TRAVERSAL|wxEXPAND, const wxString& name = wxEmptyString);
		~Item();
		void SetInstance(Main* instance);
		void SetUpButtonState(bool enabled);
		void SetDownButtonState(bool enabled);
		void SetName(wxString name);
		void SetMemStart(int start);
		void SetMemLength(int length);
		void SetMemEnd(int end);
		void SetBackColor(wxColor clr);
		void SetFontColor(wxColor clr);
		void SetAlpha(int alpha);
		wxString GetName();
		int GetMemStart();
		int GetMemLength();
		int GetMemEnd();
		wxColor GetBackColor();
		wxColor GetFontColor();
		int GetAlpha();
};
