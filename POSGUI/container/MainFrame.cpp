#include <wx/wx.h>
#include "ProductManager.h"
#include "CostCalculator.h"
#include "CustomerInfo.h"
#include "PaymentSystem.h"

class MainFrame : public wxFrame {
public:
    MainFrame()
        : wxFrame(nullptr, wxID_ANY, "POS", wxDefaultPosition, wxSize(500, 400)) {

        // ���ҧ Panel ��ѡ����Ѻ�ʴ���
        panelMain = new wxPanel(this);
        panelMain->SetBackgroundColour(wxColour(220, 220, 250));

        // ���ҧ��������Ѻ���͡�ѧ��ѹ
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

        wxStaticText* title = new wxStaticText(panelMain, wxID_ANY, "POS System", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
        title->SetFont(wxFont(20, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

        wxButton* btnProduct = new wxButton(panelMain, 1001, "�к��Ѵ����Թ���", wxDefaultPosition, wxSize(250, 40));
        wxButton* btnCost = new wxButton(panelMain, 1002, "�к��ӹǳ�鹷ع", wxDefaultPosition, wxSize(250, 40));
        wxButton* btnCustomer = new wxButton(panelMain, 1003, "�к��������١���", wxDefaultPosition, wxSize(250, 40));
        wxButton* btnPayment = new wxButton(panelMain, 1004, "�к������Թ", wxDefaultPosition, wxSize(250, 40));
        wxButton* btnExit = new wxButton(panelMain, wxID_EXIT, "�͡�ҡ�����", wxDefaultPosition, wxSize(250, 40));

        sizer->Add(title, 0, wxALIGN_CENTER | wxTOP, 20);
        sizer->Add(btnProduct, 0, wxALIGN_CENTER | wxTOP, 10);
        sizer->Add(btnCost, 0, wxALIGN_CENTER | wxTOP, 10);
        sizer->Add(btnCustomer, 0, wxALIGN_CENTER | wxTOP, 10);
        sizer->Add(btnPayment, 0, wxALIGN_CENTER | wxTOP, 10);
        sizer->Add(btnExit, 0, wxALIGN_CENTER | wxTOP, 10);

        panelMain->SetSizer(sizer);

        // �ѧ��ѹ�������Դ�ʴ� Panel ����
        btnProduct->Bind(wxEVT_BUTTON, &MainFrame::OnOpenProductManager, this);
        btnCost->Bind(wxEVT_BUTTON, &MainFrame::OnOpenCostCalculator, this);
        btnCustomer->Bind(wxEVT_BUTTON, &MainFrame::OnOpenCustomerInfo, this);
        btnPayment->Bind(wxEVT_BUTTON, &MainFrame::OnOpenPaymentSystem, this);
        btnExit->Bind(wxEVT_BUTTON, &MainFrame::OnExit, this);
    }

    // �Դ�ѧ��ѹ�������Ǣ�ͧ
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
    wxPanel* panelMain;  // Panel ��ѡ

    void ChangePanel(wxPanel* newPanel) {
        // ��͹ Panel ��Ҷ����
        if (currentPanel) {
            currentPanel->Hide();
        }

        // ź widget ����͡�ҡ sizer
        panelMain->GetSizer()->Clear(true);

        // ���� Panel ��������� sizer
        panelMain->GetSizer()->Add(newPanel, 1, wxEXPAND | wxALL, 10);

        // �ʴ� Panel ����
        panelMain->Layout();  // �Ѵ��� layout ����������� Panel �����ʴ�
        currentPanel = newPanel;
    }

    wxPanel* currentPanel = nullptr;  // �� Panel �Ѩ�غѹ
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
