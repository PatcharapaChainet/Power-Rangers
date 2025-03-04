#ifndef COST_CALCULATOR_H
#define COST_CALCULATOR_H

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/grid.h>
#include "cost.h"

class CostCalculator : public wxPanel {
public:
    CostCalculator(wxWindow* parent) : wxPanel(parent) {
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
        
        wxStaticText* title = new wxStaticText(this, wxID_ANY, "COST INSPECTOR", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
        title->SetFont(wxFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
        sizer->Add(title, 0, wxALIGN_CENTER | wxTOP, 20);

        wxBoxSizer* inputSizer = new wxBoxSizer(wxHORIZONTAL);
        dateField = new wxTextCtrl(this, wxID_ANY);
        monthField = new wxTextCtrl(this, wxID_ANY);
        yearField = new wxTextCtrl(this, wxID_ANY);

        inputSizer->Add(new wxStaticText(this, wxID_ANY, "DAY:"), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
        inputSizer->Add(dateField, 1, wxRIGHT, 5);
        inputSizer->Add(new wxStaticText(this, wxID_ANY, "MONTH:"), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
        inputSizer->Add(monthField, 1, wxRIGHT, 5);
        inputSizer->Add(new wxStaticText(this, wxID_ANY, "YEAR:"), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
        inputSizer->Add(yearField, 1, wxRIGHT, 5);

        wxButton* searchButton = new wxButton(this, wxID_ANY, "SEARCH");
        inputSizer->Add(searchButton, 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);
        sizer->Add(inputSizer, 0, wxEXPAND | wxALL, 10);

        searchButton->Bind(wxEVT_BUTTON, &CostCalculator::OnSearch, this);

        wxButton* resetButton = new wxButton(this, wxID_ANY, "RESET");
        inputSizer->Add(resetButton, 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);
        resetButton->Bind(wxEVT_BUTTON, &CostCalculator::OnReset, this);

        wxBoxSizer* gridsSizer = new wxBoxSizer(wxHORIZONTAL);
        wxPanel* leftPanel = new wxPanel(this, wxID_ANY);
        wxBoxSizer* leftSizer = new wxBoxSizer(wxVERTICAL);
        scostGrid = new wxGrid(leftPanel, wxID_ANY);
        scostGrid->CreateGrid(0, 3);
        scostGrid->SetColLabelValue(0, "DATE");
        scostGrid->SetColLabelValue(1, "INCOME");
        scostGrid->SetColLabelValue(2, "NAME");
        scostGrid->SetDefaultCellFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
        scostGrid->SetColSize(0, 120);
        scostGrid->SetColSize(1, 120);
        scostGrid->SetColSize(2, 120);
        leftSizer->Add(scostGrid, 1, wxEXPAND | wxALL, 10);
        leftPanel->SetSizer(leftSizer);

        wxPanel* rightPanel = new wxPanel(this, wxID_ANY);
        wxBoxSizer* rightSizer = new wxBoxSizer(wxVERTICAL);
        revenueGrid = new wxGrid(rightPanel, wxID_ANY);
        revenueGrid->CreateGrid(0, 2);
        revenueGrid->SetColLabelValue(0, "DATE");
        revenueGrid->SetColLabelValue(1, "INCOME");
        revenueGrid->SetDefaultCellFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
        revenueGrid->SetColSize(0, 120);
        revenueGrid->SetColSize(1, 120);
        revenueGrid->SetColSize(2, 120);
        rightSizer->Add(revenueGrid, 1, wxEXPAND | wxALL, 10);
        rightPanel->SetSizer(rightSizer);

        gridsSizer->Add(leftPanel, 1, wxEXPAND);
        gridsSizer->Add(rightPanel, 1, wxEXPAND);
        sizer->Add(gridsSizer, 1, wxEXPAND | wxALL, 10);

        wxBoxSizer* netRevenueSizer = new wxBoxSizer(wxHORIZONTAL);
        netRevenueSizer->Add(new wxStaticText(this, wxID_ANY, "SUM_INCOME: "), 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
        netRevenueText = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(150, 25), wxTE_READONLY);
        netRevenueSizer->Add(netRevenueText, 1, wxRIGHT, 5);
        sizer->Add(netRevenueSizer, 0, wxEXPAND | wxALL, 10);

        wxButton* backToMenuButton = new wxButton(this, wxID_ANY, "EXIT");
        sizer->Add(backToMenuButton, 0, wxALIGN_CENTER | wxTOP, 20);
        backToMenuButton->Bind(wxEVT_BUTTON, &CostCalculator::OnBackToMain, this);

        loadAllCosts();

        this->SetSizer(sizer);
        this->Layout();
    }

private:
    wxTextCtrl* dateField;
    wxTextCtrl* monthField;
    wxTextCtrl* yearField;
    wxTextCtrl* netRevenueText;
    wxGrid* scostGrid;
    wxGrid* revenueGrid;
    std::string lastSearchDate, lastSearchMonth, lastSearchYear;

    void loadAllCosts() {
        scostGrid->DeleteRows(0, scostGrid->GetNumberRows()); 
        for (const auto& cost : costlist) {
            scostGrid->AppendRows(1);
            scostGrid->SetCellValue(scostGrid->GetNumberRows() - 1, 0, cost.day + "/" + cost.month + "/" + cost.year);
            scostGrid->SetCellValue(scostGrid->GetNumberRows() - 1, 1, std::to_string(cost.revennue));
            scostGrid->SetCellValue(scostGrid->GetNumberRows() - 1, 2, cost.name);
        }
    }

    bool isRepeatSearch(const std::string& date, const std::string& month, const std::string& year) {
        return date == lastSearchDate && month == lastSearchMonth && year == lastSearchYear;
    }

 
    void OnSearch(wxCommandEvent& event) {
        scostGrid->DeleteRows(0, scostGrid->GetNumberRows());
        std::string date = dateField->GetValue().ToStdString();
        std::string month = monthField->GetValue().ToStdString();
        std::string year = yearField->GetValue().ToStdString();

        if (isRepeatSearch(date, month, year)) {
            wxMessageBox("you have searched this date before", "Error", wxOK | wxICON_ERROR);
            return;
        }

        if (!date.empty() && !month.empty() && !year.empty()) {
            searchday(date, month, year);
        }
        else if (date.empty() && !month.empty() && !year.empty()) {
            searchmon(month, year);
        }
        else if (date.empty() && month.empty() && !year.empty()) {
            searchyear(year);
        }
        
        lastSearchDate = date;
        lastSearchMonth = month;
        lastSearchYear = year;

        if (!scost.empty()) {
            revenueGrid->DeleteRows(0, revenueGrid->GetNumberRows()); 
            for (size_t i = 0; i < scost.size(); ++i) {
                scostGrid->AppendRows(1);
                scostGrid->SetCellValue(i, 0, scost[i].date);
                scostGrid->SetCellValue(i, 1, std::to_string(scost[i].revennue));
                scostGrid->SetCellValue(i, 2, scost[i].name);
            }
            costinspector();
            for (size_t i = 0; i < Date.size(); ++i) {
                revenueGrid->AppendRows(1);
                revenueGrid->SetCellValue(i, 0, Date[i]);
                revenueGrid->SetCellValue(i, 1, std::to_string(reve[i]));
            }
            double totalNetRevenue = totalreve(reve);
            netRevenueText->SetValue(std::to_string(totalNetRevenue));
        }
        else {
            wxMessageBox("can't find your data", "error", wxOK | wxICON_ERROR);
        }
    }

    void OnReset(wxCommandEvent& event) {
        dateField->Clear();
        monthField->Clear();
        yearField->Clear();
        scostGrid->DeleteRows(0, scostGrid->GetNumberRows());
        revenueGrid->DeleteRows(0, revenueGrid->GetNumberRows());
        netRevenueText->Clear();
    }

    void OnBackToMain(wxCommandEvent& event) {
        saveCostToFile();
        wxCommandEvent evt(wxEVT_COMMAND_BUTTON_CLICKED, 1000);
        wxPostEvent(GetParent(), evt);
    }
};

#endif 