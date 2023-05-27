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
#pragma once
#include <QGraphicsItem>
#include "DirViewCanvas.h"
#include "Utils/String.h"
#include "View/LayoutView.h"

namespace Rt2::View
{
    class DirViewItem final : public QGraphicsItem
    {
    public:
        static constexpr qreal size = 200;

    private:
        Directory _item{};
        QRectF    _bounds{0, 0, 1, 1};
        int       _state{0};
        QPointF   _textOffs{0.0, 0.0};
        String    _name;

    public:
        explicit DirViewItem(const Directory& dir, QGraphicsItem* parent = nullptr);
        ~DirViewItem() override;

        void setPosition(const QPointF& pos);

        QRectF boundingRect() const override;

        qreal width() const;

        qreal height() const;

        qreal right() const;

        qreal bottom() const;

        qreal left() const;

        qreal top() const;

        QRectF input() const;
        QRectF output() const;

    private:
        void construct();

        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

        void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;

        void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
    };

}  // namespace Rt2::View
