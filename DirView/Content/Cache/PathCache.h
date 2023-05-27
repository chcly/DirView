#pragma once
#include <QColor>
#include "Thread/Mutex.h"
#include "Utils/HashMap.h"
#include "Utils/IndexCache.h"
#include "Utils/Singleton.h"

namespace Rt2::View
{
    class PathCache final : public Singleton<PathCache>
    {
    public:
        using Cache = IndexCache<String>;

    private:
        Thread::Mutex  _mutex;
        Cache _cache;
    public:
        PathCache();

        ~PathCache() override;

        String find(size_t id, const String& err="");

        size_t save(const String& str);

        void clear();
    };

}  // namespace Rt2::DirectoryView
