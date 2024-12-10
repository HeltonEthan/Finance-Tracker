#include "MainFrame.h"
#include <wx/wx.h>
#include <wxcharts.h>
#include <wxchart.h>
#include <wxchartslegendctrl.h>
#include <wxlinechartctrl.h>
#include <wxlinechart.h>
#include <wxchartsdataset.h>
#include <wx/statline.h>
#include <iostream>
#include <string>
#include <wx/textfile.h>
#include <wx/datetime.h>
#include <ctime>
#include <fstream>

// This is becoming hard to read; but I hate overcommenting

enum IDs
{
    LISTBOX_ID = 2,
    DATELIST_ID = 3,
    INCOME_SOURCE_BOX_ID = 4,
    OUTCOME_SOURCE_BOX_ID = 5,
    INPUT_MONEY_ID = 6,
    INPUT_OUT_MONEY_ID = 7,
    IN_REFRESH_ID = 8,
    OUT_REFRESH_ID = 9,
};

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_LISTBOX(LISTBOX_ID, MainFrame::OnListChanged)
EVT_LISTBOX(DATELIST_ID, MainFrame::OnDateListChanged)
EVT_LISTBOX(INCOME_SOURCE_BOX_ID, MainFrame::IncomeSourceBox)
EVT_LISTBOX(OUTCOME_SOURCE_BOX_ID, MainFrame::OutcomeSourceBox)
EVT_BUTTON(IN_REFRESH_ID, MainFrame::InRefresh)
EVT_BUTTON(OUT_REFRESH_ID, MainFrame::OutRefresh)
wxEND_EVENT_TABLE()

// MainWindow Editor
MainFrame::MainFrame(const wxString& title): wxFrame(NULL, wxID_ANY, title)
{
    wxPanel* mainPanel = new wxPanel(this);

    wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);

    wxArrayString tabs;
    tabs.Add("General Finances");
    tabs.Add("Statistics");
    tabs.Add("Expenses Tracker");

    // Constructing the Listbox
    wxListBox* listBox = new wxListBox(mainPanel, LISTBOX_ID, wxPoint(15, 15), wxSize(125, -1), tabs);

    contentPanel = new wxPanel(mainPanel, wxID_ANY);
    contentPanel->SetBackgroundColour(*wxWHITE);

    mainSizer->Add(listBox, 0, wxEXPAND | wxALL, 5);
    mainSizer->Add(contentPanel, 1, wxEXPAND | wxALL, 5);

    mainPanel->SetSizer(mainSizer);

    UpdateContent(0);
    listBox->Select(0);
}

wxTextCtrl* inputMoney = nullptr;
wxListBox* income_source_box = nullptr;
wxTextCtrl* inputOutMoney = nullptr;
wxListBox* outcome_source_box = nullptr;

// List event detection
void MainFrame::OnListChanged(wxCommandEvent& listEvt)
{
    int listIndex = listEvt.GetSelection();
    UpdateContent(listIndex);
}

void MainFrame::UpdateContent(int listIndex)
{
    contentPanel->DestroyChildren();

    wxStaticText* contentText = nullptr;
    wxStaticText* dateSelection = nullptr;
    wxChoice* timeFrame = nullptr;

    wxArrayString dateSelect;
    dateSelect.Add("All time");
    dateSelect.Add("1 Year");
    dateSelect.Add("6 Months");
    dateSelect.Add("1 Month");

    wxArrayString income_source;
    income_source.Add("Job");
    income_source.Add("Gift");
    income_source.Add("Investing");
    income_source.Add("Other");

    wxArrayString outcome_source;
    outcome_source.Add("Food");
    outcome_source.Add("Clothes");
    outcome_source.Add("Investing");
    outcome_source.Add("Other");

    wxBoxSizer* contentSizer = new wxBoxSizer(wxVERTICAL);
    wxListBox* dateListBox = nullptr;
    wxStaticText* inputPoint = nullptr;
    wxStaticText* input = nullptr;
    wxButton* inRefresh = nullptr;
    wxStaticLine* line = nullptr;
    wxStaticText* text = nullptr;
    wxButton* outRefresh = nullptr;

    switch (listIndex)
    {
    case 0:
        //TODO make event handling for all this shit
        contentText = new wxStaticText(contentPanel, wxID_ANY, "General Finances", wxPoint(10, 10));
        contentSizer->Add(contentText, 0, wxTOP | wxLEFT, 10);
        inputPoint = new wxStaticText(contentPanel, wxID_ANY, "Input today's earnings", wxPoint(10, 40));
        inRefresh = new wxButton(contentPanel, IN_REFRESH_ID, "Submit", wxPoint(100, 60));
        inputMoney = new wxTextCtrl(contentPanel, INPUT_MONEY_ID, "", wxPoint(10, 60), wxSize(85, 22));
        income_source_box = new wxListBox(contentPanel, INCOME_SOURCE_BOX_ID, wxPoint(32, 90), wxSize(125, -1), income_source);

        line = new wxStaticLine(contentPanel, wxID_ANY, wxPoint(185, 48), wxSize(2, 125), wxLI_VERTICAL);
        line = new wxStaticLine(contentPanel, wxID_ANY, wxPoint(130, 48), wxSize(58, 2), wxLI_HORIZONTAL);
        line = new wxStaticLine(contentPanel, wxID_ANY, wxPoint(5, 171), wxSize(181, 2), wxLI_HORIZONTAL);
        line = new wxStaticLine(contentPanel, wxID_ANY, wxPoint(5, 48), wxSize(2, 125), wxLI_VERTICAL);

        text = new wxStaticText(contentPanel, wxID_ANY, "Input today's spendings", wxPoint(210, 40));
        outRefresh = new wxButton(contentPanel, OUT_REFRESH_ID, "Submit", wxPoint(300, 60));
        inputOutMoney = new wxTextCtrl(contentPanel, INPUT_OUT_MONEY_ID, "", wxPoint(210, 60), wxSize(85, 22));
        outcome_source_box = new wxListBox(contentPanel, OUTCOME_SOURCE_BOX_ID, wxPoint(232, 90), wxSize(125, -1), outcome_source);

        line = new wxStaticLine(contentPanel, wxID_ANY, wxPoint(385, 48), wxSize(2, 125), wxLI_VERTICAL);
        line = new wxStaticLine(contentPanel, wxID_ANY, wxPoint(330, 48), wxSize(58, 2), wxLI_HORIZONTAL);
        line = new wxStaticLine(contentPanel, wxID_ANY, wxPoint(205, 171), wxSize(181, 2), wxLI_HORIZONTAL);
        line = new wxStaticLine(contentPanel, wxID_ANY, wxPoint(205, 48), wxSize(2, 125), wxLI_VERTICAL);
        
        break;

    case 1:
        contentText = new wxStaticText(contentPanel, wxID_ANY, "Statistics", wxPoint(10, 10));
        contentSizer->Add(contentText, 0, wxTOP | wxLEFT, 10);
        break;

    case 2:
        contentText = new wxStaticText(contentPanel, wxID_ANY, "Expenses Visualizer", wxPoint(10, 10));
        contentSizer->Add(contentText, 0, wxTOP | wxLEFT, 10);
        dateSelection = new wxStaticText(contentPanel, wxID_ANY, "Select a time frame:", wxPoint(10, 50));
        contentSizer->Add(dateSelection, 0, wxTOP | wxLEFT, 10);
        dateListBox = new wxListBox(contentPanel, DATELIST_ID, wxPoint(125, 10), wxSize(125, -1), dateSelect);
        contentSizer->Add(dateListBox, 0, wxTOP | wxLEFT, 10);
        dateListBox->Select(0);

        graphPanel = new wxPanel(contentPanel, wxID_ANY);
        contentSizer->Add(graphPanel, 1, wxEXPAND | wxHORIZONTAL, 10);
        UpdateGraph(0);
        break;
    }

    contentPanel->SetSizer(contentSizer);
    contentPanel->Layout();
}

int OutlistIndex;

void MainFrame::OutcomeSourceBox(wxCommandEvent& Evt)
{
    OutlistIndex = Evt.GetSelection();
}

int IncomelistIndex;

void MainFrame::IncomeSourceBox(wxCommandEvent& Evt)
{
    IncomelistIndex = Evt.GetSelection();
}

void MainFrame::UpdateOnINpress(wxString placeHolderForMoney, int listIndex)
{
    double money;
    placeHolderForMoney.ToDouble(&money);

    wxString moneytype[4];
    moneytype[0] = "job";
    moneytype[1] = "gift";
    moneytype[2] = "investing";
    moneytype[3] = "other";

    time_t timestamp;
    time(&timestamp);

    struct tm* localTime = localtime(&timestamp);

    char formattedDate[9];
    strftime(formattedDate, sizeof(formattedDate), "%m %d %y", localTime);

    std::ofstream outFile("moneyIn.txt", std::ios::app);

    outFile << money << "," << moneytype[listIndex] << "," << formattedDate << std::endl;


    //Keep this last in the function.
    inputMoney->Destroy();
    income_source_box->Deselect(listIndex);
    inputMoney = new wxTextCtrl(contentPanel, INPUT_MONEY_ID, "", wxPoint(10, 60), wxSize(85, 22));
}

void MainFrame::UpdateOnOUTpress(wxString placeHolderForMoney, int listIndex)
{
    double money;
    placeHolderForMoney.ToDouble(&money);

    wxString moneytype[4];
    moneytype[0] = "food";
    moneytype[1] = "clothing";
    moneytype[2] = "investing";
    moneytype[3] = "other";

    time_t timestamp;
    time(&timestamp);

    struct tm* localTime = localtime(&timestamp);

    char formattedDate[9];  
    strftime(formattedDate, sizeof(formattedDate), "%m %d %y", localTime);

    std::ofstream outFile("moneyOut.txt", std::ios::app);

    outFile << money << "," << moneytype[listIndex] << "," << formattedDate << std::endl;


    //Keep this last in the function
    inputOutMoney->Destroy();
    outcome_source_box->Deselect(OutlistIndex);
    inputOutMoney = new wxTextCtrl(contentPanel, INPUT_OUT_MONEY_ID, "", wxPoint(210, 60), wxSize(85, 22));
}

void MainFrame::InRefresh(wxCommandEvent& Evt)
{
    UpdateOnINpress(inputMoney->GetValue(), IncomelistIndex);
}

void MainFrame::OutRefresh(wxCommandEvent& Evt)
{
    UpdateOnOUTpress(inputOutMoney->GetValue(), OutlistIndex);
}

void MainFrame::OnDateListChanged(wxCommandEvent& listEvt)
{
    int listIndex = listEvt.GetSelection();
    UpdateGraph(listIndex);
}

void MainFrame::UpdateGraph(int listIndex)
{
    graphPanel->DestroyChildren();

    //Data set all time

    wxVector<wxString> allTimeLabels;
    allTimeLabels.push_back("");
    wxChartsCategoricalData::ptr allTimeData = wxChartsCategoricalData::make_shared(allTimeLabels);

    //data set yearly

    wxVector<wxString> yearlyLabels;
    yearlyLabels.push_back("Jan");
    yearlyLabels.push_back("Feb");
    yearlyLabels.push_back("March");
    yearlyLabels.push_back("April");
    yearlyLabels.push_back("May");
    yearlyLabels.push_back("June");
    yearlyLabels.push_back("July");
    yearlyLabels.push_back("Aug");
    yearlyLabels.push_back("Sept");
    yearlyLabels.push_back("Oct");
    yearlyLabels.push_back("Nov");
    yearlyLabels.push_back("Dec");
    yearlyLabels.push_back("");
    wxChartsCategoricalData::ptr yearlyData = wxChartsCategoricalData::make_shared(yearlyLabels);

    //data set 6 months

    wxVector<wxString> biYearlyLabels;
    biYearlyLabels.push_back("");
    biYearlyLabels.push_back("");
    biYearlyLabels.push_back("");
    biYearlyLabels.push_back("");
    biYearlyLabels.push_back("");
    biYearlyLabels.push_back("");
    wxChartsCategoricalData::ptr biYearlyData = wxChartsCategoricalData::make_shared(biYearlyLabels);

    wxVector<wxString> monthLabels;
    monthLabels.push_back("");
    monthLabels.push_back("");
    monthLabels.push_back("");
    monthLabels.push_back("");
    wxChartsCategoricalData::ptr monthData = wxChartsCategoricalData::make_shared(monthLabels);

    //data set 1 month

    wxLineChartCtrl* lineChartCtrl = nullptr;
    wxBoxSizer* graphSizer = new wxBoxSizer(wxHORIZONTAL);

    switch (listIndex)
    {
    case 0:
        lineChartCtrl = new wxLineChartCtrl(graphPanel, wxID_ANY, allTimeData, wxCHARTSLINETYPE_STRAIGHT, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
        graphSizer->Add(lineChartCtrl, 1, wxEXPAND);
        graphPanel->SetSizer(graphSizer);

        break;

    case 1:
        lineChartCtrl = new wxLineChartCtrl(graphPanel, wxID_ANY, yearlyData, wxCHARTSLINETYPE_STRAIGHT, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
        graphSizer->Add(lineChartCtrl, 1, wxEXPAND);
        graphPanel->SetSizer(graphSizer);

        break;

    case 2:
        lineChartCtrl = new wxLineChartCtrl(graphPanel, wxID_ANY, biYearlyData, wxCHARTSLINETYPE_STRAIGHT, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
        graphSizer->Add(lineChartCtrl, 1, wxEXPAND);
        graphPanel->SetSizer(graphSizer);

        break;

    case 3:
        lineChartCtrl = new wxLineChartCtrl(graphPanel, wxID_ANY, monthData, wxCHARTSLINETYPE_STRAIGHT, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
        graphSizer->Add(lineChartCtrl, 1, wxEXPAND);
        graphPanel->SetSizer(graphSizer);

        break;
    }

    graphPanel->Layout();
    graphPanel->SetSizer(graphSizer);
}
