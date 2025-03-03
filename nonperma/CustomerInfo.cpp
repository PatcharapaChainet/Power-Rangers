// CustomerInfo.cpp
#include "CustomerInfo.h" 
#include <wx/sizer.h>

CustomerInfo::CustomerInfo(wxWindow* parent)
    : wxPanel(parent)
{
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    // Create title
    wxStaticText* title = new wxStaticText(this, wxID_ANY, "ระบบข้อมูลลูกค้า", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    sizer->Add(title, 0, wxALIGN_CENTER | wxTOP, 20);

    // Create back button
    wxButton* btnBack = new wxButton(this, wxID_ANY, "กลับสู่หน้าแรก", wxDefaultPosition, wxSize(200, 40));
    sizer->Add(btnBack, 0, wxALIGN_CENTER | wxTOP, 10);

    // Bind event to the back button
    btnBack->Bind(wxEVT_BUTTON, &CustomerInfo::OnBackButton, this);

    this->SetSizer(sizer);
}

// Back button handler
void CustomerInfo::OnBackButton(wxCommandEvent& event)
{
    // Send event to parent to return to main menu
    wxWindow* parent = GetParent();
    if (parent) {
        wxCommandEvent evt(wxEVT_COMMAND_BUTTON_CLICKED, wxID_HOME);
        wxPostEvent(parent, evt);
    }
}