#include <string.h>
#include <fstream>
#include "main.h"
#include "item.h"
#include "settings.h"
#include "json.hpp"


/*********************************
              Macros
*********************************/

#define DEFAULT_SASH_POS 346


/*********************************
             Globals
*********************************/

std::string savePath = "";


/*********************************
           Constructors
*********************************/

Main::Main() : wxFrame(nullptr, wxID_ANY, PROGRAM_NAME, wxPoint(0, 0), wxSize(910, 700), wxDEFAULT_FRAME_STYLE)
{
	// Initialize the window
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	// Add the window splitter with a scroll bar
	wxBoxSizer*m_ProgramSizer = new wxBoxSizer(wxVERTICAL);
	this->m_ProgramSplitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D|wxSP_LIVE_UPDATE|wxSP_NO_XP_THEME);
	this->m_ProgramSplitter->Connect(wxEVT_IDLE, wxIdleEventHandler(Main::m_ProgramSplitterOnIdle), NULL, this);
	this->m_ProgramSplitter->SetMinSize(wxSize(DEFAULT_SASH_POS, -1));
	this->m_ItemsScrollList = new wxScrolledWindow(this->m_ProgramSplitter, wxID_ANY, wxDefaultPosition, wxSize(DEFAULT_SASH_POS, -1), wxVSCROLL);
	this->m_ItemsScrollList->SetScrollRate(0, 5);

	// Add the sizer for all of our items
	this->m_ItemsSizer = new wxBoxSizer(wxVERTICAL);
	this->m_ItemsScrollList->SetSizer(this->m_ItemsSizer);
	this->m_ItemsScrollList->Layout();
	this->m_ItemsSizer->Fit(m_ItemsScrollList);

	// Create the panel for drawing
	this->m_DrawPanel = new wxPanel(this->m_ProgramSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL|wxFULL_REPAINT_ON_RESIZE);
	this->m_DrawPanel->SetBackgroundStyle(wxBG_STYLE_PAINT);
	this->m_DrawPanel->Layout();

	// Enable the split
	this->m_ProgramSplitter->SplitVertically(this->m_ItemsScrollList, m_DrawPanel, DEFAULT_SASH_POS);
	m_ProgramSizer->Add(this->m_ProgramSplitter, 1, wxEXPAND, 5);
	this->SetSizer(m_ProgramSizer);
	this->Layout();

	// Add the menu bar
	this->m_MenuBar = new wxMenuBar(0);
	this->m_MenuBarElem_File = new wxMenu();
	this->m_MenuBarItem_New = new wxMenuItem(m_MenuBarElem_File, wxID_ANY, wxString(wxT("New")) + wxT('\t') + wxT("Ctrl+N"), wxEmptyString, wxITEM_NORMAL);
	this->m_MenuBarElem_File->Append(m_MenuBarItem_New);
	this->m_MenuBarItem_Open = new wxMenuItem(m_MenuBarElem_File, wxID_ANY, wxString(wxT("Open")) + wxT('\t') + wxT("Ctrl+O"), wxEmptyString, wxITEM_NORMAL);
	this->m_MenuBarElem_File->Append(m_MenuBarItem_Open);
	this->m_MenuBarItem_Save = new wxMenuItem(m_MenuBarElem_File, wxID_ANY, wxString(wxT("Save")) + wxT('\t') + wxT("Ctrl+S"), wxEmptyString, wxITEM_NORMAL);
	this->m_MenuBarElem_File->Append(m_MenuBarItem_Save);
	this->m_MenuBarItem_SaveAs = new wxMenuItem(m_MenuBarElem_File, wxID_ANY, wxString(wxT("Save As")) + wxT('\t') + wxT("Ctrl+Shift+S"), wxEmptyString, wxITEM_NORMAL);
	this->m_MenuBarElem_File->Append(m_MenuBarItem_SaveAs);
	this->m_MenuBarElem_File->AppendSeparator();
	this->m_MenuBarItem_Export = new wxMenuItem(m_MenuBarElem_File, wxID_ANY, wxString(wxT("Export Image")) + wxT('\t') + wxT("Ctrl+E"), wxEmptyString, wxITEM_NORMAL);
	this->m_MenuBarElem_File->Append(m_MenuBarItem_Export);
	this->m_MenuBar->Append(this->m_MenuBarElem_File, wxT("File"));
	this->m_MenuBarElem_Memory = new wxMenu();
	this->m_MenuBarItem_NewItem = new wxMenuItem(m_MenuBarElem_Memory, wxID_ANY, wxString(wxT("New Memory Block")) + wxT('\t') + wxT("Ctrl+M"), wxEmptyString, wxITEM_NORMAL);
	this->m_MenuBarElem_Memory->Append(m_MenuBarItem_NewItem);
	this->m_MenuBarElem_Memory->AppendSeparator();
	this->m_MenuBarItem_Preferences = new wxMenuItem(m_MenuBarElem_Memory, wxID_ANY, wxString(wxT("Preferences")) + wxT('\t') + wxT("Ctrl+P"), wxEmptyString, wxITEM_NORMAL);
	this->m_MenuBarElem_Memory->Append(m_MenuBarItem_Preferences);
	this->m_MenuBar->Append(this->m_MenuBarElem_Memory, wxT("Memory"));
	this->SetMenuBar(this->m_MenuBar);

	// Add the tool bar
	this->m_ToolBar = this->CreateToolBar(wxTB_HORIZONTAL|wxTB_FLAT, wxID_ANY);
	this->m_ToolBarElem_New = this->m_ToolBar->AddTool(wxID_ANY, wxT("New project"), iconbm_new, wxNullBitmap, wxITEM_NORMAL, wxT("Create a new project"), wxEmptyString, NULL);
	this->m_ToolBarElem_Open = this->m_ToolBar->AddTool(wxID_ANY, wxT("Open project"), iconbm_open, wxNullBitmap, wxITEM_NORMAL, wxT("Load a project"), wxEmptyString, NULL);
	this->m_ToolBarElem_Save = this->m_ToolBar->AddTool(wxID_ANY, wxT("Save project"), iconbm_save, wxNullBitmap, wxITEM_NORMAL, wxT("Save this project"), wxEmptyString, NULL);
	this->m_ToolBarElem_Export = this->m_ToolBar->AddTool(wxID_ANY, wxT("Export image"), iconbm_export, wxNullBitmap, wxITEM_NORMAL, wxT("Export the memory map as an image"), wxEmptyString, NULL);
	this->m_ToolBar->AddSeparator();
	this->m_ToolBarElem_NewItem = this->m_ToolBar->AddTool(wxID_ANY, wxT("New memory block"), iconbm_newmem, wxNullBitmap, wxITEM_NORMAL, wxT("Create a new memory block"), wxEmptyString, NULL);
	this->m_ToolBar->AddSeparator();
	this->m_ToolBarElem_Preferences = this->m_ToolBar->AddTool(wxID_ANY, wxT("Preferences"), iconbm_preferences, wxNullBitmap, wxITEM_NORMAL, wxT("Change memory map preferences"), wxEmptyString, NULL);
	this->m_ToolBar->Realize();

	// Create the shortcuts
	wxAcceleratorEntry entries[7];
	entries[0].Set(wxACCEL_CTRL, WXK_CONTROL_N, this->m_MenuBarItem_New->GetId());
	entries[1].Set(wxACCEL_CTRL, WXK_CONTROL_O, this->m_MenuBarItem_Open->GetId());
	entries[2].Set(wxACCEL_CTRL, WXK_CONTROL_S, this->m_MenuBarItem_Save->GetId());
	entries[3].Set(wxACCEL_CTRL|wxACCEL_SHIFT, WXK_CONTROL_S, this->m_MenuBarItem_SaveAs->GetId());
	entries[4].Set(wxACCEL_CTRL, WXK_CONTROL_E, this->m_MenuBarItem_Export->GetId());
	entries[5].Set(wxACCEL_CTRL, WXK_CONTROL_M, this->m_MenuBarItem_NewItem->GetId());
	entries[6].Set(wxACCEL_CTRL, WXK_CONTROL_P, this->m_MenuBarItem_Preferences->GetId());
	wxAcceleratorTable accel(7, entries);
	this->SetAcceleratorTable(accel);

	// Put the program in the middle of the screen
	this->Centre(wxBOTH);

	// Add event handlers
	this->m_ProgramSplitter->Connect(wxEVT_COMMAND_SPLITTER_DOUBLECLICKED, wxSplitterEventHandler(Main::m_ProgramSplitterOnSplitterDClick));
	this->m_ProgramSplitter->Connect(wxEVT_COMMAND_SPLITTER_UNSPLIT, wxSplitterEventHandler(Main::m_ProgramSplitterOnSplitterUnsplit), NULL, this);
	this->m_MenuBarElem_File->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Main::m_ToolBarElem_NewOnToolClicked), this, m_MenuBarItem_New->GetId());
	this->m_MenuBarElem_File->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Main::m_ToolBarElem_OpenOnToolClicked), this, m_MenuBarItem_Open->GetId());
	this->m_MenuBarElem_File->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Main::m_ToolBarElem_SaveOnToolClicked), this, m_MenuBarItem_Save->GetId());
	this->m_MenuBarElem_File->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Main::m_ToolBarElem_SaveAsOnToolClicked), this, m_MenuBarItem_SaveAs->GetId());
	this->m_MenuBarElem_File->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Main::m_ToolBarElem_ExportOnToolClicked), this, m_MenuBarItem_Export->GetId());
	this->m_MenuBarElem_Memory->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Main::m_ToolBarElem_NewItemOnToolClicked), this, m_MenuBarItem_NewItem->GetId());
	this->m_MenuBarElem_Memory->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Main::m_ToolBarElem_PreferencesOnToolClicked), this, m_MenuBarItem_Preferences->GetId());
	this->Connect(this->m_ToolBarElem_New->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(Main::m_ToolBarElem_NewOnToolClicked));
	this->Connect(this->m_ToolBarElem_Open->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(Main::m_ToolBarElem_OpenOnToolClicked));
	this->Connect(this->m_ToolBarElem_Save->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(Main::m_ToolBarElem_SaveOnToolClicked));
	this->Connect(this->m_ToolBarElem_Export->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(Main::m_ToolBarElem_ExportOnToolClicked));
	this->Connect(this->m_ToolBarElem_NewItem->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(Main::m_ToolBarElem_NewItemOnToolClicked));
	this->Connect(this->m_ToolBarElem_Preferences->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(Main::m_ToolBarElem_PreferencesOnToolClicked));
	this->m_DrawPanel->Connect(wxEVT_PAINT, wxPaintEventHandler(Main::m_DrawPanelOnPaint), NULL, this);
}

Main::~Main()
{
	this->m_ProgramSplitter->Disconnect(wxEVT_COMMAND_SPLITTER_DOUBLECLICKED, wxSplitterEventHandler(Main::m_ProgramSplitterOnSplitterDClick));
	this->m_ProgramSplitter->Disconnect(wxEVT_COMMAND_SPLITTER_UNSPLIT, wxSplitterEventHandler(Main::m_ProgramSplitterOnSplitterUnsplit), NULL, this);
	this->m_MenuBarElem_File->Unbind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Main::m_ToolBarElem_NewOnToolClicked), this, m_MenuBarItem_New->GetId());
	this->m_MenuBarElem_File->Unbind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Main::m_ToolBarElem_OpenOnToolClicked), this, m_MenuBarItem_Open->GetId());
	this->m_MenuBarElem_File->Unbind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Main::m_ToolBarElem_SaveOnToolClicked), this, m_MenuBarItem_Save->GetId());
	this->m_MenuBarElem_File->Unbind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Main::m_ToolBarElem_SaveAsOnToolClicked), this, m_MenuBarItem_SaveAs->GetId());
	this->m_MenuBarElem_File->Unbind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Main::m_ToolBarElem_ExportOnToolClicked), this, m_MenuBarItem_Export->GetId());
	this->m_MenuBarElem_Memory->Unbind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Main::m_ToolBarElem_NewItemOnToolClicked), this, m_MenuBarItem_NewItem->GetId());
	this->m_MenuBarElem_Memory->Unbind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(Main::m_ToolBarElem_PreferencesOnToolClicked), this, m_MenuBarItem_Preferences->GetId());
	this->Disconnect(this->m_ToolBarElem_New->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(Main::m_ToolBarElem_NewOnToolClicked));
	this->Disconnect(this->m_ToolBarElem_Open->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(Main::m_ToolBarElem_OpenOnToolClicked));
	this->Disconnect(this->m_ToolBarElem_Save->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(Main::m_ToolBarElem_SaveOnToolClicked));
	this->Disconnect(this->m_ToolBarElem_Export->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(Main::m_ToolBarElem_ExportOnToolClicked));
	this->Disconnect(this->m_ToolBarElem_NewItem->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(Main::m_ToolBarElem_NewItemOnToolClicked));
	this->Disconnect(this->m_ToolBarElem_Preferences->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(Main::m_ToolBarElem_PreferencesOnToolClicked));
	this->m_DrawPanel->Disconnect(wxEVT_PAINT, wxPaintEventHandler(Main::m_DrawPanelOnPaint), NULL, this);
}


/*********************************
          Event Handling
*********************************/

void Main::m_ToolBarElem_NewOnToolClicked(wxCommandEvent& event)
{
	wxMessageDialog dialog(this, "Unsaved changes will be lost. Continue?", "New Project", wxCENTER | wxNO_DEFAULT | wxYES_NO | wxICON_WARNING);

	// Do stuff based on the dialog answer
	switch (dialog.ShowModal())
	{
		case wxID_YES:
			this->ResetProgram();
			break;
		case wxID_NO:
			break;
	}
}

void Main::m_ToolBarElem_OpenOnToolClicked(wxCommandEvent& event)
{
	std::string progname;
	nlohmann::json file;
	wxMessageDialog dialog(this, "Unsaved changes will be lost. Continue?", "Load Project", wxCENTER | wxNO_DEFAULT | wxYES_NO | wxICON_WARNING);
	wxFileDialog fileDialogue(this, _("Load Memory Map"), "", "", "JSON files (*.json)|*.json", wxFD_OPEN);

	// If the user pressed "Yes"
	if (dialog.ShowModal() == wxID_YES)
	{
		// Ensure we didn't cancel the file opening dialog
		if (fileDialogue.ShowModal() == wxID_CANCEL)
			return;

		// We're good to reset the program
		this->ResetProgram();

		// Open the json file
		savePath = std::string(fileDialogue.GetPath().ToStdString());
		file = nlohmann::json::parse(std::ifstream(savePath));
		settings_memstart = file["Settings"]["Mem Start"];
		settings_memsize = file["Settings"]["Mem Length"];
		settings_memsegments = file["Settings"]["Mem Segments"];
		for (auto it = file["Items"].begin(); it != file["Items"].end(); ++it)
		{
			Item* elem = (Item*)this->NewItem();
			elem->SetName((*it)["Name"]);
			elem->SetMemStart((*it)["Start"]);
			elem->SetMemLength((*it)["Length"]);
			elem->SetBackColor(wxColor((*it)["Color"][0], (*it)["Color"][1], (*it)["Color"][2]));
			elem->SetFontColor(wxColor((*it)["TextColor"][0], (*it)["TextColor"][1], (*it)["TextColor"][2]));
			elem->SetAlpha((*it)["Alpha"]);
		}
		this->RefreshDrawing();

		// Update our program title
		progname = PROGRAM_NAME;
		progname.append(" - ");
		progname.append(savePath.substr(savePath.find_last_of("/\\") + 1));
		this->SetTitle(progname);
	}
}

void Main::m_ToolBarElem_SaveOnToolClicked(wxCommandEvent& event)
{
	this->SaveFile(false);
}

void Main::m_ToolBarElem_SaveAsOnToolClicked(wxCommandEvent& event)
{
	this->SaveFile(true);
}

void Main::m_ToolBarElem_ExportOnToolClicked(wxCommandEvent& event)
{
	wxFileDialog fileDialogue(this, _("Export Memory Map"), "", "", "PNG image (*.png)|*.png", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);

	// Ensure the user didn't cancel
	if (fileDialogue.ShowModal() == wxID_CANCEL)
		return;

	// Generate the image
	wxSize imgsize(512, 1024);
	wxBitmap image(imgsize, 32);
	wxMemoryDC dc(image);
	dc.SetBrush(*wxWHITE_BRUSH);
	this->Paint(&dc, imgsize);
	image.ConvertToImage().SaveFile(fileDialogue.GetPath(), wxBITMAP_TYPE_PNG);
}

void Main::m_ToolBarElem_NewItemOnToolClicked(wxCommandEvent& event)
{
	this->NewItem();
}

void Main::m_ToolBarElem_PreferencesOnToolClicked(wxCommandEvent& event)
{
	Settings* elem = new Settings(this);
	elem->Show();
}

void Main::m_ProgramSplitterOnIdle(wxIdleEvent& event)
{
	this->m_ProgramSplitter->SetSashPosition(DEFAULT_SASH_POS);
	this->m_ProgramSplitter->Disconnect(wxEVT_IDLE, wxIdleEventHandler(Main::m_ProgramSplitterOnIdle), NULL, this);
}

void Main::m_ProgramSplitterOnSplitterDClick(wxSplitterEvent& event)
{
	event.Veto();
}

void Main::m_ProgramSplitterOnSplitterUnsplit(wxSplitterEvent& event)
{
	event.Veto();
}

void Main::m_DrawPanelOnPaint(wxPaintEvent& event)
{
	wxBufferedPaintDC dc(this->m_DrawPanel);
	dc.SetBrush(wxSystemSettings::GetColour(wxSYS_COLOUR_APPWORKSPACE));
	this->Paint(&dc, this->m_DrawPanel->GetSize());
}


/*********************************
         Helper Functions
*********************************/

void Main::ResetProgram()
{
	this->SetTitle(PROGRAM_NAME);
	this->m_ProgramSplitter->SetSashPosition(DEFAULT_SASH_POS);

	// Set the program to defaults
	settings_memstart    = DEFAULTSETTING_MEMSTART;
	settings_memsize     = DEFAULTSETTING_MEMSIZE;
	settings_memsegments = DEFAULTSETTING_MEMSEGMENTS;

	// Remove all the items
	while (this->list_Items.size() > 0)
	{
		Item* it = (Item*)*this->list_Items.begin();
		this->RemoveItem(it);
		delete it;
	}

	// Refresh the layout
	this->m_ItemsSizer->Layout();
	this->RefreshDrawing();

	// Reset the save path
	savePath = "";
}

void* Main::NewItem()
{
	Item* it = new Item(this->m_ItemsScrollList);
	it->SetInstance(this);
	this->list_Items.push_back(it);
	this->m_ItemsSizer->Add(it, 1, wxALL|wxEXPAND, 5);

	// Refresh the sizers and the buttons
	this->m_ItemsSizer->FitInside(this->m_ItemsScrollList);
	this->m_ItemsScrollList->Layout();
	this->FixItemMoverButtons();
	return it;
}

void Main::MoveUpItem(void* item)
{
	int index_cur = 0;
	std::list<void*>::iterator it = this->list_Items.begin();
	std::list<void*>::iterator prev = it;

	// Find the element we want to swap
	do
	{
		Item* elem = (Item*)*it;

		// If we want to swap this
		if (elem == (Item*)item)
		{
			int index_prev = index_cur-1;

			// Perform the swap
			std::swap(*it, *prev);
			this->m_ItemsSizer->Detach(index_cur);
			this->m_ItemsSizer->Insert(index_cur, (Item*)*it, 1, wxALL|wxEXPAND, 5);
			this->m_ItemsSizer->Detach(index_prev);
			this->m_ItemsSizer->Insert(index_prev, (Item*)*prev, 1, wxALL|wxEXPAND, 5);

			// Refresh the sizers and the buttons
			this->m_ItemsSizer->Layout();
			this->m_ItemsScrollList->Layout();
			this->FixItemMoverButtons();
			return;
		}

		// Otherwise, move to the next element
		prev = it;
		it = std::next(it);
		index_cur++;
	}
	while(it != this->list_Items.end());
}

void Main::MoveDownItem(void* item)
{
	int index_cur = 0;
	std::list<void*>::iterator it = this->list_Items.begin();

	// Find the element we want to swap
	do
	{
		Item* elem = (Item*)*it;

		// If we want to swap this
		if (elem == (Item*)item)
		{
			std::list<void*>::iterator next = std::next(it);
			int index_next = index_cur+1;

			// Perform the swap
			std::swap(*it, *next);
			this->m_ItemsSizer->Detach(index_cur);
			this->m_ItemsSizer->Insert(index_cur, (Item*)*it, 1, wxALL|wxEXPAND, 5);
			this->m_ItemsSizer->Detach(index_next);
			this->m_ItemsSizer->Insert(index_next, (Item*)*next, 1, wxALL|wxEXPAND, 5);

			// Refresh the sizers and the buttons
			this->m_ItemsSizer->Layout();
			this->m_ItemsScrollList->Layout();
			this->FixItemMoverButtons();
			return;
		}

		// Otherwise, move to the next element
		it = std::next(it);
		index_cur++;
	}
	while(it != this->list_Items.end());
}

void Main::RemoveItem(void* item)
{
	// Remove the item
	this->m_ItemsSizer->Detach((Item*)item);
	this->list_Items.remove(item);

	// Refresh the sizers and the buttons
	this->m_ItemsSizer->Layout();
	this->FixItemMoverButtons();
	this->m_ItemsScrollList->FitInside();
}

std::list<void*>* Main::GetItemList()
{
	return &this->list_Items;
}

void Main::FixItemMoverButtons()
{
	Item* first = (Item*)list_Items.front();
	Item* last = (Item*)list_Items.back();
	std::list<void*>::iterator it;

	// Iterate through each item
	for (it = this->list_Items.begin(); it != this->list_Items.end(); ++it)
	{
		Item* elem = (Item*)*it;

		// Disable the up button on the first element
		if (elem == first)
			elem->SetUpButtonState(false);
		else
			elem->SetUpButtonState(true);

		// Disable the down button on the last element
		if (elem == last)
			elem->SetDownButtonState(false);
		else
			elem->SetDownButtonState(true);
	}
}

void Main::SaveFile(bool newfile)
{
	std::string progname;
	nlohmann::json appdata = 
	{
		{
			"Settings", 
			{
				{"Mem Start", settings_memstart},
				{"Mem Length", settings_memsize},
				{"Mem Segments", settings_memsegments}
			}
		}, 
		{
			"Items",  
			{
				// Starts empty
			}
		}
	};

	// Add each item to the JSON file
	if (this->list_Items.size() > 0)
	{
		int itemcount = 0;
		std::list<void*>::iterator it;
		for (it = this->list_Items.begin(); it != this->list_Items.end(); ++it)
		{
			Item* elem = (Item*)*it;
			appdata["Items"][itemcount++] = {
				{"Name", elem->GetName()},
				{"Start", elem->GetMemStart()},
				{"Length", elem->GetMemLength()},
				{"Color", {elem->GetBackColor().Red(), elem->GetBackColor().Green(), elem->GetBackColor().Blue(), elem->GetBackColor().Blue()}},
				{"TextColor", {elem->GetFontColor().Red(), elem->GetFontColor().Green(), elem->GetFontColor().Blue()}},
				{"Alpha", elem->GetAlpha()},
			};
		}
	}

	// Open the file save dialogue
	if (savePath.empty() || newfile)
	{
		wxFileDialog fileDialogue(this, _("Save Memory Map"), "", "", "JSON files (*.json)|*.json", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);

		// Ensure the user didn't cancel
		if (fileDialogue.ShowModal() == wxID_CANCEL)
			return;

		// Write it to a file
		savePath = std::string(fileDialogue.GetPath().ToStdString());
	}

	// Save the file
	std::ofstream file(savePath);
	file << appdata;
	file.close();

	// Update our program title
	progname = PROGRAM_NAME;
	progname.append(" - ");
	progname.append(savePath.substr(savePath.find_last_of("/\\") + 1));
	this->SetTitle(progname);
}

void Main::RefreshDrawing()
{
	this->m_DrawPanel->Refresh();
}

void Main::Paint(wxDC* dc, wxSize framesize)
{
	wxString text;
	double rectx, recty, rectw, recth;
	double textx, texty, textw, texth;
	std::list<void*>::iterator it;

	// Draw the background
	dc->DrawRectangle(-1, -1, framesize.x+2, framesize.y+2);

	// Calculate the rectangle size and position
	rectw = framesize.x*0.4;
	recth = framesize.y*0.8;
	rectx = framesize.x/2 - rectw/2;
	recty = framesize.y/2 - recth/2;

	// Now draw the memory map
	dc->SetPen(*wxBLACK_PEN);
	dc->SetBrush(*wxTRANSPARENT_BRUSH);
	dc->DrawRectangle(round(rectx), round(recty), round(rectw), round(recth));

	// Draw the start and end of the memory map
	dc->SetBackgroundMode(wxBRUSHSTYLE_TRANSPARENT);
	text = wxString::Format(wxT("0x%08x"), settings_memstart);
	framesize = dc->GetTextExtent(text);
	textw = framesize.x;
	texth = framesize.y;
	textx = rectx - textw - 4;
	texty = recty - texth/2;
	dc->DrawText(text, round(textx), round(texty));
	text = wxString::Format(wxT("0x%08x"), settings_memstart+settings_memsize);
	framesize = dc->GetTextExtent(text);
	textw = framesize.x;
	texth = framesize.y;
	textx = rectx - textw - 4;
	texty = recty+recth - texth/2;
	dc->SetFont(*wxNORMAL_FONT);
	dc->DrawText(text, round(textx), round(texty));

	// Draw each item into the memory map
	for (it = this->list_Items.begin(); it != this->list_Items.end(); ++it)
	{
		double rectlen = settings_memsize;
		double elemx, elemy, elemw, elemh;
		Item* elem = (Item*)*it;

		// Find out how much of the rectangle this element occupies
		elemw = rectw;
		elemx = rectx;
		elemy = recty + recth*(((float)elem->GetMemStart())/rectlen);
		elemh = recth*(((float)elem->GetMemLength())/rectlen);

		// Draw the rectangle
		dc->SetPen(*wxBLACK_PEN);
		dc->SetBrush(wxColor(elem->GetBackColor().Red(), elem->GetBackColor().Green(), elem->GetBackColor().Blue(), elem->GetAlpha()));
		dc->DrawRectangle(round(elemx), round(elemy), round(elemw), round(elemh));

		// Draw the item name
		dc->SetPen(elem->GetFontColor());
		text = elem->GetName();
		framesize = dc->GetTextExtent(text);
		textw = framesize.x;
		texth = framesize.y;
		textx = elemx + elemw/2 - textw/2;
		texty = elemy + elemh/2 - texth/2;
		dc->DrawText(text, round(textx), round(texty));
	}

	// Handle memory segments
	if (settings_memsegments > 1)
	{
		double segmentdis = recth/settings_memsegments;
		double segmentsize = settings_memsize/settings_memsegments;

		// Set the pen to black
		dc->SetPen(*wxBLACK_PEN);
		dc->SetBrush(*wxTRANSPARENT_BRUSH);
		dc->SetFont(*wxNORMAL_FONT);

		// Draw the segment line and text
		for (int i=1; i<settings_memsegments; i++)
		{
			double segmenty = recty+i*segmentdis;
			dc->DrawLine(round(rectx), round(segmenty), round(rectx+rectw), round(segmenty));

			// Draw the memory label
			text = wxString::Format(wxT("0x%08x"), (int)(settings_memstart+segmentsize*i));
			framesize = dc->GetTextExtent(text);
			textw = framesize.x;
			texth = framesize.y;
			textx = rectx - textw - 4;
			texty = segmenty - texth/2;
			dc->DrawText(text, round(textx), round(texty));
		}
	}
}