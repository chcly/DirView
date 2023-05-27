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
