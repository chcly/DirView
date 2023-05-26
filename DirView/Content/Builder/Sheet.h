#pragma once
#include <QTransform>
#include "DirView/Content/Declarations.h"

namespace Rt2::View
{
    class DirectorySheet;
    using DirectorySheetArray = std::deque<DirectorySheet*>;

    class DirectoryPaint
    {
    private:
        QTransform      _transform;
        Directory       _dir;
        QString         _name;
        qreal           _line{0};
        QPen            _linePen;
        DirectorySheet* _parent{nullptr};

    public:
        DirectoryPaint() = default;
        explicit DirectoryPaint(DirectorySheet* parent, const Directory& dir);

        void cacheName();

        const Directory& dir() const;

        void translate(const Math::Vec2& v);

        void setPen(const QPen& pen);

        void paint(QPainter&     paint,
                   const QColor& fg,
                   const QColor& bg,
                   const QColor& bd,
                   qreal         w,
                   bool          flip);

        bool hit(const QRectF& hitRect) const;

        Math::Rect position() const;
    };

    using DirectoryPaintArray = SimpleArray<DirectoryPaint*>;

    class DirectorySheet
    {
    private:
        DirectoryPaintArray _children;
        bool                _init{false};
        Math::Real          _opacity{1};
        Math::Real          _lineWidth{1};
        QColor              _border;
        QColor              _background;
        QColor              _foreground;
        Math::Rect          _viewport{};
        bool                _flip{true};
        QPen                _linePen;

    public:
        DirectorySheet();
        ~DirectorySheet();

        bool empty() const;

        int size() const;

        void clear();

        const Directory& at(int index, const Directory& err = {});

        Math::Rect root();

        void push(const Directory&);

        void paint(QPainter& paint);

        void setOpacity(Math::Real v);

        void setLineWidth(Math::Real v);

        void setForeground(const QColor& color);

        void setBackground(const QColor& color);

        void setBorder(const QColor& color);

        void setFlip(bool flip);

        DirectoryPaint* hitTest(const QRectF& hitRect);
    };

    inline bool DirectorySheet::empty() const
    {
        return _children.empty();
    }

    inline int DirectorySheet::size() const
    {
        return _children.sizeI();
    }

}  // namespace Rt2::DirectoryView
