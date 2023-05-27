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
#include "Utils/FileSystem.h"
#include "View/Definitions.h"

namespace Rt2::View
{
    constexpr int DirListEventCode  = EC_001;
    constexpr int DirClickEventCode = EC_003;

    class DirListEvent final : public QEvent
    {
    private:
        const String _directory;

    public:
        explicit DirListEvent(String dir);

        const String& directory() const;
    };

    inline const String& DirListEvent::directory() const
    {
        return _directory;
    }

    class DirClickEvent final : public QEvent
    {
    private:
        const String _directory;

    public:
        explicit DirClickEvent(String dir);

        const String& directory() const;
    };

    inline const String& DirClickEvent::directory() const
    {
        return _directory;
    }

}  // namespace Rt2::View
