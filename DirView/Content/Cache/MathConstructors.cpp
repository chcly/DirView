#include "MathConstructors.h"
#include "Math/Rand.h"

namespace Rt2::View
{
    QRectF Qm::rect(const Math::Rect& r)
    {
        return {r.x, r.y, r.w, r.h};
    }

    Math::Rect Qm::rect(const QRectF& r)
    {
        return {r.x(), r.y(), r.width(), r.height()};
    }

    QRectF Qm::adjust(const Math::Rect& r, const Math::Real& f)
    {
        return rect(r).adjusted(r.w * f, r.h * f, -r.w * f, -r.h * f);
    }

    QRectF Qm::adjust(const QRectF& r, const Math::Real& f)
    {
        return r.adjusted(r.width() * f,
                          r.height() * f,
                          -r.width() * f,
                          -r.height() * f);
    }

    Math::Vec2 Qm::toVec2(const QPointF& p)
    {
        return {Math::Real(p.x()), Math::Real(p.y())};
    }

    Math::Vec2 Qm::toVec2(const QPoint& p)
    {
        return {Math::Real(p.x()), Math::Real(p.y())};
    }

    QPointF Qm::point(const Math::Vec2& pt)
    {
        return {pt.x, pt.y};
    }

    void Qm::square(const QRectF& inp, Math::Vec2& scale, Math::Vec2& offs)
    {
        offs = {};
        if (inp.width() > inp.height())
        {
            offs.x  = (inp.width() - inp.height()) * Math::Half;
            offs.y  = 0;
            scale.x = scale.y = inp.height();
        }
        else
        {
            offs.x  = (inp.height() - inp.width()) * Math::Half;
            offs.y  = 0;
            scale.x = scale.y = inp.width();
        }
    }

    QColor Qm::randB()
    {
        return TintB::mix(0x33,
                          Math::Rand::u8(),
                          Math::Rand::u8(),
                          Math::Rand::u8(),
                          0.25);
    }

    QColor Qm::randG()
    {
        return TintG::mix(0x33,
                          Math::Rand::u8(),
                          Math::Rand::u8(),
                          Math::Rand::u8(),
                          0.25);
    }

    QColor Qm::randR()
    {
        return TintR::mix(0x33,
                          Math::Rand::u8(),
                          Math::Rand::u8(),
                          Math::Rand::u8(),
                          0.25);
    }
}  // namespace Rt2::DirectoryView
