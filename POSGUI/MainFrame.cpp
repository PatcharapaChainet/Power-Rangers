#include <wx/wx.h>
#include "ProductManager.h"
#include "CostCalculator.h"
#include "CustomerInfo.h"
#include "PaymentSystem.h"
#include "Item.h"
#include "customerservice.h"
#include "cost.h"
#include <vector>
std::vector<Item> productlist;
std::vector<Customer> customerlist;
std::vector<cost> costlist;


class MainFrame : public wxFrame {
public:
    MainFrame()
        : wxFrame(nullptr, wxID_ANY, "POS", wxDefaultPosition, wxSize(500, 400)) {

        panelMain = new wxPanel(this);
        panelMain->SetBackgroundColour(wxColour(220, 220, 250));

        void loadProductsFromFile(); {
            Item::LoadProductsFromFile(productlist);
        }
        loadCustomerFromFile();
        loadcostFromFile();
        Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainFrame::OnReturnToMain, this, 1000);

        CreateMainMenu();
    }

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

    void OnReturnToMain(wxCommandEvent& event) {
        CreateMainMenu();
        currentPanel = nullptr;
        panelMain->Layout();
    }


private:
    wxPanel* panelMain;
    wxPanel* currentPanel = nullptr;


    void CreateMainMenu() {
        if (panelMain->GetSizer()) {
            panelMain->GetSizer()->Clear(true);
        }

        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

        wxStaticText* title = new wxStaticText(panelMain, wxID_ANY, "POS System", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
        title->SetFont(wxFont(20, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

        wxButton* btnProduct = new wxButton(panelMain, 1001, "STOCK MANAGER", wxDefaultPosition, wxSize(250, 40));
        wxButton* btnCost = new wxButton(panelMain, 1002, "COST INSPECTOR", wxDefaultPosition, wxSize(250, 40));
        wxButton* btnCustomer = new wxButton(panelMain, 1003, "CUSTOMER INFO", wxDefaultPosition, wxSize(250, 40));
        wxButton* btnPayment = new wxButton(panelMain, 1004, "PAYMENT SYSTEM", wxDefaultPosition, wxSize(250, 40));
        wxButton* btnExit = new wxButton(panelMain, wxID_EXIT, "EXIT", wxDefaultPosition, wxSize(250, 40));

        sizer->Add(title, 0, wxALIGN_CENTER | wxTOP, 20);
        sizer->Add(btnProduct, 0, wxALIGN_CENTER | wxTOP, 10);
        sizer->Add(btnCost, 0, wxALIGN_CENTER | wxTOP, 10);
        sizer->Add(btnCustomer, 0, wxALIGN_CENTER | wxTOP, 10);
        sizer->Add(btnPayment, 0, wxALIGN_CENTER | wxTOP, 10);
        sizer->Add(btnExit, 0, wxALIGN_CENTER | wxTOP, 10);

        panelMain->SetSizer(sizer);

        btnProduct->Bind(wxEVT_BUTTON, &MainFrame::OnOpenProductManager, this);
        btnCost->Bind(wxEVT_BUTTON, &MainFrame::OnOpenCostCalculator, this);
        btnCustomer->Bind(wxEVT_BUTTON, &MainFrame::OnOpenCustomerInfo, this);
        btnPayment->Bind(wxEVT_BUTTON, &MainFrame::OnOpenPaymentSystem, this);
        btnExit->Bind(wxEVT_BUTTON, &MainFrame::OnExit, this);
    }

  
    void ChangePanel(wxPanel* newPanel) {
        if (currentPanel) {
            currentPanel->Hide();
        }

        panelMain->GetSizer()->Clear(true);
        panelMain->GetSizer()->Add(newPanel, 1, wxEXPAND | wxALL, 10);

        panelMain->Layout();
        currentPanel = newPanel;
    }

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
