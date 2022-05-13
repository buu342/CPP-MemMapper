#include "main.h"
#include "export.h"


Export::Export(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxDialog(parent, id, title, pos, size, style)
{
	this->imagewidth = 512;
	this->imageheight = 1024;

	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxGridSizer* m_Sizer_Main;
	m_Sizer_Main = new wxGridSizer(0, 2, 0, 0);

	m_Label_Width = new wxStaticText(this, wxID_ANY, wxT("Image Width"), wxDefaultPosition, wxDefaultSize, 0);
	m_Label_Width->Wrap(-1);
	m_Sizer_Main->Add(m_Label_Width, 0, wxALIGN_CENTER|wxALL, 5);

	m_Label_Height = new wxStaticText(this, wxID_ANY, wxT("Image Height"), wxDefaultPosition, wxDefaultSize, 0);
	m_Label_Height->Wrap(-1);
	m_Sizer_Main->Add(m_Label_Height, 0, wxALIGN_CENTER|wxALL, 5);

	m_SpinCtrl_Width = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 99999, this->imagewidth);
	m_Sizer_Main->Add(m_SpinCtrl_Width, 0, wxALIGN_CENTER|wxALL, 5);

	m_SpinCtrl_Height = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 99999, this->imageheight);
	m_Sizer_Main->Add(m_SpinCtrl_Height, 0, wxALIGN_CENTER|wxALL, 5);

	m_Button_Export = new wxButton(this, wxID_ANY, wxT("Export"), wxDefaultPosition, wxDefaultSize, 0);
	m_Sizer_Main->Add(m_Button_Export, 0, wxALIGN_CENTER|wxALL, 5);

	m_Button_Cancel = new wxButton(this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0);
	m_Sizer_Main->Add(m_Button_Cancel, 0, wxALIGN_CENTER|wxALL, 5);


	this->SetSizer(m_Sizer_Main);
	this->Layout();
	m_Sizer_Main->Fit(this);

	this->Centre(wxBOTH);

	// Connect Events
	m_SpinCtrl_Width->Connect(wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler(Export::m_SpinCtrl_WidthOnSpinCtrl), NULL, this);
	m_SpinCtrl_Height->Connect(wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler(Export::m_SpinCtrl_HeightOnSpinCtrl), NULL, this);
	m_Button_Export->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Export::m_Button_ExportOnButtonClick), NULL, this);
	m_Button_Cancel->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Export::m_Button_CancelOnButtonClick), NULL, this);
}

Export::~Export()
{
	// Disconnect Events
	m_SpinCtrl_Width->Disconnect(wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler(Export::m_SpinCtrl_WidthOnSpinCtrl), NULL, this);
	m_SpinCtrl_Height->Disconnect(wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler(Export::m_SpinCtrl_HeightOnSpinCtrl), NULL, this);
	m_Button_Export->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Export::m_Button_ExportOnButtonClick), NULL, this);
	m_Button_Cancel->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Export::m_Button_CancelOnButtonClick), NULL, this);

}

void Export::m_SpinCtrl_WidthOnSpinCtrl(wxSpinEvent& event)
{
	this->imagewidth = event.GetValue();
}

void Export::m_SpinCtrl_HeightOnSpinCtrl(wxSpinEvent& event)
{
	this->imageheight = event.GetValue();
}

void Export::m_Button_ExportOnButtonClick(wxCommandEvent& event)
{
	// Pop up a file dialogue
	wxFileDialog fileDialogue(this, _("Export Memory Map"), "", "", "PNG image (*.png)|*.png", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);

	// Ensure the user didn't cancel
	if (fileDialogue.ShowModal() == wxID_CANCEL)
		return;

	// Generate the image
	wxSize imgsize(this->imagewidth, this->imageheight);
	wxBitmap image(imgsize, 32);
	wxMemoryDC dc(image);
	dc.SetBrush(*wxWHITE_BRUSH);
	((Main*)this->GetParent())->Paint(&dc, imgsize);
	image.ConvertToImage().SaveFile(fileDialogue.GetPath(), wxBITMAP_TYPE_PNG);

	// Kill self
	this->Close(true);
}

void Export::m_Button_CancelOnButtonClick(wxCommandEvent& event)
{
	this->Close(true);
}

void Export::ShowExport()
{
	this->ShowModal();
}