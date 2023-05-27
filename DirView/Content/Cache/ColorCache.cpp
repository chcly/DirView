#include "DirView/Content/Cache/ColorCache.h"
#include "DirView/Content/Cache/MathConstructors.h"
#include "Math/Rand.h"
#include "Utils/Singleton.h"

namespace Rt2
{
    template<>
    View::ColorCache* 
        Singleton<View::ColorCache>::instance = nullptr;
}

namespace Rt2::View
{

    ColorCache::ColorCache() = default;

    ColorCache::~ColorCache()
    {
        _colorTable.clear();
    }

    void ColorCache::cacheExtension(const String& str)
    {
        Thread::ScopeLock scope(&_mutex);

        const size_t hash = Hash(str);

        if (const size_t loc = _extension.find(hash); 
            loc == Npos)
            _extension.insert(hash, str);
    }

    QColor ColorCache::color(const size_t type)
    {
        Thread::ScopeLock scope(&_mutex);

        if (const size_t loc = _colorTable.find(type);
            loc == Npos)
        {
            const QColor col = TintB::mix(
                0x33,
                Math::Rand::u8(),
                Math::Rand::u8(),
                Math::Rand::u8(),
                0.25);
            _colorTable.insert(type, col);
            return col;
        }
        else
            return _colorTable.at(loc);
    }

}  // namespace Rt2::DirectoryView
