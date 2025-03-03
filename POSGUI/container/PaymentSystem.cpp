#include "PaymentSystem.h" 
#include <wx/sizer.h>

PaymentSystem::PaymentSystem(wxWindow* parent)
    : wxPanel(parent)  // ���ҧ wxPanel �� parent (MainFrame)
{
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    // ���������Ңͧ�к������Թ
    wxStaticText* title = new wxStaticText(this, wxID_ANY, "�к������Թ", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    sizer->Add(title, 0, wxALIGN_CENTER | wxTOP, 20);

    // �������� widget ��� �
    wxButton* btnBack = new wxButton(this, wxID_ANY, "��Ѻ��ѧ������ѡ", wxDefaultPosition, wxSize(200, 40));
    sizer->Add(btnBack, 0, wxALIGN_CENTER | wxTOP, 10);

    this->SetSizer(sizer);
}
