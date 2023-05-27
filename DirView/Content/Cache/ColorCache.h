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
