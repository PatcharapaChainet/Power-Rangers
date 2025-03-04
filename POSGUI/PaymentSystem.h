#ifndef PAYMENT_SYSTEM_H
#define PAYMENT_SYSTEM_H

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/listctrl.h>
#include "Item.h"
#include "customerservice.h"
#include "Cost.h"
#include <vector>
#include <string>

class PaymentSystem : public wxPanel {
public:
    PaymentSystem(wxWindow* parent);
    int quantity = 0;
private:
    wxListCtrl* productListCtrl;
    wxTextCtrl* totalPriceCtrl;
    wxTextCtrl* amountPaidCtrl;
    wxTextCtrl* changeCtrl;
    wxTextCtrl* memberPhoneCtrl;
    wxCheckBox* usePointsCheckBox;
    wxButton* addProductButton;
    wxButton* payButton;
    wxButton* addAmountButton;
    wxButton* addPhoneButton;
    wxButton* resetButton;
    wxStaticText* titleText;

    double totalPrice;
    vector<Item> productlist;
    vector<Customer> customerlist;
    vector<cost> costlist;

    void OnAddProduct(wxCommandEvent& event);
    void OnBackToMain(wxCommandEvent& event);
    void OnPay(wxCommandEvent& event);
    void OnAddAmount(wxCommandEvent& event);
    void OnAddPhone(wxCommandEvent& event);
    void OnReset(wxCommandEvent& event);
};

enum {
    ID_ADD_PRODUCT = 1,
    ID_PAY,
    ID_AMOUNT_PAID,
    ID_BACK,
    ID_ADD_AMOUNT,
    ID_ADD_PHONE,
    ID_RESET
};

PaymentSystem::PaymentSystem(wxWindow* parent)
    : wxPanel(parent, wxID_ANY), totalPrice(0.0) {

    Item::LoadProductsFromFile(productlist);
    loadCustomerFromFile();
    loadcostFromFile();

    wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);

    titleText = new wxStaticText(this, wxID_ANY, "PAYMENT SYSTEM", wxDefaultPosition, wxSize(300, 30), wxALIGN_CENTER);

    wxBoxSizer* rightSizer = new wxBoxSizer(wxVERTICAL);

    productListCtrl = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxSize(400, 300), wxLC_REPORT);
    productListCtrl->InsertColumn(0, "PRODUCT_ID");
    productListCtrl->InsertColumn(1, "NAME");
    productListCtrl->InsertColumn(2, "QUANTITY");
    productListCtrl->InsertColumn(3, "SUM");

    rightSizer->Add(titleText, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);

    rightSizer->Add(new wxStaticText(this, wxID_ANY, "Total Price"), 0, wxALL, 5);
    totalPriceCtrl = new wxTextCtrl(this, wxID_ANY, "0.0", wxDefaultPosition, wxSize(150, 30), wxTE_READONLY);
    rightSizer->Add(totalPriceCtrl, 0, wxALL, 5);

    addProductButton = new wxButton(this, ID_ADD_PRODUCT, "Add Product", wxDefaultPosition, wxSize(100, 30));
    rightSizer->Add(addProductButton, 0, wxALL, 5);
    addProductButton->Bind(wxEVT_BUTTON, &PaymentSystem::OnAddProduct, this);

    amountPaidCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(150, 30));
    rightSizer->Add(new wxStaticText(this, wxID_ANY, "Amount Paid"), 0, wxALL, 5);
    rightSizer->Add(amountPaidCtrl, 0, wxALL, 5);

    addAmountButton = new wxButton(this, ID_ADD_AMOUNT, "Add money", wxDefaultPosition, wxSize(100, 30));
    rightSizer->Add(addAmountButton, 0, wxALL, 5);
    addAmountButton->Bind(wxEVT_BUTTON, &PaymentSystem::OnAddAmount, this);

    changeCtrl = new wxTextCtrl(this, wxID_ANY, "0.0", wxDefaultPosition, wxSize(150, 30), wxTE_READONLY);
    rightSizer->Add(new wxStaticText(this, wxID_ANY, "Change"), 0, wxALL, 5);
    rightSizer->Add(changeCtrl, 0, wxALL, 5);

    memberPhoneCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(150, 30));
    rightSizer->Add(new wxStaticText(this, wxID_ANY, "Phone Number"), 0, wxALL, 5);
    rightSizer->Add(memberPhoneCtrl, 0, wxALL, 5);

    addPhoneButton = new wxButton(this, ID_ADD_PHONE, "Add Phone Number", wxDefaultPosition, wxSize(100, 30));
    rightSizer->Add(addPhoneButton, 0, wxALL, 5);
    addPhoneButton->Bind(wxEVT_BUTTON, &PaymentSystem::OnAddPhone, this);

    usePointsCheckBox = new wxCheckBox(this, wxID_ANY, "Use discount", wxDefaultPosition, wxSize(100, 30));
    rightSizer->Add(usePointsCheckBox, 0, wxALL, 5);

    payButton = new wxButton(this, ID_PAY, "Pay", wxDefaultPosition, wxSize(100, 30));
    rightSizer->Add(payButton, 0, wxALL, 5);
    payButton->Bind(wxEVT_BUTTON, &PaymentSystem::OnPay, this);

    wxButton* backToMainButton = new wxButton(this, wxID_ANY, "Exit", wxDefaultPosition, wxSize(100, 30));
    rightSizer->Add(backToMainButton, 0, wxALL, 5);
    backToMainButton->Bind(wxEVT_BUTTON, &PaymentSystem::OnBackToMain, this);


    resetButton = new wxButton(this, ID_RESET, "Reset", wxDefaultPosition, wxSize(100, 30));
    rightSizer->Add(resetButton, 0, wxALL, 5);
    resetButton->Bind(wxEVT_BUTTON, &PaymentSystem::OnReset, this);

    mainSizer->Add(productListCtrl, 1, wxALL | wxEXPAND, 5);
    mainSizer->Add(rightSizer, 0, wxALL, 5);

    SetSizer(mainSizer);
}

void PaymentSystem::OnBackToMain(wxCommandEvent& event) {
    wxCommandEvent evt(wxEVT_COMMAND_BUTTON_CLICKED, 1000);
    Item::SaveProductsToFile(productlist);
    saveCostToFile();
    saveCustomerToFile();
    wxPostEvent(GetParent(), evt);
}

void PaymentSystem::OnAddProduct(wxCommandEvent& event) {
    wxTextEntryDialog codeDialog(this, "Please input Product ID", "Add Product", "");
    if (codeDialog.ShowModal() == wxID_OK) {
        std::string productCode = codeDialog.GetValue().ToStdString();

        bool found = false;
        for (auto& item : productlist) {
            if (item.getcode() == productCode) {
                wxTextEntryDialog quantityDialog(this, "Please input Product quantity", "Add Product", "");
                if (quantityDialog.ShowModal() == wxID_OK) {
                    int quantity = wxAtoi(quantityDialog.GetValue());
                    if (quantity > item.getQuantity()) {
                        wxMessageBox("Sorry not enough product", "error", wxOK | wxICON_ERROR);
                        return;
                    }
                    long index = productListCtrl->InsertItem(productListCtrl->GetItemCount(), productCode);
                    productListCtrl->SetItem(index, 1, item.getName());
                    productListCtrl->SetItem(index, 2, std::to_string(quantity));
                    productListCtrl->SetItem(index, 3, std::to_string(item.getPrice() * quantity));

                    totalPrice += item.getPrice() * quantity;
                    totalPriceCtrl->SetValue(std::to_string(totalPrice));
                    found = true;
                }
            }
        }
        if (found == false) {
            wxMessageBox("can't find product", "error", wxOK | wxICON_ERROR);
            return;
        }
    }
}

void PaymentSystem::OnPay(wxCommandEvent& event) {
    double amountPaid = wxAtoi(amountPaidCtrl->GetValue());
    string memberPhone;
    if (usePointsCheckBox->IsChecked()) {
        memberPhone = memberPhoneCtrl->GetValue().ToStdString();
        if (checkcustomer(memberPhone)) {
            int pointsToUse = checkpoint(memberPhone);
            double discount = pointsToUse;

            if (discount > totalPrice) {
                discount = totalPrice;
            }

            totalPrice -= discount;
            minusCustomerPoint(memberPhone, discount);
            totalPriceCtrl->SetValue(std::to_string(totalPrice));
        }
        else {
            wxMessageBox("please br registered bofore continue", "¢ÈÕº‘¥æ≈“¥", wxOK | wxICON_ERROR);
            return;
        }
    }

    if (amountPaid < totalPrice) {
        wxMessageBox("not enough money", "error", wxOK | wxICON_ERROR);
        return;
    }
    else {
        for (long itemIdx = 0; itemIdx < productListCtrl->GetItemCount(); ++itemIdx) {
            std::string productCode = productListCtrl->GetItemText(itemIdx, 0).ToStdString();
            for (auto& item : productlist) {
                if (item.getcode() == productCode) {
                    int soldQuantity = wxAtoi(productListCtrl->GetItemText(itemIdx, 2));
                    item.decItem(soldQuantity);
                }
            }
        }

        double change = amountPaid - totalPrice;
        changeCtrl->SetValue(std::to_string(change));


        addCustomerPoint(memberPhone, totalPrice / 50);

        wxMessageBox("payment successful", "successful", wxOK | wxICON_INFORMATION);
    }
}



void PaymentSystem::OnAddAmount(wxCommandEvent& event) {
    wxTextEntryDialog dialog(this, "please input money amount", "Add money", "");
    if (dialog.ShowModal() == wxID_OK) {
        amountPaidCtrl->SetValue(dialog.GetValue());

    }
}

void PaymentSystem::OnAddPhone(wxCommandEvent& event) {
    wxTextEntryDialog dialog(this, "please input phone number", "Add phonenumber", "");
    if (dialog.ShowModal() == wxID_OK) {
        memberPhoneCtrl->SetValue(dialog.GetValue());
    }
}

void PaymentSystem::OnReset(wxCommandEvent& event) {
    totalPriceCtrl->Clear();
    amountPaidCtrl->Clear();
    changeCtrl->Clear();
    memberPhoneCtrl->Clear();
    usePointsCheckBox->SetValue(false);
}

#endif 
