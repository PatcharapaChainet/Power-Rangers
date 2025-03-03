#ifndef PRODUCT_MANAGER_H 
#define PRODUCT_MANAGER_H

#include <wx/wx.h>

// เปลี่ยนจาก wxFrame เป็น wxPanel
class ProductManager : public wxPanel {
public:
    ProductManager(wxWindow* parent);  // Constructor รับ wxWindow (หรือ wxFrame)
};

#endif
