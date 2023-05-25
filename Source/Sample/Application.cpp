#include <QApplication>
#include "Utils/Exception.h"
#include "Source/Sample/Application.h"
#include "Source/Content/MainWindow.h"
#include "View/Qu.h"


namespace Rt2::QtTemplate
{
    bool Application::parse(int argc, char** argv)
    {
        return true;
    }

    int Application::go()
    {

        int          argc = 0;
        QApplication app(argc, nullptr);
        View::Qu::initResources(app);

        MainWindow win{};
        win.post();

        return QApplication::exec();
    }

}  // namespace Rt2::DirList

int main(int argc, char* argv[])
{
    int rc = 1;
    try
    {
        Rt2::QtTemplate::Application app;
        if (app.parse(argc, argv))
            rc = app.go();
    }
    catch (Rt2::Exception& ex)
    {
        Rt2::Console::writeLine(ex.what());
        // unused outside of flagging that an
        // error occurred.
        rc = 1;
    }
    return rc;
}
