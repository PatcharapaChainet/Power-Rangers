#include "ProductManager.h" 
#include <wx/sizer.h>

ProductManager::ProductManager(wxWindow* parent)
    : wxPanel(parent)  // สร้าง wxPanel บน parent (MainFrame)
{
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    // เพิ่มเนื้อหาของระบบจัดการสินค้า
    wxStaticText* title = new wxStaticText(this, wxID_ANY, "ระบบจัดการสินค้า", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    sizer->Add(title, 0, wxALIGN_CENTER | wxTOP, 20);

    // ปุ่มหรือ widget อื่น ๆ
    wxButton* btnBack = new wxButton(this, wxID_ANY, "กลับไปยังเมนูหลัก", wxDefaultPosition, wxSize(200, 40));
    sizer->Add(btnBack, 0, wxALIGN_CENTER | wxTOP, 10);

    this->SetSizer(sizer);
}
