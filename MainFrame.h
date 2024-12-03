#pragma once
#include <wx/wx.h>

class MainFrame : public wxFrame
{
public:
    // Constructor for the MainFrame class
    // Need to learn more on constructors
    MainFrame(const wxString& title);

    void OnListChanged(wxCommandEvent& evt); // Defined in MainFrame.cpp

    void OnDropdownChanged(wxCommandEvent& dropdownevt);

private:
    wxPanel* contentPanel;

    wxPanel* graphPanel;

    void UpdateContent(int index); // Defined in MainFrame.cpp

    void updateGraph(int index);

    wxDECLARE_EVENT_TABLE(); // Needed
};
