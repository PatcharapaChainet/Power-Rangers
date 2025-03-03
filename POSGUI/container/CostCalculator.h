#ifndef COST_CALCULATOR_H 
#define COST_CALCULATOR_H

#include <wx/wx.h>

// เปลี่ยนจาก wxFrame เป็น wxPanel
class CostCalculator : public wxPanel {
public:
    CostCalculator(wxWindow* parent);  // Constructor รับ wxWindow (หรือ wxFrame)
};

#endif
