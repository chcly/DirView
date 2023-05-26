#include "DirectoryView/Directory/Sheet.h"
#include <QPainter>
#include "DirectoryView/ColorCache.h"
#include "DirectoryView/Definitions.h"
#include "DirectoryView/MathConstructors.h"
#include "DirectoryView/PathCache.h"
#include "Math/Bin/ShelfStep.h"
#include "Math/Bin/SpiralStep.h"

namespace Rt2::DirectoryView
{
    constexpr QRectF Qrs = {.05, -0.05, 1, 1};
    constexpr QRectF Qr0 = {0, 0, 1, 1};
    constexpr QRectF Qr1 = {0.0125, 0.0125, 1 - 0.025, 1 - 0.025};
    constexpr QRectF Qr2 = {0.05, 0.05, 1 - 0.1, 1 - 0.1};
    constexpr QRectF Top = {0.5 - 0.05 / 2, -0.05, 0.05, 0.05};

    DirectoryPaint::DirectoryPaint(DirectorySheet* parent, const Directory& dir) :
        _dir(dir),
        _parent(parent)
    {
        _transform.reset();
    }

    const Directory& DirectoryPaint::dir() const
    {
        return _dir;
    }

    void DirectoryPaint::translate(const Math::Vec2& v)
    {
        _transform.reset();
        _transform.translate(v.x, v.y);
    }

    void DirectoryPaint::setPen(const QPen& pen)
    {
        _linePen = pen;
    }

    void DirectoryPaint::cacheName()
    {
        String str = PathCache::reference().find(_dir.index());

        if (Su::endsWith(str, '/'))
            str.pop_back();
        if (const size_t pos = str.find_last_of('/');
            pos != Npos)
            str = str.substr(pos + 1, str.size());
        _name = Qsu::to(str);
    }

    void DirectoryPaint::paint(QPainter&     paint,
                               const QColor& fg,
                               const QColor& bg,
                               const QColor& bd,
                               const qreal   w,
                               const bool    flip)
    {
        _line = w;

        paint.save();
        paint.setTransform(_transform, true);

        if (flip)
        {
            paint.scale(1, -1);
            paint.translate(0, -1);
        }

        paint.fillRect(Qr0, bd);
        paint.fillRect(Qr1, bg);
        paint.fillRect(Qr2, bg.lighter(Colors::Lgt030));

        for (const auto& r : _dir.files())
        {
            QRectF r2 = Qm::rect(r.rect);

            QColor col = ColorCache::reference().color(r.colorIndex);
            col.setAlpha(0xFF);

            paint.fillRect(r2, col);
            paint.setPen(QPen(col.darker(), w));
            paint.drawRect(r2);

            col.setAlpha(0xA7);
            col = col.lighter(120);
            paint.fillRect(Qm::adjust(r2, 0.05), col);

            col = col.lighter(120);
            paint.fillRect(Qm::adjust(r2, 0.125), col);
        }

        if (flip)
        {
            paint.scale(1, -1);
            paint.translate(0, -1);
        }

        paint.scale(8 * w, 8 * w);
        paint.translate(0, 2 * w);
        paint.setPen(QPen(fg));
        paint.drawText(QPointF{0, 0}, _name);
        paint.restore();
    }

    bool DirectoryPaint::hit(const QRectF& hitRect) const
    {
        const auto tp = _transform.map(QPointF{0, 0});
        if (const QRectF lr = {tp.x(), tp.y(), 1, 1};
            hitRect.intersects(lr))
            return true;
        return false;
    }

    Math::Rect DirectoryPaint::position() const
    {
        return Qm::rect(_transform.mapRect(Qr0));
    }

    DirectorySheet::DirectorySheet()
    {
        _children.reserve(100);
    }

    DirectorySheet::~DirectorySheet()
    {
        for (const auto c : _children)
            delete c;
        _children.clear();
    }

    void DirectorySheet::clear()
    {
        _children.resizeFast(0);
    }

    const Directory& DirectorySheet::at(const int index, const Directory& err)
    {
        if (index < _children.sizeI())
            return _children.at(index)->dir();
        return err;
    }

    Math::Rect DirectorySheet::root()
    {
        if (!_children.empty())
        {
            return _children.at(0)->position();
        }
        return {};
    }

    void DirectorySheet::push(const Directory& dir)
    {
        _init = false;
        _children.push_back(new DirectoryPaint(this, dir));
    }

    void DirectorySheet::paint(QPainter& paint)
    {
        if (!_init)  // initialize position
        {
            Math::Vec2                offs = {0, 0};
            Math::BinPack::ShelfStep step(1.1, _children.size());

            for (const auto& ob : _children)
            {
                step.step(offs);
                ob->cacheName();
                ob->translate(offs);
            }
        }

        paint.setOpacity(_opacity);
        for (const auto& ob : _children)
        {
            ob->paint(paint,
                      _foreground,
                      _background,
                      _border,
                      _lineWidth,
                      _flip);
        }
    }

    void DirectorySheet::setOpacity(const Math::Real v)
    {
        _opacity = v;
    }

    void DirectorySheet::setLineWidth(const Math::Real v)
    {
        _linePen   = QPen(Colors::Accent, 4 * v);
        _lineWidth = v;
    }

    void DirectorySheet::setForeground(const QColor& color)
    {
        _foreground = color;
    }

    void DirectorySheet::setBackground(const QColor& color)
    {
        _background = color;
    }

    void DirectorySheet::setBorder(const QColor& color)
    {
        _border = color;
    }

    void DirectorySheet::setFlip(const bool flip)
    {
        _flip = flip;
    }

    DirectoryPaint* DirectorySheet::hitTest(const QRectF& hitRect)
    {
        for (const auto& ob : _children)
        {
            if (ob->hit(hitRect))
                return ob;
        }
        return nullptr;
    }
}  // namespace Rt2::DirectoryView
