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
#include "ViewModel/ViewModel.h"
#include "DirView/Content/DirViewItem.h"

class QGraphicsView;
class QGraphicsScene;

namespace Rt2::View
{
    class DirViewCanvas final : public QGraphicsView
    {
        Q_OBJECT
    private:
        QGraphicsScene* _scene{nullptr};
        QPointF         _co{0, 0}, _last{0, 0}, _offs{0, 0};
        int             _state{0};

    public:
        explicit DirViewCanvas(QWidget* parent = nullptr);
        ~DirViewCanvas() override;

        void setPath(const String& path);


    private:
        void construct();

        void updateMouse(const QPointF& co);

        void mousePressEvent(QMouseEvent* event) override;

        void mouseReleaseEvent(QMouseEvent* event) override;

        void mouseMoveEvent(QMouseEvent* event) override;
    };

}  // namespace Rt2::View
