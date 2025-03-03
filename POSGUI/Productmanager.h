#ifndef PRODUCTMANAGER_H
#define PRODUCTMANAGER_H

#include <wx/wx.h>
#include <wx/grid.h>
#include <vector>
#include "Item.h"
#include "cost.h"

class ProductManager : public wxPanel {
public:
    ProductManager(wxWindow* parent) : wxPanel(parent) {
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

        wxStaticText* title = new wxStaticText(this, wxID_ANY, "ระบบจัดการสินค้า", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
        title->SetFont(wxFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
        sizer->Add(title, 0, wxALIGN_CENTER | wxTOP, 20);

        productGrid = new wxGrid(this, wxID_ANY);
        productGrid->CreateGrid(0, 5);  
        productGrid->SetColLabelValue(0, "รหัสสินค้า");
        productGrid->SetColLabelValue(1, "ชื่อสินค้า");
        productGrid->SetColLabelValue(2, "ราคาต้นทุน");
        productGrid->SetColLabelValue(3, "ราคาขาย");
        productGrid->SetColLabelValue(4, "จำนวนสินค้า");

        productGrid->SetDefaultCellFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
        productGrid->SetDefaultColSize(120, true);
        productGrid->SetColSize(0, 120);
        productGrid->SetColSize(1, 200);
        productGrid->SetColSize(2, 120);
        productGrid->SetColSize(3, 120);
        productGrid->SetColSize(4, 120);
        sizer->Add(productGrid, 1, wxEXPAND | wxALL, 10);

        wxBoxSizer* formSizer = new wxBoxSizer(wxHORIZONTAL);

        nameField = new wxTextCtrl(this, wxID_ANY);
        codeField = new wxTextCtrl(this, wxID_ANY);
        costField = new wxTextCtrl(this, wxID_ANY);
        priceField = new wxTextCtrl(this, wxID_ANY);
        quantityField = new wxTextCtrl(this, wxID_ANY);

        formSizer->Add(new wxStaticText(this, wxID_ANY, "ชื่อสินค้า"), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
        formSizer->Add(nameField, 1, wxLEFT | wxRIGHT, 10);
        formSizer->Add(new wxStaticText(this, wxID_ANY, "รหัสสินค้า"), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
        formSizer->Add(codeField, 1, wxLEFT | wxRIGHT, 10);
        formSizer->Add(new wxStaticText(this, wxID_ANY, "ราคาต้นทุน"), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
        formSizer->Add(costField, 1, wxLEFT | wxRIGHT, 10);
        formSizer->Add(new wxStaticText(this, wxID_ANY, "ราคาขาย"), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
        formSizer->Add(priceField, 1, wxLEFT | wxRIGHT, 10);
        formSizer->Add(new wxStaticText(this, wxID_ANY, "จำนวนสินค้า"), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
        formSizer->Add(quantityField, 1, wxLEFT | wxRIGHT, 10);

        wxButton* addButton = new wxButton(this, wxID_ANY, "เพิ่มสินค้า");
        formSizer->Add(addButton, 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 10);
        sizer->Add(formSizer, 0, wxEXPAND | wxALL, 10);

        addButton->Bind(wxEVT_BUTTON, &ProductManager::OnAddProduct, this);

        wxBoxSizer* deleteSizer = new wxBoxSizer(wxHORIZONTAL);
        deleteField = new wxTextCtrl(this, wxID_ANY);
        wxButton* deleteButton = new wxButton(this, wxID_ANY, "ลบสินค้า");
        deleteSizer->Add(new wxStaticText(this, wxID_ANY, "กรอกรหัสสินค้าที่จะลบ:"), 0, wxALIGN_CENTER_VERTICAL);
        deleteSizer->Add(deleteField, 1, wxLEFT, 10);
        deleteSizer->Add(deleteButton, 0, wxLEFT, 10);

        sizer->Add(deleteSizer, 0, wxEXPAND | wxALL, 10);

        wxButton* backToMainButton = new wxButton(this, wxID_ANY, "กลับสู่หน้าหลัก");
        sizer->Add(backToMainButton, 0, wxALIGN_CENTER | wxTOP, 10);
        backToMainButton->Bind(wxEVT_BUTTON, &ProductManager::OnBackToMain, this);

        deleteButton->Bind(wxEVT_BUTTON, &ProductManager::OnDeleteProduct, this);

        this->SetSizer(sizer);
        this->Layout();

        Item::LoadProductsFromFile(productlist);
        UpdateProductGrid();
    }

private:
    wxGrid* productGrid;
    wxTextCtrl* nameField;
    wxTextCtrl* codeField;
    wxTextCtrl* costField;
    wxTextCtrl* priceField;
    wxTextCtrl* quantityField;
    wxTextCtrl* deleteField;

    std::vector<Item> productlist;

    void UpdateProductGrid() {
        if (productGrid->GetNumberRows() > 0) {
            productGrid->DeleteRows(0, productGrid->GetNumberRows());
        }

        for (size_t i = 0; i < productlist.size(); ++i) {
            productGrid->AppendRows(1);
            productGrid->SetCellValue(i, 0, productlist[i].getcode());
            productGrid->SetCellValue(i, 1, productlist[i].getName());
            productGrid->SetCellValue(i, 2, std::to_string(productlist[i].getCost()));
            productGrid->SetCellValue(i, 3, std::to_string(productlist[i].getPrice()));
            productGrid->SetCellValue(i, 4, std::to_string(productlist[i].getQuantity()));
        }
    }


    void OnAddProduct(wxCommandEvent& event) {
        std::string name = nameField->GetValue().ToStdString();
        std::string code = codeField->GetValue().ToStdString();
        double cost = wxAtof(costField->GetValue());
        double price = wxAtof(priceField->GetValue());
        int quantity = wxAtoi(quantityField->GetValue());
        addcost(name,-cost * quantity);
        nameField->Clear();
        codeField->Clear();
        costField->Clear();
        priceField->Clear();
        quantityField->Clear();
        saveCostToFile();
        productlist.push_back(Item(code, name, cost, price, quantity));
        Item::SaveProductsToFile(productlist);
        UpdateProductGrid();
    }

   
    void OnDeleteProduct(wxCommandEvent& event) {
        std::string codeToDelete = deleteField->GetValue().ToStdString();
        auto it = std::remove_if(productlist.begin(), productlist.end(),
            [&codeToDelete](const Item& item) { 
                delcost(item.getName());
                saveCostToFile(); return item.getcode() == codeToDelete; });

        if (it != productlist.end()) {
            productlist.erase(it, productlist.end());
            Item::SaveProductsToFile(productlist);
            UpdateProductGrid();
        }
        deleteField->Clear();
    }

 
    void OnBackToMain(wxCommandEvent& event) {
        Item::SaveProductsToFile(productlist);
        wxCommandEvent evt(wxEVT_COMMAND_BUTTON_CLICKED, 1000);
        wxPostEvent(GetParent(), evt);
    }
};

#endif 
