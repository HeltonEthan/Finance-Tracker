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
    TIMEFRAME_ID = 3,
};

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_LISTBOX(LISTBOX_ID, MainFrame::OnListChanged)
wxEND_EVENT_TABLE()

// MainWindow Editor
MainFrame::MainFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title)
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

    // TODO: Add event handling for case 2 and data input methods in MainWindow
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
        timeFrame = new wxChoice(contentPanel, TIMEFRAME_ID, wxDefaultPosition, wxDefaultSize, dateSelect);
        timeFrame->Select(0);
        contentSizer->Add(timeFrame, 0, wxTOP | wxLEFT, 10);

        graphPanel = new wxPanel(contentPanel, wxID_ANY);
        contentSizer->Add(graphPanel, 1, wxEXPAND | wxALL, 10);
        updateGraph(0);
        break;

    case 3:
        contentText = new wxStaticText(contentPanel, wxID_ANY, "Expenses Tracker", wxPoint(10, 10));
        contentSizer->Add(contentText, 0, wxTOP | wxLEFT, 10);
        break;
    }

    contentPanel->SetSizer(contentSizer);
    contentPanel->Layout();
}

// Dropdown box event handler
void MainFrame::updateGraph(int dropDownEvt)
{
    graphPanel->DestroyChildren();

    wxVector<wxString> labels;
    labels.push_back("January");
    labels.push_back("February");
    labels.push_back("March");
    labels.push_back("April");
    labels.push_back("May");
    labels.push_back("June");
    labels.push_back("July");
    wxChartsCategoricalData::ptr chartData = wxChartsCategoricalData::make_shared(labels);

    wxVector<wxDouble> points1;
    points1.push_back(3);
    points1.push_back(-2.5);
    points1.push_back(-1.2);
    points1.push_back(3);
    points1.push_back(6);
    points1.push_back(5);
    points1.push_back(1);
    wxChartsDoubleDataset::ptr dataset1(new wxChartsDoubleDataset("My First Dataset", points1));
    chartData->AddDataset(dataset1);

    wxVector<wxDouble> points2;
    points2.push_back(1);
    points2.push_back(-1.33);
    points2.push_back(2.5);
    points2.push_back(7);
    points2.push_back(3);
    points2.push_back(-1.8);
    points2.push_back(0.4);
    wxChartsDoubleDataset::ptr dataset2(new wxChartsDoubleDataset("My Second Dataset", points2));
    chartData->AddDataset(dataset2);

    wxLineChartCtrl* lineChartCtrl = nullptr;
    wxBoxSizer* graphSizer = new wxBoxSizer(wxHORIZONTAL);

    switch (dropDownEvt)
    {
    case 0:
        lineChartCtrl = new wxLineChartCtrl(graphPanel, wxID_ANY, chartData, wxCHARTSLINETYPE_STRAIGHT, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
        graphSizer->Add(lineChartCtrl, 1, wxEXPAND);
        graphPanel->SetSizer(graphSizer);
        break;

    case 1:
        break;

    case 2:
        break;

    case 3:
        break;

    case 4:
        break;

    default:
        return;
    }

    graphPanel->Layout();
}
