#include "MainFrame.h"

enum IDs
{
    LISTBOX_ID = 2,
    TIMEFRAME_ID = 3,
};


wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_LISTBOX(LISTBOX_ID, MainFrame::OnListChanged)
wxEND_EVENT_TABLE()

MainFrame::MainFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title)
{
    wxPanel* mainPanel = new wxPanel(this);

    wxArrayString tabs;
    tabs.Add("General Finances");
    tabs.Add("Statistics");
    tabs.Add("Expenses Tracker");
    tabs.Add("Expenses History");

    //Constructing the Listbox
    wxListBox* listBox = new wxListBox(mainPanel, LISTBOX_ID, wxPoint(15, 15), wxSize(125, -1), tabs);

    contentPanel = new wxPanel(mainPanel, wxID_ANY, wxPoint(150, 15), wxSize(600, 500));
    contentPanel->SetBackgroundColour(*wxWHITE);
    UpdateContent(0);
}

//List event detection
void MainFrame::OnListChanged(wxCommandEvent& evt)
{
    int index = evt.GetSelection();
    UpdateContent(index);
}

void MainFrame::UpdateContent(int index)
{

    contentPanel->DestroyChildren();
    wxStaticText* contentText = nullptr;
    wxStaticText* dateSelection = nullptr;
    wxChoice* timeFrame = nullptr;

    wxArrayString dateSelect; //Need to make events for these
    dateSelect.Add("All time");
    dateSelect.Add("1 Year");
    dateSelect.Add("6 Months");
    dateSelect.Add("1 Month");
    dateSelect.Add("2 Weeks");


    //TODO: add event handling for case 2 and data input methods in MainWindow
    switch (index)
    {
    case 0:
        contentText = new wxStaticText(contentPanel, wxID_ANY, "General Finances", wxPoint(10, 10));
        break;
    case 1:
        contentText = new wxStaticText(contentPanel, wxID_ANY, "Statistics", wxPoint(10, 10));
        break;
    case 2:
        contentText = new wxStaticText(contentPanel, wxID_ANY, "Expenses Tracker", wxPoint(10, 10));
        dateSelection = new wxStaticText(contentPanel, wxID_ANY, "Select a time frame:", wxPoint(10, 50));
        timeFrame = new wxChoice(contentPanel, TIMEFRAME_ID, wxPoint(125, 48), wxSize(100, -1), dateSelect);
        timeFrame->Select(0);
        break;
    case 3:
        contentText = new wxStaticText(contentPanel, wxID_ANY, "Expenses History", wxPoint(10, 10));
        break;
    }
}
