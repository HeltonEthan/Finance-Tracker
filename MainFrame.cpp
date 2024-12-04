#include "MainFrame.h"
#include <wx/wx.h>
#include <wxcharts.h>
#include <wxchart.h>
#include <wxchartslegendctrl.h>
#include <wxlinechartctrl.h>
#include <wxlinechart.h>
#include <wxchartsdataset.h>

// This is becoming hard to read; but I hate overcommenting

enum IDs
{
    LISTBOX_ID = 2,
    DATELIST_ID = 3,
};

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_LISTBOX(LISTBOX_ID, MainFrame::OnListChanged)
EVT_LISTBOX(DATELIST_ID, MainFrame::OnDateListChanged)
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
    tabs.Add("Expenses History");

    // Constructing the Listbox
    wxListBox* listBox = new wxListBox(mainPanel, LISTBOX_ID, wxPoint(15, 15), wxSize(125, -1), tabs);

    contentPanel = new wxPanel(mainPanel, wxID_ANY);
    contentPanel->SetBackgroundColour(*wxWHITE);

    mainSizer->Add(listBox, 0, wxEXPAND | wxALL, 5);
    mainSizer->Add(contentPanel, 1, wxEXPAND | wxALL, 5);

    mainPanel->SetSizer(mainSizer);

    UpdateContent(0);
}

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

    wxArrayString dateSelect; // Need to make events for these
    dateSelect.Add("All time");
    dateSelect.Add("1 Year");
    dateSelect.Add("6 Months");
    dateSelect.Add("1 Month");
    dateSelect.Add("2 Weeks");

    wxBoxSizer* contentSizer = new wxBoxSizer(wxVERTICAL);

    wxListBox* dateListBox = nullptr;

    switch (listIndex)
    {
    case 0:
        contentText = new wxStaticText(contentPanel, wxID_ANY, "General Finances", wxPoint(10, 10));
        contentSizer->Add(contentText, 0, wxTOP | wxLEFT, 10);
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
        contentSizer->Add(graphPanel, 1, wxEXPAND | wxALL, 10);
        UpdateGraph(0);
        break;

    case 3:
        contentText = new wxStaticText(contentPanel, wxID_ANY, "Expenses Tracker", wxPoint(10, 10));
        contentSizer->Add(contentText, 0, wxTOP | wxLEFT, 10);
        break;
    }

    contentPanel->SetSizer(contentSizer);
    contentPanel->Layout();
}

//Not working
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
    allTimeLabels.push_back("1/23");
    allTimeLabels.push_back("");
    allTimeLabels.push_back("3/23");
    allTimeLabels.push_back("");
    allTimeLabels.push_back("5/23");
    allTimeLabels.push_back("");
    allTimeLabels.push_back("7/23");
    allTimeLabels.push_back("");
    allTimeLabels.push_back("9/23");
    allTimeLabels.push_back("");
    allTimeLabels.push_back("11/23");
    allTimeLabels.push_back("");
    allTimeLabels.push_back("1/24");
    allTimeLabels.push_back("");
    allTimeLabels.push_back("3/24");
    allTimeLabels.push_back("");
    allTimeLabels.push_back("5/24");
    allTimeLabels.push_back("");
    allTimeLabels.push_back("7/24");
    allTimeLabels.push_back("");
    allTimeLabels.push_back("9/24");
    allTimeLabels.push_back("");
    allTimeLabels.push_back("11/24");
    allTimeLabels.push_back("");
    allTimeLabels.push_back("");
    wxChartsCategoricalData::ptr allTimeData = wxChartsCategoricalData::make_shared(allTimeLabels);

    wxVector<wxDouble> allTimePoints;
    allTimePoints.push_back(600);
    allTimePoints.push_back(625);
    allTimePoints.push_back(642.2);
    allTimePoints.push_back(730);
    allTimePoints.push_back(654);
    allTimePoints.push_back(576);
    allTimePoints.push_back(648.4);
    allTimePoints.push_back(632);
    allTimePoints.push_back(643);
    allTimePoints.push_back(723);
    allTimePoints.push_back(687);
    allTimePoints.push_back(645);
    allTimePoints.push_back(644);
    allTimePoints.push_back(678);
    allTimePoints.push_back(702);
    allTimePoints.push_back(657);
    allTimePoints.push_back(654);
    allTimePoints.push_back(678);
    allTimePoints.push_back(675);
    allTimePoints.push_back(654);
    allTimePoints.push_back(645);
    allTimePoints.push_back(678);
    allTimePoints.push_back(645);
    allTimePoints.push_back(694);
    wxChartsDoubleDataset::ptr allTimeDataSet(new wxChartsDoubleDataset("All time dataset", allTimePoints));
    allTimeData->AddDataset(allTimeDataSet);

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

    wxVector<wxDouble> yearlyPoints;
    yearlyPoints.push_back(654);
    yearlyPoints.push_back(668);
    yearlyPoints.push_back(722);
    yearlyPoints.push_back(637);
    yearlyPoints.push_back(664);
    yearlyPoints.push_back(698);
    yearlyPoints.push_back(645);
    yearlyPoints.push_back(664);
    yearlyPoints.push_back(675);
    yearlyPoints.push_back(638);
    yearlyPoints.push_back(655);
    yearlyPoints.push_back(704);
    wxChartsDoubleDataset::ptr yearlyDataSet(new wxChartsDoubleDataset("Yearly data set", yearlyPoints));
    yearlyData->AddDataset(yearlyDataSet);
    

    wxLineChartCtrl* allTimeCtrl = nullptr;
    wxLineChartCtrl* yearlyCtrl = nullptr;
    wxBoxSizer* graphSizer = new wxBoxSizer(wxHORIZONTAL);

    switch (listIndex)
    {
    case 0:
        allTimeCtrl = new wxLineChartCtrl(graphPanel, wxID_ANY, allTimeData, wxCHARTSLINETYPE_STRAIGHT, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
        graphSizer->Add(allTimeCtrl, 1, wxEXPAND);
        graphPanel->SetSizer(graphSizer);

        break;

    case 1:
        yearlyCtrl = new wxLineChartCtrl(graphPanel, wxID_ANY, yearlyData, wxCHARTSLINETYPE_STRAIGHT, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
        graphSizer->Add(yearlyCtrl, 1, wxEXPAND);
        graphPanel->SetSizer(graphSizer);

        break;

    case 2:
        
        break;

    case 3:
        
        break;

    case 4:
        
        break;
    }

    graphPanel->Layout();
    graphPanel->SetSizer(graphSizer);
}
