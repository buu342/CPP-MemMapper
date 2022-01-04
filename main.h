#pragma once

#include <list>
#include <iterator>

typedef struct IUnknown IUnknown;
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
#include <wx/scrolwin.h>
#include <wx/splitter.h>
#include <wx/menu.h>
#include <wx/toolbar.h>
#include <wx/frame.h>
#include <wx/msgdlg.h>
#include <wx/dcbuffer.h>

class Main : public wxFrame
{
	private:
		int mem_start;
		int mem_end;
		std::list<void*> list_Items;
		void FixItemMoverButtons();

	protected:
		wxSplitterWindow* m_ProgramSplitter;
		wxScrolledWindow* m_ItemsScrollList;
		wxPanel* m_ItemPanel;
		wxStaticText* m_ItemElem_LabelName;
		wxTextCtrl* m_ItemElem_InputName;
		wxBitmapButton* m_ItemElem_ButtonFontColor;
		wxBitmapButton* m_ItemElem_ButtonColor;
		wxStaticText* m_ItemElem_LabelAlpha;
		wxSlider* m_ItemElem_SliderAlpha;
		wxStaticText* m_ItemElem_LabelStart;
		wxSpinCtrl* m_ItemElem_SpinStart;
		wxStaticText* m_ItemElem_LabelEnd;
		wxSpinCtrl* m_ItemElem_SpinEnd;
		wxBitmapButton* m_ItemElem_ButtonUp;
		wxBitmapButton* m_ItemElem_ButtonDown;
		wxBitmapButton* m_ItemElem_ButtonDelete;
		wxPanel* m_DrawPanel;
		wxMenuBar* m_MenuBar;
		wxMenu* m_MenuBarElem_File;
		wxToolBar* m_ToolBar;
		wxToolBarToolBase* m_ToolBarElem_New;
		wxToolBarToolBase* m_ToolBarElem_Open;
		wxToolBarToolBase* m_ToolBarElem_Save;
		wxToolBarToolBase* m_ToolBarElem_NewItem;
		wxToolBarToolBase* m_ToolBarElem_Undo;
		wxToolBarToolBase* m_ToolBarElem_Redo;
		wxBoxSizer* m_ItemsSizer;
		void m_ProgramSplitterOnIdle(wxIdleEvent&);
		void m_ToolBarElem_NewItemOnToolClicked(wxCommandEvent& event);
		void m_ProgramSplitterOnSplitterDClick(wxSplitterEvent& event);
		void m_ProgramSplitterOnSplitterUnsplit(wxSplitterEvent& event);
		void m_DrawPanelOnPaint(wxPaintEvent& event);

	public:
		Main();
		~Main();
		std::list<void*>* GetItemList();
		void MoveUpItem(void* item);
		void MoveDownItem(void* item);
		void RemoveItem(void* item);
		void RefreshDrawing();
};
