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
#include "Cache/ColorCache.h"
#include "Cache/PathCache.h"
#include "DirListView.h"
#include "DirViewCanvas.h"
#include "DirViewEditPath.h"
#include "DirViewInfo.h"
#include "View/Style.h"

namespace Rt2::View
{

    DirView::DirView(QWidget* parent) :
        LayoutView(parent)
    {
        // these should be made local
        new ColorCache();
        new PathCache();
        construct();
    }

    DirView::~DirView()
    {
        delete ColorCache::pointer();
        delete PathCache::pointer();
    }

    void DirView::setPath(const String& path)
    {
        _model.setValue(path, ViewModel::OUTPUT);
    }

    void DirView::construct()
    {
        const auto layout = Style::Layout::v0();
        constructView(layout);
        setMinimumSize(Style::Window::Small);
        setBackgroundColor(Style::Window::Swatches::Qb10::Qs1);

        _path = new EditPath();
        _path->setFixedHeight(Style::Window::BaseHeight);

        _info     = new DirViewInfo();
        _listView = new DirListView();
        _canvas   = new DirViewCanvas();

        const auto ml = Style::Layout::h0();
        const auto sb = Style::Widget::vs(_info, _listView);
        sb->setStretchFactor(0, 0);
        sb->setStretchFactor(1, 1);

        const auto sl = Style::Widget::hs(sb, _canvas);
        sl->setStretchFactor(0, 0);
        sl->setStretchFactor(1, 1);

        ml->addWidget(sl, 1);

        layout->addWidget(_path);
        layout->addLayout(ml, 1);

        // view -> path
        _model.addOutput(
            [this](const String& str)
            {
                if (_path)
                    _path->setPath(str);
            });
        // listItem -> path
        _listView->addOutput(
            [this](const QVariant& str)
            {
                _path->setPath(str.toString().toStdString());
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
                if (_canvas)
                    _canvas->setPath(str);
            });

        // canvas -> path
        _canvas->addOutput(
            [this](const String& str)
            {
                if (_path)
                    _path->setPath(str);
            });
    }
}  // namespace Rt2::View
