#include "DirView/Sample/Application.h"
#include <QApplication>
#include "DirView/Content/DirView.h"
#include "Utils/Exception.h"
#include "Utils/CommandLine/Parser.h"
#include "View/Metrics.h"
#include "View/Qu.h"

namespace Rt2::Samples
{
    bool Application::parse(int argc, char** argv)
    {
        CommandLine::Parser  p;
        if (p.parse(argc, argv, nullptr, 0) < 0)
            return false;

        if (p.hasArguments())
            _path = p.arguments().at(0);
        else
            _path = CommandLine::Parser::currentDirectory();
        return true;
    }

    int Application::go() const
    {
        int argc = 0;

        QApplication app(argc, nullptr);
        View::Qu::initResources(app);

        View::DirView win{};
        win.setMinimumSize(View::Metrics::minWindow);
        win.setPath(_path);
        win.showMaximized();

        return QApplication::exec();
    }

}  // namespace Rt2::Samples

int main(int argc, char* argv[])
{
    int rc = 1;
    try
    {
        Rt2::Samples::Application app;
        if (app.parse(argc, argv))
            rc = app.go();
    }
    catch (Rt2::Exception& ex)
    {
        Rt2::Console::writeLine(ex.what());
        rc = 1;
    }
    return rc;
}
