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
