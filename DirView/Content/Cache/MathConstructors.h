#pragma once
#include <QRect>
#include "Math/Rect.h"
#include "View/Colors.h"

namespace Rt2::View
{
    using TintB = ConstMix<0x00, 0x00, 0x1F>;
    using TintG = ConstMix<0x00, 0x2F, 0x00>;
    using TintR = ConstMix<0x2F, 0x00, 0x00>;

    class Qm
    {
    public:
        static QRectF rect(const Math::Rect& r);

        static Math::Rect rect(const QRectF& r);

        static QRectF adjust(const Math::Rect& r, const Math::Real& f);

        static QRectF adjust(const QRectF& r, const Math::Real& f);

        static Math::Vec2 toVec2(const QPointF& p);

        static Math::Vec2 toVec2(const QPoint& p);

        static QPointF point(const Math::Vec2& pt);

        static void square(const QRectF& inp, Math::Vec2& scale, Math::Vec2& offs);

        static QColor randB();

        static QColor randG();

        static QColor randR();
    };

}  // namespace Rt2::DirectoryView
