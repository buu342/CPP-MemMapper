#include "main.h"
#include "item.h"

Item::Item(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name) : wxPanel(parent, id, pos, size, style, name)
{
	// Initialize private variables
	this->col_alpha = 128;
	this->col_back = wxColor(rand()%255, rand()%255, rand()%255, this->col_alpha);
	this->col_text = wxColor(0, 0, 0, 255);

	// Force the height of the item
	this->SetMinSize(wxSize(-1,102));
	this->SetMaxSize(wxSize(-1,102));

	// Create a sizer for the data and the manipulation buttons
	wxFlexGridSizer* m_ItemElem_Sizer0;
	m_ItemElem_Sizer0 = new wxFlexGridSizer(0, 2, 0, 0);
	m_ItemElem_Sizer0->AddGrowableCol(0);
	m_ItemElem_Sizer0->SetFlexibleDirection(wxBOTH);
	m_ItemElem_Sizer0->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	// Create a sizer for the data
	wxBoxSizer* m_ItemElem_DataSizer;
	m_ItemElem_DataSizer = new wxBoxSizer(wxVERTICAL);

	// Create the sizer for the first data row
	wxFlexGridSizer* m_ItemElem_Sizer1;
	m_ItemElem_Sizer1 = new wxFlexGridSizer(1, 0, 0, 0);
	m_ItemElem_Sizer1->AddGrowableCol(1);
	m_ItemElem_Sizer1->SetFlexibleDirection(wxBOTH);
	m_ItemElem_Sizer1->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	// Add the elements of the first data row
	this->m_ItemElem_LabelName = new wxStaticText(this, wxID_ANY, wxT("Name:"), wxDefaultPosition, wxDefaultSize, 0);
	this->m_ItemElem_LabelName->Wrap(-1);
	m_ItemElem_Sizer1->Add(m_ItemElem_LabelName, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
	this->m_ItemElem_InputName = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	m_ItemElem_Sizer1->Add(m_ItemElem_InputName, 0, wxALL|wxEXPAND, 5);
	this->m_ItemElem_ButtonFontColor = new wxBitmapButton(this, wxID_ANY, wxBitmap(wxT("resources/font.png"), wxBITMAP_TYPE_ANY), wxDefaultPosition, wxSize(24,24), wxBU_AUTODRAW|0);
	m_ItemElem_Sizer1->Add(m_ItemElem_ButtonFontColor, 0, wxALL, 5);
	m_ItemElem_DataSizer->Add(m_ItemElem_Sizer1, 1, wxEXPAND, 5);

	// Create the sizer for the second data row
	wxFlexGridSizer* m_ItemElem_Sizer2;
	m_ItemElem_Sizer2 = new wxFlexGridSizer(1, 0, 0, 0);
	m_ItemElem_Sizer2->AddGrowableCol(2);
	m_ItemElem_Sizer2->SetFlexibleDirection(wxBOTH);
	m_ItemElem_Sizer2->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	// Add the elements of the second data row
	this->m_ItemElem_ButtonColor = new wxBitmapButton(this, wxID_ANY, wxBitmap(wxT("resources/fill.png"), wxBITMAP_TYPE_ANY), wxDefaultPosition, wxSize(24,24), wxBU_AUTODRAW|0);
	m_ItemElem_Sizer2->Add(this->m_ItemElem_ButtonColor, 0, wxALL, 5);
	this->m_ItemElem_LabelAlpha = new wxStaticText(this, wxID_ANY, wxT("Alpha:"), wxDefaultPosition, wxDefaultSize, 0);
	this->m_ItemElem_LabelAlpha->Wrap(-1);
	m_ItemElem_Sizer2->Add(this->m_ItemElem_LabelAlpha, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
	this->m_ItemElem_SliderAlpha = new wxSlider(this, wxID_ANY, 128, 0, 255, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL);
	m_ItemElem_Sizer2->Add(this->m_ItemElem_SliderAlpha, 0, wxALL|wxEXPAND, 5);
	m_ItemElem_DataSizer->Add(m_ItemElem_Sizer2, 1, wxEXPAND, 5);

	// Create the sizer for the third data row
	wxFlexGridSizer* m_ItemElem_Sizer3;
	m_ItemElem_Sizer3 = new wxFlexGridSizer(1, 0, 0, 0);
	m_ItemElem_Sizer3->AddGrowableCol(1);
	m_ItemElem_Sizer3->AddGrowableCol(3);
	m_ItemElem_Sizer3->SetFlexibleDirection(wxBOTH);
	m_ItemElem_Sizer3->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	// Add the elements of the third data row
	this->m_ItemElem_LabelStart = new wxStaticText(this, wxID_ANY, wxT("Start:"), wxDefaultPosition, wxDefaultSize, 0);
	this->m_ItemElem_LabelStart->Wrap(-1);
	m_ItemElem_Sizer3->Add(this->m_ItemElem_LabelStart, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
	this->m_ItemElem_SpinStart = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 0x7FFFFFFF, 0);
	this->m_ItemElem_SpinStart->SetBase(16);
	m_ItemElem_Sizer3->Add(this->m_ItemElem_SpinStart, 0, wxALL|wxEXPAND, 5);
	this->m_ItemElem_LabelLength = new wxStaticText(this, wxID_ANY, wxT("Length:"), wxDefaultPosition, wxDefaultSize, 0);
	this->m_ItemElem_LabelLength->Wrap(-1);
	m_ItemElem_Sizer3->Add(this->m_ItemElem_LabelLength, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
	this->m_ItemElem_SpinLength = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 0x7FFFFFFF, 0);
	this->m_ItemElem_SpinLength->SetBase(16);
	m_ItemElem_Sizer3->Add(this->m_ItemElem_SpinLength, 0, wxALL|wxEXPAND, 5);
	m_ItemElem_DataSizer->Add(m_ItemElem_Sizer3, 1, wxEXPAND, 5);

	// Add all the elements to the data sizer
	m_ItemElem_Sizer0->Add(m_ItemElem_DataSizer, 1, wxEXPAND, 5);

	// Create the sizer for the item manipulation
	wxBoxSizer* m_ItemElem_PosManipSizer;
	m_ItemElem_PosManipSizer = new wxBoxSizer(wxVERTICAL);

	// Add the three manipulation button
	this->m_ItemElem_ButtonUp = new wxBitmapButton(this, wxID_ANY, wxBitmap(wxT("resources/up.png"), wxBITMAP_TYPE_ANY), wxDefaultPosition, wxSize(24,24), wxBU_AUTODRAW);
	this->m_ItemElem_ButtonUp->SetBitmapDisabled(wxBitmap(wxT("resources/up_disabled.png"), wxBITMAP_TYPE_ANY));
	m_ItemElem_PosManipSizer->Add(this->m_ItemElem_ButtonUp, 0, wxALL, 5);
	this->m_ItemElem_ButtonDown = new wxBitmapButton(this, wxID_ANY, wxBitmap(wxT("resources/down.png"), wxBITMAP_TYPE_ANY), wxDefaultPosition, wxSize(24,24), wxBU_AUTODRAW);
	this->m_ItemElem_ButtonDown->SetBitmapDisabled(wxBitmap(wxT("resources/down_disabled.png"), wxBITMAP_TYPE_ANY));
	m_ItemElem_PosManipSizer->Add(this->m_ItemElem_ButtonDown, 0, wxALL, 5);
	this->m_ItemElem_ButtonDelete = new wxBitmapButton(this, wxID_ANY, wxBitmap(wxT("resources/delete.png"), wxBITMAP_TYPE_ANY), wxDefaultPosition, wxSize(24,24), wxBU_AUTODRAW);
	m_ItemElem_PosManipSizer->Add(this->m_ItemElem_ButtonDelete, 0, wxALL, 5);
	m_ItemElem_Sizer0->Add(m_ItemElem_PosManipSizer, 1, 0, 5);

	// Finalize the layout
	this->SetSizer(m_ItemElem_Sizer0);
	this->Layout();

	// Connect events
	this->m_ItemElem_ButtonUp->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Item::m_ItemElem_ButtonUpOnButtonClick), NULL, this);
	this->m_ItemElem_ButtonDown->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Item::m_ItemElem_ButtonDownOnButtonClick), NULL, this);
	this->m_ItemElem_ButtonDelete->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Item::m_ItemElem_ButtonDeleteOnButtonClick), NULL, this);
	this->m_ItemElem_ButtonColor->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Item::m_ItemElem_ButtonColorOnButtonClick), NULL, this);
	this->m_ItemElem_InputName->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Item::m_ItemElem_InputNameOnText ), NULL, this );
	this->m_ItemElem_SliderAlpha->Connect( wxEVT_SLIDER, wxCommandEventHandler( Item::m_ItemElem_SliderAlphaOnSlider ), NULL, this );
	this->m_ItemElem_SpinStart->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Item::m_ItemElem_SpinStartOnSpinCtrl ), NULL, this );
	this->m_ItemElem_SpinLength->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( Item::m_ItemElem_SpinLengthOnSpinCtrl ), NULL, this );
}

Item::~Item()
{
	this->m_ItemElem_ButtonUp->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Item::m_ItemElem_ButtonUpOnButtonClick), NULL, this);
	this->m_ItemElem_ButtonDown->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Item::m_ItemElem_ButtonDownOnButtonClick), NULL, this);
	this->m_ItemElem_ButtonDelete->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Item::m_ItemElem_ButtonDeleteOnButtonClick), NULL, this);
	this->m_ItemElem_ButtonColor->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Item::m_ItemElem_ButtonColorOnButtonClick), NULL, this);
	this->m_ItemElem_InputName->Disconnect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(Item::m_ItemElem_InputNameOnText), NULL, this);
	this->m_ItemElem_SliderAlpha->Disconnect(wxEVT_SLIDER, wxCommandEventHandler(Item::m_ItemElem_SliderAlphaOnSlider), NULL, this);
	this->m_ItemElem_SpinStart->Disconnect(wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler(Item::m_ItemElem_SpinStartOnSpinCtrl ), NULL, this);
	this->m_ItemElem_SpinLength->Disconnect(wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler(Item::m_ItemElem_SpinLengthOnSpinCtrl), NULL, this);
}

void Item::SetInstance(Main* instance)
{
	this->instance = instance;
}

void Item::m_ItemElem_ButtonUpOnButtonClick(wxCommandEvent& event)
{
	this->instance->MoveUpItem(this);
}

void Item::m_ItemElem_ButtonDownOnButtonClick(wxCommandEvent& event)
{
	this->instance->MoveDownItem(this);
}

void Item::m_ItemElem_ButtonDeleteOnButtonClick(wxCommandEvent& event)
{
	this->instance->RemoveItem(this);
	delete this; // Commit sudoku
}

void Item::m_ItemElem_ButtonColorOnButtonClick(wxCommandEvent& event)
{
	wxColor col;
	wxColourDialog dlg(this->instance);
	dlg.SetTitle(wxString("Color Picker"));
	if (dlg.ShowModal() != wxID_OK)
		return;
	col = dlg.GetColourData().GetColour();
	this->col_back = wxColor(col.Red(), col.Green(), col.Blue(), this->m_ItemElem_SliderAlpha->GetValue());
	this->instance->RefreshDrawing();
}

void Item::m_ItemElem_InputNameOnText(wxCommandEvent& event)
{
	this->instance->RefreshDrawing();
}

void Item::m_ItemElem_SliderAlphaOnSlider(wxCommandEvent& event)
{
	this->col_back = wxColor(this->col_back.Red(), this->col_back.Green(), this->col_back.Blue(), this->m_ItemElem_SliderAlpha->GetValue());
	this->instance->RefreshDrawing();
}

void Item::m_ItemElem_SpinStartOnSpinCtrl(wxSpinEvent& event)
{
	this->instance->RefreshDrawing();
}

void Item::m_ItemElem_SpinLengthOnSpinCtrl(wxSpinEvent& event)
{
	this->instance->RefreshDrawing();
}

void Item::SetUpButtonState(bool enabled)
{
	this->m_ItemElem_ButtonUp->Enable(enabled);
}

void Item::SetDownButtonState(bool enabled)
{
	this->m_ItemElem_ButtonDown->Enable(enabled);
}

void Item::SetName(wxString name)
{
	this->m_ItemElem_InputName->SetValue(name);
}

void Item::SetMemStart(int start)
{
	this->m_ItemElem_SpinStart->SetValue(start);
}

void Item::SetMemLength(int length)
{
	this->m_ItemElem_SpinLength->SetValue(length);
}

void Item::SetMemEnd(int end)
{
	this->m_ItemElem_SpinLength->SetValue(this->m_ItemElem_SpinStart->GetValue() - end);
}

void Item::SetBackColor(wxColor clr)
{
	this->col_back = clr;
}

void Item::SetFontColor(wxColor clr)
{
	this->col_text = clr;
}

wxString Item::GetName()
{
	return this->m_ItemElem_InputName->GetValue();
}

int Item::GetMemStart()
{
	return this->m_ItemElem_SpinStart->GetValue();
}

int Item::GetMemLength()
{
	return this->m_ItemElem_SpinLength->GetValue();
}

int Item::GetMemEnd()
{
	return this->m_ItemElem_SpinStart->GetValue()+this->m_ItemElem_SpinLength->GetValue();
}

wxColor Item::GetBackColor()
{
	return this->col_back;
}

wxColor Item::GetFontColor()
{
	return this->col_text;
}