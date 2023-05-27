#pragma once
#include <QColor>
#include "Thread/Mutex.h"
#include "Utils/HashMap.h"
#include "Utils/Singleton.h"

namespace Rt2::View
{
    class ColorCache final : public Singleton<ColorCache>
    {
    public:
        using ColorTable     = HashTable<size_t, QColor>;
        using ExtensionTable = HashTable<size_t, String>;

    private:
        Thread::Mutex  _mutex;
        ExtensionTable _extension;
        ColorTable     _colorTable;

    public:
        ColorCache();

        ~ColorCache() override;

        void cacheExtension(const String& str);

        QColor color(size_t type);
    };

}  // namespace Rt2::DirectoryView
