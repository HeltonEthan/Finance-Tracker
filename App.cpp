#include "App.h"
#include "MainFrame.h"

//Opens the main window
wxIMPLEMENT_APP(App);

//OnInit() defines the main window
bool App::OnInit()
{
    MainFrame* mainFrame = new MainFrame("Finance Tracker");
    mainFrame->SetClientSize(800, 600);
    mainFrame->Center();
    mainFrame->Show();

    return true;
}
