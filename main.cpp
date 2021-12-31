#include <string.h>
#include "main.h"
#include "item.h"

#define DEFAULT_SASH_POS 300

#define DEFAULT_MEMSTART 0x00000000
#define DEFAULT_MEMEND   0x00400000

Main::Main() : wxFrame(nullptr, wxID_ANY, "MemMapper", wxPoint(0, 0), wxSize(910, 700), wxDEFAULT_FRAME_STYLE)
{
	// Initialize
	wxInitAllImageHandlers();
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	// Add the window splitter with a scroll bar
	wxBoxSizer*m_ProgramSizer = new wxBoxSizer(wxVERTICAL);
	this->m_ProgramSplitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D|wxSP_LIVE_UPDATE|wxSP_NO_XP_THEME);
	this->m_ProgramSplitter->Connect(wxEVT_IDLE, wxIdleEventHandler(Main::m_ProgramSplitterOnIdle), NULL, this);
	this->m_ProgramSplitter->SetMinSize(wxSize(DEFAULT_SASH_POS,-1));
	this->m_ItemsScrollList = new wxScrolledWindow(this->m_ProgramSplitter, wxID_ANY, wxDefaultPosition, wxSize(DEFAULT_SASH_POS, -1), wxALWAYS_SHOW_SB|wxVSCROLL);
	this->m_ItemsScrollList->SetScrollRate(0, 5);
	this->m_ItemsScrollList->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENU));

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
	this->m_MenuBar->Append(this->m_MenuBarElem_File, wxT("File"));
	this->SetMenuBar(this->m_MenuBar);

	// Add the tool bar
	this->m_ToolBar = this->CreateToolBar(wxTB_HORIZONTAL|wxTB_FLAT, wxID_ANY);
	this->m_ToolBarElem_New = this->m_ToolBar->AddTool(wxID_ANY, wxT("New project"), wxBitmap(wxT("resources/new.png"), wxBITMAP_TYPE_ANY), wxNullBitmap, wxITEM_NORMAL, wxT("Create a new project"), wxEmptyString, NULL);
	this->m_ToolBarElem_Open = this->m_ToolBar->AddTool(wxID_ANY, wxT("Open project"), wxBitmap(wxT("resources/open.png"), wxBITMAP_TYPE_ANY), wxNullBitmap, wxITEM_NORMAL, wxT("Load a project"), wxEmptyString, NULL);
	this->m_ToolBarElem_Save = this->m_ToolBar->AddTool(wxID_ANY, wxT("Save project"), wxBitmap(wxT("resources/save.png"), wxBITMAP_TYPE_ANY), wxNullBitmap, wxITEM_NORMAL, wxT("Save this project"), wxEmptyString, NULL);
	this->m_ToolBar->AddSeparator();
	this->m_ToolBarElem_NewItem = this->m_ToolBar->AddTool(wxID_ANY, wxT("New item"), wxBitmap(wxT("resources/newmem.png"), wxBITMAP_TYPE_ANY), wxNullBitmap, wxITEM_NORMAL, wxT("Create a new memory block"), wxEmptyString, NULL);
	this->m_ToolBar->Realize();

	// Put the program in the middle of the screen
	this->Centre(wxBOTH);

	// Add event handlers
	this->m_ProgramSplitter->Connect(wxEVT_COMMAND_SPLITTER_DOUBLECLICKED, wxSplitterEventHandler(Main::m_ProgramSplitterOnSplitterDClick));
	this->m_ProgramSplitter->Connect(wxEVT_COMMAND_SPLITTER_UNSPLIT, wxSplitterEventHandler(Main::m_ProgramSplitterOnSplitterUnsplit), NULL, this);
	this->Connect(this->m_ToolBarElem_NewItem->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(Main::m_ToolBarElem_NewItemOnToolClicked));
	this->m_DrawPanel->Connect(wxEVT_PAINT, wxPaintEventHandler(Main::m_DrawPanelOnPaint), NULL, this);
}

Main::~Main()
{
	this->Disconnect(this->m_ToolBarElem_NewItem->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(Main::m_ToolBarElem_NewItemOnToolClicked));
	this->m_ProgramSplitter->Disconnect(wxEVT_COMMAND_SPLITTER_DOUBLECLICKED, wxSplitterEventHandler(Main::m_ProgramSplitterOnSplitterDClick), NULL, this);
	this->m_ProgramSplitter->Disconnect(wxEVT_COMMAND_SPLITTER_UNSPLIT, wxSplitterEventHandler(Main::m_ProgramSplitterOnSplitterUnsplit), NULL, this);
}

void Main::m_ProgramSplitterOnIdle(wxIdleEvent& event)
{
	this->m_ProgramSplitter->SetSashPosition(DEFAULT_SASH_POS);
	this->m_ProgramSplitter->Disconnect(wxEVT_IDLE, wxIdleEventHandler(Main::m_ProgramSplitterOnIdle), NULL, this);
}

void Main::m_ToolBarElem_NewItemOnToolClicked(wxCommandEvent& event)
{
	Item* it = new Item(this->m_ItemsScrollList);
	it->SetInstance(this);
	this->list_Items.push_back(it);
	this->m_ItemsSizer->Add(it, 1, wxALL|wxEXPAND, 5);

	// Refresh the sizers and the buttons
	this->m_ItemsSizer->FitInside(this->m_ItemsScrollList);
	this->m_ItemsScrollList->Layout();
	this->FixItemMoverButtons();
}

void Main::m_ProgramSplitterOnSplitterDClick(wxSplitterEvent& event)
{
	event.Veto();
}

void Main::m_ProgramSplitterOnSplitterUnsplit(wxSplitterEvent& event)
{
	event.Veto();
}

std::list<void*>* Main::GetItemList()
{
	return &this->list_Items;
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

void Main::m_DrawPanelOnPaint(wxPaintEvent& event)
{
	wxString text;
	int rectx, recty, rectw, recth;
	int textx, texty, textw, texth;
	std::list<void*>::iterator it;
	wxBufferedPaintDC dc(this->m_DrawPanel);
	wxSize framesize = this->m_DrawPanel->GetSize();

	// Draw the background
	dc.SetBrush(wxSystemSettings::GetColour(wxSYS_COLOUR_APPWORKSPACE));
	dc.DrawRectangle(-1, -1, framesize.x+2, framesize.y+2);

	// Calculate the rectangle size and position
	rectw = framesize.x*0.4;
	recth = framesize.y*0.8;
	rectx = framesize.x/2 - rectw/2;
	recty = framesize.y/2 - recth/2;

	// Now draw the memory map
	dc.SetPen(*wxBLACK_PEN);
	dc.SetBrush(*wxTRANSPARENT_BRUSH);
	dc.DrawRectangle(rectx, recty, rectw, recth);

	// Draw the start and end of the memory map
	dc.SetBackgroundMode(wxBRUSHSTYLE_TRANSPARENT);
	text = wxString::Format(wxT("0x%08x"), DEFAULT_MEMSTART);
	framesize = dc.GetTextExtent(text);
	textw = framesize.x;
	texth = framesize.y;
	textx = rectx - textw - 4;
	texty = recty - texth/2;
	dc.DrawText(text, textx, texty);
	text = wxString::Format(wxT("0x%08x"), DEFAULT_MEMEND);
	framesize = dc.GetTextExtent(text);
	textw = framesize.x;
	texth = framesize.y;
	textx = rectx - textw - 4;
	texty = recty+recth - texth/2;
	dc.SetFont(*wxNORMAL_FONT);
	dc.DrawText(text, textx, texty);

	// Draw each item into the memory map
	for (it = this->list_Items.begin(); it != this->list_Items.end(); ++it)
	{
		float rectlen = DEFAULT_MEMEND - DEFAULT_MEMSTART-1;
		int elemx, elemy, elemw, elemh;
		Item* elem = (Item*)*it;

		// Find out how much of the rectangle this element occupies
		elemw = rectw;
		elemx = rectx;
		elemy = recty + recth*(elem->GetMemStart()/rectlen);
		elemh = recth*(elem->GetMemLength()/rectlen);

		// Draw the rectangle
		dc.SetPen(*wxBLACK_PEN);
		dc.SetBrush(elem->GetBackColor());
		dc.DrawRectangle(elemx, elemy, elemw, elemh);

		// Draw the item name
		dc.SetPen(elem->GetFontColor());
		text = elem->GetName();
		framesize = dc.GetTextExtent(text);
		textw = framesize.x;
		texth = framesize.y;
		textx = elemx + elemw/2 - textw/2;
		texty = elemy + elemh/2 - texth/2;
		dc.DrawText(text, textx, texty);
	}
}