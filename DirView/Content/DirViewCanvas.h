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
#include <QGraphicsView>
#include <QLineEdit>
#include <QWidget>
#include "Builder/Events.h"
#include "DirView/Content/DirViewItem.h"
#include "ViewModel/ViewModel.h"

class QGraphicsView;
class QGraphicsScene;

namespace Rt2::View::Builder
{
    class Manager;
}

namespace Rt2::View
{
    class DirViewItem;

    class DirViewCanvas final : public QGraphicsView
    {
        Q_OBJECT
    private:
        StringModel       _model;
        QGraphicsScene*   _scene{nullptr};
        QPointF           _shelf{0, 0};
        QRectF            _bounds{0, 0, 1, 1};
        Builder::Manager* _manager{nullptr};
        int               _nrPerW{0}, _cur{0};

    public:
        explicit DirViewCanvas(QWidget* parent = nullptr);
        ~DirViewCanvas() override;

        void setPath(const String& path);

        void addOutput(const StringModel::Observer& ot);

    private:
        void construct();

        void updateBounds();

        void layout();

        void updateItem(DirViewItem *item);

        void push(const Directory& directory);

        bool event(QEvent* event) override;

        void resizeEvent(QResizeEvent* event) override;
    };

}  // namespace Rt2::View
