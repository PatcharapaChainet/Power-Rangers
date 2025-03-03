#include <wx/wx.h>
#include "ProductManager.h"
#include "CostCalculator.h"
#include "CustomerInfo.h"
#include "PaymentSystem.h"

class MainFrame : public wxFrame {
public:
    MainFrame()
        : wxFrame(nullptr, wxID_ANY, "POS", wxDefaultPosition, wxSize(500, 400)) {

        // สร้าง Panel หลักสำหรับแสดงผล
        panelMain = new wxPanel(this);
        panelMain->SetBackgroundColour(wxColour(220, 220, 250));

        // สร้างปุ่มสำหรับเลือกฟังก์ชัน
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

        wxStaticText* title = new wxStaticText(panelMain, wxID_ANY, "POS System", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
        title->SetFont(wxFont(20, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

        wxButton* btnProduct = new wxButton(panelMain, 1001, "ระบบจัดการสินค้า", wxDefaultPosition, wxSize(250, 40));
        wxButton* btnCost = new wxButton(panelMain, 1002, "ระบบคำนวณต้นทุน", wxDefaultPosition, wxSize(250, 40));
        wxButton* btnCustomer = new wxButton(panelMain, 1003, "ระบบข้อมูลลูกค้า", wxDefaultPosition, wxSize(250, 40));
        wxButton* btnPayment = new wxButton(panelMain, 1004, "ระบบชำระเงิน", wxDefaultPosition, wxSize(250, 40));
        wxButton* btnExit = new wxButton(panelMain, wxID_EXIT, "ออกจากโปรแกรม", wxDefaultPosition, wxSize(250, 40));

        sizer->Add(title, 0, wxALIGN_CENTER | wxTOP, 20);
        sizer->Add(btnProduct, 0, wxALIGN_CENTER | wxTOP, 10);
        sizer->Add(btnCost, 0, wxALIGN_CENTER | wxTOP, 10);
        sizer->Add(btnCustomer, 0, wxALIGN_CENTER | wxTOP, 10);
        sizer->Add(btnPayment, 0, wxALIGN_CENTER | wxTOP, 10);
        sizer->Add(btnExit, 0, wxALIGN_CENTER | wxTOP, 10);

        panelMain->SetSizer(sizer);

        // ฟังก์ชันให้ปุ่มเปิดแสดง Panel ใหม่
        btnProduct->Bind(wxEVT_BUTTON, &MainFrame::OnOpenProductManager, this);
        btnCost->Bind(wxEVT_BUTTON, &MainFrame::OnOpenCostCalculator, this);
        btnCustomer->Bind(wxEVT_BUTTON, &MainFrame::OnOpenCustomerInfo, this);
        btnPayment->Bind(wxEVT_BUTTON, &MainFrame::OnOpenPaymentSystem, this);
        btnExit->Bind(wxEVT_BUTTON, &MainFrame::OnExit, this);
    }

    // เปิดฟังก์ชันที่เกี่ยวข้อง
    void OnOpenProductManager(wxCommandEvent& event) {
        ChangePanel(new ProductManager(panelMain));
    }

    void OnOpenCostCalculator(wxCommandEvent& event) {
        ChangePanel(new CostCalculator(panelMain));
    }

    void OnOpenCustomerInfo(wxCommandEvent& event) {
        ChangePanel(new CustomerInfo(panelMain));
    }

    void OnOpenPaymentSystem(wxCommandEvent& event) {
        ChangePanel(new PaymentSystem(panelMain));
    }

    void OnExit(wxCommandEvent& event) {
        Close(true);
    }

private:
    wxPanel* panelMain;  // Panel หลัก

    void ChangePanel(wxPanel* newPanel) {
        // ซ่อน Panel เก่าถ้ามี
        if (currentPanel) {
            currentPanel->Hide();
        }

        // ลบ widget เก่าออกจาก sizer
        panelMain->GetSizer()->Clear(true);

        // เพิ่ม Panel ใหม่เข้าไปใน sizer
        panelMain->GetSizer()->Add(newPanel, 1, wxEXPAND | wxALL, 10);

        // แสดง Panel ใหม่
        panelMain->Layout();  // จัดการ layout ใหม่เพื่อให้ Panel ใหม่แสดง
        currentPanel = newPanel;
    }

    wxPanel* currentPanel = nullptr;  // เก็บ Panel ปัจจุบัน
};

class MyApp : public wxApp {
public:
    virtual bool OnInit() {
        MainFrame* frame = new MainFrame();
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
