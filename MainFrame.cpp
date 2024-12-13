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
#include <sstream>
#include <wxpiechart.h>
#include <wxpiechartctrl.h>
#include <wxpiechartoptions.h>

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

    //Data handling for the pie chart yoo

    std::string yearIN_Line;
    std::ifstream yearIN_File("moneyIn.txt");

    double job = 0;
    double other = 0;
    double gift = 0;
    double investing = 0;

    while (std::getline(yearIN_File, yearIN_Line))
    {
        std::istringstream lineStream(yearIN_Line);
        std::string MoneyStr, Type, dateStr;
        std::getline(lineStream, MoneyStr, ',');
        std::getline(lineStream, Type, ',');
        std::getline(lineStream, dateStr, ',');

        double moneyIN = std::stod(MoneyStr);

        if (Type == "job")
        {
            job += moneyIN;
        }
        else if (Type == "investing")
        {
            investing += moneyIN;
        }
        else if (Type == "gift")
        {
            gift += moneyIN;
        }
        else 
        {
            other += moneyIN;
        }
    }

    wxChartsLegendCtrl* legendCtrl = nullptr;
    wxPieChartCtrl* pieChartCtrl = nullptr;
    wxBoxSizer* pieSizer = nullptr;
    wxPieChartData::ptr chartData = wxPieChartData::make_shared();

    switch (listIndex)
    {
    case 0:
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

        chartData->AppendSlice(wxChartSliceData(job, wxColor(0x4A46F7), "Job"));
        chartData->AppendSlice(wxChartSliceData(investing, wxColor(0xBDBF46), "Investing"));
        chartData->AppendSlice(wxChartSliceData(gift, wxColor(0x5CB4FD), "Gift"));
        chartData->AppendSlice(wxChartSliceData(other, wxColor(0xB19F94), "Other"));

        piePanel = new wxPanel(contentPanel, wxID_ANY, wxPoint(410, 10), wxSize(200, 200));

        pieChartCtrl = new wxPieChartCtrl(piePanel, wxID_ANY, chartData, wxPoint(25, 25), wxSize(175, 175), wxBORDER_NONE);


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

void MainFrame::LabelHandler()
{

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

    //labels yearly

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

    //Calculations and data processing for yearly IN

    std::string yearIN_Line;
    std::ifstream yearIN_File("moneyIn.txt");

    wxVector<wxDouble> yearPointsIN;

    time_t timestamp;
    time(&timestamp);

    struct tm* localTime = localtime(&timestamp);

    char yearDate[3];
    strftime(yearDate, sizeof(yearDate), "%y", localTime);

    char monthDate[3];
    strftime(monthDate, sizeof(monthDate), "%m", localTime);

    double currentYear = std::stod(yearDate);

    int currentMonth = std::stoi(monthDate);

    double YTD = std::stod(yearDate);

    double IN_JAN = 0;
    double IN_FEB = 0;
    double IN_MAR = 0;
    double IN_APR = 0;
    double IN_MAY = 0;
    double IN_JUN = 0;
    double IN_JUL = 0;
    double IN_AUG = 0;
    double IN_SEP = 0;
    double IN_OCT = 0;
    double IN_NOV = 0;
    double IN_DEC = 0;

    while (std::getline(yearIN_File, yearIN_Line))
    {
        std::istringstream lineStream(yearIN_Line);
        std::string yearOUT_MoneyStr, yearOUT_Type, dateStr;
        std::getline(lineStream, yearOUT_MoneyStr, ',');
        std::getline(lineStream, yearOUT_Type, ',');
        std::getline(lineStream, dateStr, ',');

        std::istringstream dateStream(dateStr);
        std::string month, day, year;
        std::getline(dateStream, month, ' ');
        std::getline(dateStream, day, ' ');
        std::getline(dateStream, year);

        double monthNUM = std::stod(month);
        double yearNUM = std::stod(year);

        double yearIN_Money = std::stod(yearOUT_MoneyStr);
        
        if (currentYear == yearNUM)
        {
            if (monthNUM == 1)
                IN_JAN += yearIN_Money;
            else if (monthNUM == 2)
                IN_FEB += yearIN_Money;
            else if (monthNUM == 3)
                IN_MAR += yearIN_Money;
            else if (monthNUM == 4)
                IN_APR += yearIN_Money;
            else if (monthNUM == 5)
                IN_MAY += yearIN_Money;
            else if (monthNUM == 6)
                IN_JUN += yearIN_Money;
            else if (monthNUM == 7)
                IN_JUL += yearIN_Money;
            else if (monthNUM == 8)
                IN_AUG += yearIN_Money;
            else if (monthNUM == 9)
                IN_SEP += yearIN_Money;
            else if (monthNUM == 10)
                IN_OCT += yearIN_Money;
            else if (monthNUM == 11)
                IN_NOV += yearIN_Money;
            else if (monthNUM == 12)
                IN_DEC += yearIN_Money;
        }
    }

    yearPointsIN.push_back(IN_JAN);
    yearPointsIN.push_back(IN_FEB);
    yearPointsIN.push_back(IN_MAR);
    yearPointsIN.push_back(IN_APR);
    yearPointsIN.push_back(IN_MAY);
    yearPointsIN.push_back(IN_JUN);
    yearPointsIN.push_back(IN_JUL);
    yearPointsIN.push_back(IN_AUG);
    yearPointsIN.push_back(IN_SEP);
    yearPointsIN.push_back(IN_OCT);
    yearPointsIN.push_back(IN_NOV);
    yearPointsIN.push_back(IN_DEC);

    wxChartsDoubleDataset::ptr yearlyDataIN(new wxChartsDoubleDataset("Yearly points IN", yearPointsIN));
    yearlyData->AddDataset(yearlyDataIN);

    //Calculations and data processing for yearly OUT

    std::string yearOUT_Line;
    std::ifstream yearOUT_File("moneyOut.txt");

    wxVector<wxDouble> yearPointsOUT;

    double OUT_JAN = 0;
    double OUT_FEB = 0;
    double OUT_MAR = 0;
    double OUT_APR = 0;
    double OUT_MAY = 0;
    double OUT_JUN = 0;
    double OUT_JUL = 0;
    double OUT_AUG = 0;
    double OUT_SEP = 0;
    double OUT_OCT = 0;
    double OUT_NOV = 0;
    double OUT_DEC = 0;

    while (std::getline(yearIN_File, yearIN_Line))
    {
        std::istringstream lineStream(yearIN_Line);
        std::string yearOUT_MoneyStr, yearOUT_Type, dateStr;
        std::getline(lineStream, yearOUT_MoneyStr, ',');
        std::getline(lineStream, yearOUT_Type, ',');
        std::getline(lineStream, dateStr, ',');

        std::istringstream dateStream(dateStr);
        std::string month, day, year;
        std::getline(dateStream, month, ' ');
        std::getline(dateStream, day, ' ');
        std::getline(dateStream, year);

        double yearOUT_Money = std::stod(yearOUT_MoneyStr);

        double monthNUM = std::stod(month);
        double yearNUM = std::stod(year);

        if (currentYear == yearNUM)
        {
            if (monthNUM == 1)
                OUT_JAN += yearOUT_Money;
            else if (monthNUM == 2)
                OUT_FEB += yearOUT_Money;
            else if (monthNUM == 3)
                OUT_MAR += yearOUT_Money;
            else if (monthNUM == 4)
                OUT_APR += yearOUT_Money;
            else if (monthNUM == 5)
                OUT_MAY += yearOUT_Money;
            else if (monthNUM == 6)
                OUT_JUN += yearOUT_Money;
            else if (monthNUM == 7)
                OUT_JUL += yearOUT_Money;
            else if (monthNUM == 8)
                OUT_AUG += yearOUT_Money;
            else if (monthNUM == 9)
                OUT_SEP += yearOUT_Money;
            else if (monthNUM == 10)
                OUT_OCT += yearOUT_Money;
            else if (monthNUM == 11)
                OUT_NOV += yearOUT_Money;
            else if (monthNUM == 12)
                OUT_DEC += yearOUT_Money;
        }
    }

    yearPointsIN.push_back(OUT_JAN);
    yearPointsIN.push_back(OUT_FEB);
    yearPointsIN.push_back(OUT_MAR);
    yearPointsIN.push_back(OUT_APR);
    yearPointsIN.push_back(OUT_MAY);
    yearPointsIN.push_back(OUT_JUN);
    yearPointsIN.push_back(OUT_JUL);
    yearPointsIN.push_back(OUT_AUG);
    yearPointsIN.push_back(OUT_SEP);
    yearPointsIN.push_back(OUT_OCT);
    yearPointsIN.push_back(OUT_NOV);
    yearPointsIN.push_back(OUT_DEC);

    wxChartsDoubleDataset::ptr yearlyDataOUT(new wxChartsDoubleDataset("Yearly points OUT", yearPointsOUT));
    yearlyData->AddDataset(yearlyDataOUT);

    //data set 6 months

    wxVector<wxString> biYearlyLabels;
    biYearlyLabels.push_back("");
    biYearlyLabels.push_back("");
    biYearlyLabels.push_back("");
    biYearlyLabels.push_back("");
    biYearlyLabels.push_back("");
    biYearlyLabels.push_back("");
    wxChartsCategoricalData::ptr biYearlyData = wxChartsCategoricalData::make_shared(biYearlyLabels);

    //data set 1 months

    wxVector<wxString> monthLabels;
    monthLabels.push_back("");
    monthLabels.push_back("");
    monthLabels.push_back("");
    monthLabels.push_back("");
    wxChartsCategoricalData::ptr monthData = wxChartsCategoricalData::make_shared(monthLabels);

    wxLineChartCtrl* lineChartCtrl = nullptr;
    wxBoxSizer* graphSizer = new wxBoxSizer(wxHORIZONTAL);

    //This is where handling is for pulling shit out of the files (ALL TIME)

    //ALLTIME OUT & LABELS

    std::string outLine;
    std::ifstream outFile("moneyOut.txt");

    wxVector<wxString> allTimeLabels;
    wxVector<wxDouble> allTimePointsOUT;

    while (std::getline(outFile, outLine))
    {
        std::istringstream lineStream(outLine);
        std::string outMoneyStr, outType, dateStr;
        std::getline(lineStream, outMoneyStr, ',');
        std::getline(lineStream, outType, ',');
        std::getline(lineStream, dateStr, ',');

        std::istringstream dateStream(dateStr);
        std::string month, day, year;
        std::getline(dateStream, month, ' ');
        std::getline(dateStream, day, ' ');
        std::getline(dateStream, year);

        double monthNUM = std::stod(month);
        double yearNUM = std::stod(year);

        wxDouble money = std::stod(outMoneyStr);
        allTimePointsOUT.push_back(money);
        allTimeLabels.push_back("");
    }

    wxChartsCategoricalData::ptr allTimeData = wxChartsCategoricalData::make_shared(allTimeLabels);
    wxChartsDoubleDataset::ptr allTimeDataOUT(new wxChartsDoubleDataset("All Time Points OUT", allTimePointsOUT));

    allTimeData->AddDataset(allTimeDataOUT);

    //ALL TIME IN

    std::string inLine;
    std::ifstream inFile("moneyIn.txt");

    wxVector<wxDouble> allTimePointsIN;

    while (std::getline(inFile, inLine))
    {
        std::istringstream lineStream(inLine);
        std::string inMoneyStr, inType, inDateStr;
        std::getline(lineStream, inMoneyStr, ',');
        std::getline(lineStream, inType, ',');
        std::getline(lineStream, inDateStr, ',');

        wxDouble inMoney = std::stod(inMoneyStr);
        allTimePointsIN.push_back(inMoney);
    }

    wxChartsDoubleDataset::ptr allTimeDataIN(new wxChartsDoubleDataset("All Time Points OUT", allTimePointsIN));
    allTimeData->AddDataset(allTimeDataIN);

    //End of (ALL TIME) Data handling

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
