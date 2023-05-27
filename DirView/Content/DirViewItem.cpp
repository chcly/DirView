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
#include "DirView/Content/DirViewItem.h"
#include <qstyleoption.h>
#include <QApplication>
#include <QPainter>
#include "DirView/Content/Cache/ColorCache.h"
#include "DirView/Content/Cache/MathConstructors.h"
#include "DirView/Content/Cache/PathCache.h"
#include "DirView/Content/DirViewEvent.h"
#include "Utils/Directory/Path.h"
#include "View/Colors.h"
#include "View/Metrics.h"
#include "View/Qu.h"

namespace Rt2::View
{
    DirViewItem::DirViewItem(const Directory& dir, QGraphicsView* view, QGraphicsItem* parent) :
        QGraphicsItem(parent),
        _item(dir),
        _view(view)
    {
        construct();
    }

    DirViewItem::~DirViewItem() = default;

    void DirViewItem::setPosition(const QPointF& pos)
    {
        _pos = pos;
        _bounds.setX(_pos.x());
        _bounds.setY(_pos.y());
        _bounds.setWidth(size);
        _bounds.setHeight(size);
    }

    void DirViewItem::construct()
    {
        _bounds = {0, 0, size, size};
        _pos    = {0, 0};

        resetTransform();

        _path = Su::trimR(PathCache::reference().find(_item.index()), '/');
        _name = Rt2::Directory::Path(_path).base();
        _text = Qu::measure(_name, Metrics::defaultTextSize);
    }

    QRectF DirViewItem::boundingRect() const
    {
        return _bounds;
    }

    qreal DirViewItem::width() const
    {
        return _bounds.width();
    }

    qreal DirViewItem::height() const
    {
        return _bounds.height();
    }

    void DirViewItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
    {
        QApplication::postEvent(_view, new DirClickEvent(_path));
    }

    constexpr QRectF Qrs = {.05, -0.05, 1, 1};
    constexpr QRectF Qr0 = {0, 0, 1, 1};
    constexpr QRectF Qr1 = {0.0125, 0.0125, 1 - 0.025, 1 - 0.025};
    constexpr QRectF Qr2 = {0.05, 0.05, 1 - 0.1, 1 - 0.1};
    constexpr QRectF Top = {0.5 - 0.05 / 2, -0.05, 0.05, 0.05};

    void DirViewItem::paint(QPainter*                       paint,
                            const QStyleOptionGraphicsItem* option,
                            QWidget*                        widget)
    {
        const QRectF rect = boundingRect();

        paint->save();
        paint->translate(rect.x(), rect.y());
        paint->scale(rect.width(), rect.height());

        paint->fillRect(Qr0, Colors::Background);
        paint->fillRect(Qr1, Colors::Background);
        paint->fillRect(Qr2, Colors::Border.lighter(Colors::Lgt030));

        QTransform t;
        t.translate(0, 1);
        t.scale(1, -1);
        paint->setTransform(t, true);

        for (const auto& r : _item.files())
        {
            QRectF r2 = Qm::rect(r.rect);

            QColor col = ColorCache::reference().color(r.colorIndex);
            col.setAlpha(0xFF);

            paint->fillRect(r2, col);
            paint->setPen(QPen(col.darker(), 0.001));
            paint->drawRect(r2);

            col.setAlpha(0xA7);
            col = col.lighter(120);
            paint->fillRect(Qm::adjust(r2, 0.05), col);

            col = col.lighter(120);
            paint->fillRect(Qm::adjust(r2, 0.125), col);
        }

        paint->restore();

        paint->setPen(QPen(Colors::Foreground.darker(Colors::Drk030)));
        paint->drawText(QPointF{
                            rect.left(),
                            rect.bottom() + _text.height(),
                        },
                        Qsu::to(_name));
    }

}  // namespace Rt2::View
