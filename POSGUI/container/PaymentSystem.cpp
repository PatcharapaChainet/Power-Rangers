#include "PaymentSystem.h" 
#include <wx/sizer.h>

PaymentSystem::PaymentSystem(wxWindow* parent)
    : wxPanel(parent)  // สร้าง wxPanel บน parent (MainFrame)
{
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    // เพิ่มเนื้อหาของระบบชำระเงิน
    wxStaticText* title = new wxStaticText(this, wxID_ANY, "ระบบชำระเงิน", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    sizer->Add(title, 0, wxALIGN_CENTER | wxTOP, 20);

    // ปุ่มหรือ widget อื่น ๆ
    wxButton* btnBack = new wxButton(this, wxID_ANY, "กลับไปยังเมนูหลัก", wxDefaultPosition, wxSize(200, 40));
    sizer->Add(btnBack, 0, wxALIGN_CENTER | wxTOP, 10);

    this->SetSizer(sizer);
}
