#include "MainWindow.h"
#include <QBoxLayout>
#include <QLabel>
#include <QWidget>
#include "View/Colors.h"
#include "View/Metrics.h"
#include "View/Qu.h"

namespace Rt2::QtTemplate
{

    MainWindow::MainWindow(QWidget* parent) :
        LayoutView(parent)
    {
        construct();
    }

    MainWindow::~MainWindow() = default;

    void MainWindow::construct()
    {
        const auto layout = View::Qu::vertical();
        constructView(layout);
        setMinimumSize(View::Metrics::minWindow);
        setBorder(0);
        setPadding(0);

        layout->addWidget(
            View::Qu::text("Hello World", View::Colors::ForegroundLight),
            1,
            Qt::AlignCenter);
    }

    void MainWindow::post()
    {
        show();
    }

}  // namespace Rt2::QtTemplate
