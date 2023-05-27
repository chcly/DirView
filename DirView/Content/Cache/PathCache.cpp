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
#include "DirView/Content/Cache/PathCache.h"
#include "Utils/Singleton.h"
#include "View/Qu.h"

namespace Rt2
{
    template <>
    View::PathCache*
        Singleton<View::PathCache>::instance = nullptr;
}

namespace Rt2::View
{

    PathCache::PathCache() = default;

    PathCache::~PathCache()
    {
        _cache.clear();
    }

    String PathCache::find(const size_t id, const String& err)
    {
        Thread::ScopeLock scope(&_mutex);
        if (_cache.contains(id))
            return _cache.at(id);
        return err;
    }

    size_t PathCache::save(const String& str)
    {
        if (!_cache.contains(str))
            return _cache.insert(str);
        return _cache.get(str);
    }

    void PathCache::clear()
    {
        Thread::ScopeLock scope(&_mutex);
        _cache.clear();
    }
}  // namespace Rt2::View
