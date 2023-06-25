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
        return TintB::qMix(0x33,
                          Math::Rand::u8(),
                          Math::Rand::u8(),
                          Math::Rand::u8(),
                          0.25);
    }

    QColor Qm::randG()
    {
        return TintG::qMix(0x33,
                          Math::Rand::u8(),
                          Math::Rand::u8(),
                          Math::Rand::u8(),
                          0.25);
    }

    QColor Qm::randR()
    {
        return TintR::qMix(0x33,
                          Math::Rand::u8(),
                          Math::Rand::u8(),
                          Math::Rand::u8(),
                          0.25);
    }
}  // namespace Rt2::DirectoryView
