#ifndef CUSTOMER_INFO_H
#define CUSTOMER_INFO_H

#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/sizer.h>
#include <vector>
#include "CustomerService.h"

class CustomerInfo : public wxPanel {
public:
    CustomerInfo(wxWindow* parent) : wxPanel(parent) {
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

        wxStaticText* title = new wxStaticText(this, wxID_ANY, "ระบบข้อมูลลูกค้า", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
        title->SetFont(wxFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
        sizer->Add(title, 0, wxALIGN_CENTER | wxTOP, 20);

        customerGrid = new wxGrid(this, wxID_ANY);
        customerGrid->CreateGrid(0, 3);  
        customerGrid->SetColLabelValue(0, "ชื่อลูกค้า");
        customerGrid->SetColLabelValue(1, "เบอร์โทร");
        customerGrid->SetColLabelValue(2, "คะแนน");

        customerGrid->SetDefaultCellFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
        customerGrid->SetDefaultColSize(120, true);
        customerGrid->SetColSize(0, 200);
        customerGrid->SetColSize(1, 150);
        customerGrid->SetColSize(2, 120);
        sizer->Add(customerGrid, 1, wxEXPAND | wxALL, 10);

 
        wxBoxSizer* formSizer = new wxBoxSizer(wxHORIZONTAL);

        nameField = new wxTextCtrl(this, wxID_ANY);
        phoneField = new wxTextCtrl(this, wxID_ANY);

        formSizer->Add(new wxStaticText(this, wxID_ANY, "ชื่อลูกค้า"), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
        formSizer->Add(nameField, 1, wxLEFT | wxRIGHT, 10);
        formSizer->Add(new wxStaticText(this, wxID_ANY, "เบอร์โทรลูกค้า"), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
        formSizer->Add(phoneField, 1, wxLEFT | wxRIGHT, 10);

        wxButton* addButton = new wxButton(this, wxID_ANY, "เพิ่มลูกค้า");
        formSizer->Add(addButton, 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 10);
        sizer->Add(formSizer, 0, wxEXPAND | wxALL, 10);

        addButton->Bind(wxEVT_BUTTON, &CustomerInfo::OnAddCustomer, this);

        wxBoxSizer* deleteSizer = new wxBoxSizer(wxHORIZONTAL);
        deleteField = new wxTextCtrl(this, wxID_ANY);
        wxButton* deleteButton = new wxButton(this, wxID_ANY, "ลบลูกค้า");
        deleteSizer->Add(new wxStaticText(this, wxID_ANY, "กรอกรหัสโทรศัพท์ที่ต้องการลบ:"), 0, wxALIGN_CENTER_VERTICAL);
        deleteSizer->Add(deleteField, 1, wxLEFT, 10);
        deleteSizer->Add(deleteButton, 0, wxLEFT, 10);

        sizer->Add(deleteSizer, 0, wxEXPAND | wxALL, 10);

        wxButton* backButton = new wxButton(this, wxID_ANY, "กลับไปหน้าหลัก");
        sizer->Add(backButton, 0, wxALIGN_CENTER | wxALL, 10);
        backButton->Bind(wxEVT_BUTTON, &CustomerInfo::OnBackToMain, this);

    
        this->SetSizer(sizer);
        this->Layout();


        loadCustomerFromFile();  
        UpdateCustomerGrid();

        deleteButton->Bind(wxEVT_BUTTON, &CustomerInfo::OnDeleteCustomer, this);
    }

private:
    wxGrid* customerGrid;
    wxTextCtrl* nameField;
    wxTextCtrl* phoneField;
    wxTextCtrl* deleteField;

    void UpdateCustomerGrid() {
        if (customerGrid->GetNumberRows() > 0) {
            customerGrid->DeleteRows(0, customerGrid->GetNumberRows());
        }

        for (size_t i = 0; i < customerlist.size(); ++i) {
            customerGrid->AppendRows(1);
            customerGrid->SetCellValue(i, 0, customerlist[i].name);
            customerGrid->SetCellValue(i, 1, customerlist[i].getPnumber());
            customerGrid->SetCellValue(i, 2, std::to_string(customerlist[i].point));
        }
    }

    void OnAddCustomer(wxCommandEvent& event) {
        std::string name = nameField->GetValue().ToStdString();
        std::string phone = phoneField->GetValue().ToStdString();

        auto it = std::find_if(customerlist.begin(), customerlist.end(),
            [&phone](const Customer& customer) { return customer.getPnumber() == phone; });

        if (it != customerlist.end()) {
            wxMessageBox("เบอร์โทรนี้มีอยู่แล้ว กรุณากรอกข้อมูลใหม่", "ข้อผิดพลาด", wxOK | wxICON_ERROR);
        }
        else if (name.empty() || phone.empty()) {
            wxMessageBox("กรุณากรอกข้อมูลให้ครบถ้วน", "ข้อผิดพลาด", wxOK | wxICON_ERROR);
        }
        else {
            addCustomer(phone, name, 0);  
            UpdateCustomerGrid();
            nameField->Clear();
            phoneField->Clear();
        }
    }

    void OnDeleteCustomer(wxCommandEvent& event) {
        std::string phoneToDelete = deleteField->GetValue().ToStdString();
        auto it = std::remove_if(customerlist.begin(), customerlist.end(),
            [&phoneToDelete](const Customer& customer) { return customer.getPnumber() == phoneToDelete; });

        if (it != customerlist.end()) {
            customerlist.erase(it, customerlist.end());
            saveCustomerToFile();  
            UpdateCustomerGrid();
            deleteField->Clear();
        }
        else {
            wxMessageBox("ไม่พบข้อมูลลูกค้าที่เบอร์โทรนี้", "ข้อผิดพลาด", wxOK | wxICON_ERROR);
        }
    }

    void OnBackToMain(wxCommandEvent& event) {
        saveCustomerToFile();  

        wxCommandEvent evt(wxEVT_COMMAND_BUTTON_CLICKED, 1000); 
        wxPostEvent(GetParent(), evt);
    }
};

#endif