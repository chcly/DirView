/*
-------------------------------------------------------------------------------
    Copyright (c) Charles Carley.

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
-------------------------------------------------------------------------------
*/
#include "DirView/Content/DirView.h"
#include <QBoxLayout>
#include <QSplitter>
#include <QWidget>
#include "DirListView.h"
#include "DirViewEditPath.h"
#include "DirViewInfo.h"
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

        _info = new DirViewInfo();
        _info->setMaximumHeight(Metrics::ctrlMin.height());
        _listView = new DirListView();

        const auto c3 = Qu::box(nullptr, Colors::Border);

        const auto hl = Qu::horizontal();
        hl->addWidget(
            Qu::split(
                Qu::split(
                    _info,
                    _listView,
                    Qt::Vertical),
                c3,
                Qt::Horizontal),
            1);
        layout->addWidget(_path);
        layout->addLayout(hl, 1);

        // view -> path
        _model.addOutput(
            [this](const String& str)
            {
                if (_path)
                    _path->setPath(str);
            });

        // path -> list
        // path -> canvas
        // path -> info
        _path->addOutput(
            [this](const String& str)
            {
                if (_listView)
                    _listView->setPath(str);
                if (_info)
                    _info->setPath(str);
            });

        // listItem -> path
        _listView->addOutput(
            [this](const String& str)
            {
                _path->setPath(str);
            });
    }
}  // namespace Rt2::View
