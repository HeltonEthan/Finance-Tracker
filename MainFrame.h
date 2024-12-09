#pragma once
#include <wx/wx.h>

class MainFrame : public wxFrame
{
public:
    // Constructor for the MainFrame class
    // Need to learn more on constructors
    MainFrame(const wxString& title);

    void OnListChanged(wxCommandEvent& evt); // Defined in MainFrame.cpp

    void OnDateListChanged(wxCommandEvent& comboBoxEvt);

    void OutcomeSourceBox(wxCommandEvent& Evt);

    void IncomeSourceBox(wxCommandEvent& Evt);

    void InRefresh(wxCommandEvent& Evt);

    void OutRefresh(wxCommandEvent& Evt);

private:
    wxPanel* contentPanel;

    wxPanel* graphPanel;

    void UpdateContent(int index); // Defined in MainFrame.cpp

    void UpdateGraph(int index);

    void UpdateOnINpress(std::string money);

    void ImportINListBox();

    void ImportOUTListBox();

    void UpdateOnOUTpress();

    wxDECLARE_EVENT_TABLE(); // Needed
};
