#ifndef CUSTOMER_INFO_H 
#define CUSTOMER_INFO_H

#include <wx/wx.h>

// เปลี่ยนจาก wxFrame เป็น wxPanel
class CustomerInfo : public wxPanel {
public:
    CustomerInfo(wxWindow* parent);  // Constructor รับ wxWindow (หรือ wxFrame)
};

#endif
