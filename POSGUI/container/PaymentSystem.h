#ifndef PAYMENT_SYSTEM_H 
#define PAYMENT_SYSTEM_H

#include <wx/wx.h>

// เปลี่ยนจาก wxFrame เป็น wxPanel
class PaymentSystem : public wxPanel {
public:
    PaymentSystem(wxWindow* parent);  // Constructor รับ wxWindow (หรือ wxFrame)
};

#endif
