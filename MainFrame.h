#pragma once
#include <wx/wx.h>


class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString& title); //Constructor for the MainFrame class //Need to learn more on constructors
    void OnListChanged(wxCommandEvent& evt); //Defined in MainFrame.cpp

private:
    wxPanel* contentPanel;
    void UpdateContent(int index); //Defined in MainFrame.cpp

    wxDECLARE_EVENT_TABLE(); //Needed
};
