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
#include "DirViewItem.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QPainter>
#include "Cache/ColorCache.h"
#include "Cache/MathConstructors.h"
#include "Cache/PathCache.h"
#include "Utils/Directory/Path.h"
#include "View/Colors.h"
#include "View/Metrics.h"
#include "View/Qu.h"
#include "View/View.h"

namespace Rt2::View
{
    constexpr qreal Socket = Metrics::defaultTextSize / 2;

    DirViewItem::DirViewItem(const Directory& dir, QGraphicsItem* parent) :
        QGraphicsItem(parent),
        _item(dir)
    {
        construct();
    }

    DirViewItem::~DirViewItem() = default;

    void DirViewItem::setPosition(const QPointF& pos)
    {
        _textOffs = pos;
    }

    void DirViewItem::construct()
    {
        _bounds   = {0, 0, size, size};
        _textOffs = {0, 0};

        String item = PathCache::reference().find(_item.index());

        _name = Rt2::Directory::Path(item).stem();
    }

    QRectF DirViewItem::boundingRect() const
    {
        return transform().mapRect(_bounds);
    }

    qreal DirViewItem::width() const
    {
        return _bounds.width();
    }

    qreal DirViewItem::height() const
    {
        return _bounds.height();
    }

    qreal DirViewItem::right() const
    {
        return transform().mapRect(_bounds).right();
    }

    qreal DirViewItem::bottom() const
    {
        return transform().mapRect(_bounds).bottom();
    }

    qreal DirViewItem::left() const
    {
        return transform().mapRect(_bounds).left();
    }

    qreal DirViewItem::top() const
    {
        return transform().mapRect(_bounds).top();
    }

    QRectF DirViewItem::input() const
    {
        return {left() - Socket, top() + height() / 2, Socket, Socket};
    }

    QRectF DirViewItem::output() const
    {
        return {right(), top() + height() / 2, Socket, Socket};
    }

    void DirViewItem::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
    {
        _state |= ENTER;
        update();
    }

    void DirViewItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
    {
        _state &= ~ENTER;
        update();
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
        paint->save();
        paint->resetTransform();
        paint->translate(_textOffs.x(), _textOffs.y());
        paint->scale(size, size);
        paint->fillRect(Qr0, Colors::Background);
        paint->fillRect(Qr1, Colors::Background);
        paint->fillRect(Qr2, Colors::Border.lighter(Colors::Lgt030));

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

        paint->resetTransform();
        paint->setPen(QPen(Colors::Foreground));
        paint->drawText(_textOffs, Qsu::to(_name));
        paint->restore();
    }

}  // namespace Rt2::View
