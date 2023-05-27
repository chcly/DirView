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

namespace Rt2::View
{
    using PathChange = std::function<void(const String& path)>;

    class DirViewItem final : public QGraphicsItem
    {
    public:
        static constexpr qreal size = 200;

    private:
        Directory      _item{};
        QRectF         _bounds{0, 0, 1, 1};
        QPointF        _pos{0.0, 0.0};
        QRectF         _text{0.0, 0.0, 1.0, 1.0};
        String         _name;
        String         _path;
        QGraphicsView* _view{nullptr};

    public:
        explicit DirViewItem(const Directory& dir, QGraphicsView* view, QGraphicsItem* parent = nullptr);
        ~DirViewItem() override;

        void setPosition(const QPointF& pos);

        QRectF boundingRect() const override;

        qreal width() const;

        qreal height() const;

    private:
        void construct();

        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

        void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;
    };

}  // namespace Rt2::View
