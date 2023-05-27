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
#include "DirViewCanvas.h"
#include <QGraphicsView>
#include <QMouseEvent>
#include <QWidget>
#include "Builder/Events.h"
#include "Cache/MathConstructors.h"
#include "DirView/Content/Builder/Manager.h"
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

    void DirViewCanvas::push(const Directory& directory)
    {
        DirViewItem* item = new DirViewItem(directory);
        item->setFlags(QGraphicsItem::ItemIsSelectable);

        _scene->addItem(item);
        
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

    void DirViewCanvas::updateMouse(const QPointF& co)
    {
        _co   = co - _last;
        _last = co;
    }

    void DirViewCanvas::mousePressEvent(QMouseEvent* event)
    {
        if (event->button() == Qt::LeftButton)
        {
            _state |= ENTER;
            updateMouse(mapToScene(Qmc::point(event->globalPosition())));
            update();
            event->accept();
        }
        QGraphicsView::mousePressEvent(event);
    }

    void DirViewCanvas::mouseReleaseEvent(QMouseEvent* event)
    {
        if (event->button() == Qt::LeftButton)
        {
            _state &= ~ENTER;
            _offs = _co = _last = {0, 0};
            update();
            event->accept();
        }
        QGraphicsView::mouseReleaseEvent(event);
    }

    void DirViewCanvas::mouseMoveEvent(QMouseEvent* event)
    {
        if (_state & ENTER)
        {
            updateMouse(mapToScene(Qmc::point(event->globalPosition())));

            _offs += _co;
            translate(_offs.x(), _offs.y());
            update();
            event->accept();
        }
        QGraphicsView::mouseMoveEvent(event);
    }

    bool DirViewCanvas::event(QEvent* event)
    {
        if ((int)event->type() == Builder::DirPushEvent)
        {
            if (const Builder::DirectoryEvent* de =
                    (Builder::DirectoryEvent*)event)
            {
                push(de->directory());
            }
            event->accept();
            return true;
        }

        return QGraphicsView::event(event);
    }

    void DirViewCanvas::resizeEvent(QResizeEvent* event)
    {
        _nrPerW = int((qreal)event->size().width() / (ItemSize + Spacing));
        updateBounds();
        QGraphicsView::resizeEvent(event);
    }

}  // namespace Rt2::View
