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
#include <wx/filedlg.h>
#include <wx/rawbmp.h>

#define PROGRAM_NAME "MemMapper"

class Main : public wxFrame
{
	private:
		std::list<void*> list_Items;
		void FixItemMoverButtons();

	protected:
		wxSplitterWindow* m_ProgramSplitter;
		wxScrolledWindow* m_ItemsScrollList;
		wxBoxSizer* m_ItemsSizer;
		wxPanel* m_ItemPanel;
		wxPanel* m_DrawPanel;
		wxMenuBar* m_MenuBar;
		wxMenu* m_MenuBarElem_File;
		wxMenuItem* m_MenuBarItem_New;
		wxMenuItem* m_MenuBarItem_Open;
		wxMenuItem* m_MenuBarItem_Save;
		wxMenuItem* m_MenuBarItem_SaveAs;
		wxMenuItem* m_MenuBarItem_Export;
		wxMenu* m_MenuBarElem_Memory;
		wxMenuItem* m_MenuBarItem_NewItem;
		wxMenuItem* m_MenuBarItem_Preferences;
		wxToolBar* m_ToolBar;
		wxToolBarToolBase* m_ToolBarElem_New;
		wxToolBarToolBase* m_ToolBarElem_Open;
		wxToolBarToolBase* m_ToolBarElem_Save;
		wxToolBarToolBase* m_ToolBarElem_Export;
		wxToolBarToolBase* m_ToolBarElem_NewItem;
		wxToolBarToolBase* m_ToolBarElem_Preferences;
		wxToolBarToolBase* m_ToolBarElem_Undo;
		wxToolBarToolBase* m_ToolBarElem_Redo;
		void m_ProgramSplitterOnIdle(wxIdleEvent&);
		void m_ToolBarElem_NewOnToolClicked(wxCommandEvent& event);
		void m_ToolBarElem_OpenOnToolClicked(wxCommandEvent& event);
		void m_ToolBarElem_SaveOnToolClicked(wxCommandEvent& event);
		void m_ToolBarElem_SaveAsOnToolClicked(wxCommandEvent& event);
		void m_ToolBarElem_ExportOnToolClicked(wxCommandEvent& event);
		void m_ToolBarElem_NewItemOnToolClicked(wxCommandEvent& event);
		void m_ToolBarElem_PreferencesOnToolClicked(wxCommandEvent& event);
		void m_ProgramSplitterOnSplitterDClick(wxSplitterEvent& event);
		void m_ProgramSplitterOnSplitterUnsplit(wxSplitterEvent& event);
		void m_DrawPanelOnPaint(wxPaintEvent& event);

	public:
		Main();
		~Main();
		std::list<void*>* GetItemList();
		void  ResetProgram();
		void* NewItem();
		void  MoveUpItem(void* item);
		void  MoveDownItem(void* item);
		void  RemoveItem(void* item);
		void  SaveFile(bool newfile);
		void  RefreshDrawing();
		void  Paint(wxDC* dc, wxSize framesize);
};
