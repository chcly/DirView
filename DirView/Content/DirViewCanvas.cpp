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
#include "DirView/Content/DirViewCanvas.h"
#include <QGraphicsView>
#include <QMouseEvent>
#include <QWidget>
#include "DirView/Content/Builder/Events.h"
#include "DirView/Content/Builder/Manager.h"
#include "DirView/Content/DirViewEvent.h"
#include "View/Colors.h"
#include "View/Metrics.h"
#include "View/Qu.h"

class QGraphicsView;
class QGraphicsScene;

namespace Rt2::View
{
    constexpr qreal Spacing  = Metrics::defaultTextSize + 6;
    constexpr qreal Sx       = Spacing / 2;
    constexpr qreal ItemSize = DirViewItem::size;

    DirViewCanvas::DirViewCanvas(QWidget* parent) :
        QGraphicsView(parent)
    {
        construct();
    }

    DirViewCanvas::~DirViewCanvas()
    {
        delete _scene;
        delete _manager;
    }

    void DirViewCanvas::construct()
    {
        setMouseTracking(true);
        setUpdatesEnabled(true);
        setRenderHint(QPainter::Antialiasing);
        setMinimumWidth(Metrics::minWindow.width());
        setBackgroundBrush(Colors::Border);
        setTransformationAnchor(AnchorViewCenter);
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        setInteractive(true);
        resetTransform();

        delete _scene;
        _scene = new QGraphicsScene(this);
        setScene(_scene);
        updateBounds();

        _manager = new Builder::Manager(this);
    }

    void DirViewCanvas::updateBounds()
    {
        const QRectF r = _scene->itemsBoundingRect();
        setSceneRect(
            {
                0,
                0,
                Max((qreal)width() - Spacing, r.width() - Spacing),
                Max((qreal)height(), r.height() + 2 * Spacing),
            });
    }

    void DirViewCanvas::layout()
    {
        _shelf = {Sx, Sx};
        _cur = 0;

        const auto& items = _scene->items();
        for (const auto item : items)
            updateItem((DirViewItem*)item);

        update();
    }

    void DirViewCanvas::updateItem(DirViewItem* item)
    {
        if (!item) return;

        item->setPosition(_shelf);

        if (_cur + 1 < _nrPerW)
        {
            ++_cur;
            _shelf.setX(_shelf.x() + item->width() + Spacing);
        }
        else
        {
            _cur = 0;
            _shelf.setX(Sx);
            _shelf.setY(_shelf.y() + item->height() + Spacing);
        }
        updateBounds();
    }

    void DirViewCanvas::push(const Directory& directory)
    {
        DirViewItem* item = new DirViewItem(directory, this);
        item->setFlags(QGraphicsItem::ItemIsSelectable);
        _scene->addItem(item);
        updateItem(item);
        update();
    }

    void DirViewCanvas::setPath(const String& path)
    {
        _cur   = 0;
        _shelf = {Sx, Sx};
        updateBounds();
        _scene->clear();
        _manager->build({path, 0, 0});
    }

    void DirViewCanvas::addOutput(const StringModel::Observer& ot)
    {
        _model.addOutput(ot);
    }

    bool DirViewCanvas::event(QEvent* event)
    {
        if ((int)event->type() == Builder::DirPushEventCode)
        {
            if (const Builder::DirPushEvent* de =
                    (Builder::DirPushEvent*)event)
            {
                push(de->directory());
            }
            event->accept();
            return true;
        }

        if ((int)event->type() == DirClickEventCode)
        {
            if (const DirClickEvent* de =
                    (DirClickEvent*)event)
                _model.setValue(de->directory(), ViewModel::OUTPUT);
            event->accept();
            return true;
        }

        return QGraphicsView::event(event);
    }

    void DirViewCanvas::resizeEvent(QResizeEvent* event)
    {
        QGraphicsView::resizeEvent(event);

        const int old = _nrPerW;
        _nrPerW       = int((qreal)event->size().width() / (ItemSize + Spacing));
        if (old != _nrPerW)
            layout();
    }

}  // namespace Rt2::View
