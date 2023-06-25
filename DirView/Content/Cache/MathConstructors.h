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
#include <QRect>

#include "Math/Rect.h"
#include "View/ColorMix.h"

namespace Rt2::View
{
    using TintB = Mix::Mixer::MixRgb<0x00, 0x00, 0x1F>;
    using TintG = Mix::Mixer::MixRgb<0x00, 0x2F, 0x00>;
    using TintR = Mix::Mixer::MixRgb<0x2F, 0x00, 0x00>;

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

}  // namespace Rt2::View
