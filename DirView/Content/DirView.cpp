#include "DirView/Content/DirView.h"
#include <QBoxLayout>
#include <QSplitter>
#include <QWidget>

#include "DirViewEditPath.h"
#include "View/Colors.h"
#include "View/Metrics.h"
#include "View/Qu.h"

namespace Rt2::View
{

    DirView::DirView(QWidget* parent) :
        LayoutView(parent)
    {
        construct();
    }

    DirView::~DirView() = default;

    void DirView::setPath(const String& path)
    {
        _model.setValue(path, ViewModel::OUTPUT);
    }

    void DirView::construct()
    {
        const auto layout = Qu::vertical();
        constructView(layout);
        setMinimumSize(Metrics::minWindow);
        setBorder(0);
        setPadding(0);


        _path = new EditPath();
        _path->setFixedHeight(Metrics::iconPadding.height() * 2);

        auto s1 = Qu::box(nullptr, Colors::Ac02);
        s1->setMinimumWidth(Metrics::minWindow.width());

        auto s2 = Qu::box(nullptr, Colors::Ac03);
        s2->setMinimumWidth(Metrics::minWindow.width());

        const auto c3 = Qu::box(nullptr, Colors::Ac04);

        const auto hl = Qu::horizontal();

        hl->addWidget(Qu::split(
                          Qu::split(
                              s1,
                              s2,
                              Qt::Vertical),
                          c3,
                          Qt::Horizontal),
                      1);
        layout->addLayout(hl, 1);
        layout->addWidget(_path);


        // view -> path
        _model.addOutput([this](const String& str)
        {
            if (_path)
                _path->setPath(str);
        });
    }
}  // namespace Rt2::View
