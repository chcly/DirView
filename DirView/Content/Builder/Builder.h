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
#include "DirView/Content/Builder/Types.h"
#include "Thread/Runner.h"
#include "Utils/FileSystem.h"

namespace Rt2::View::Builder
{
    class Builder final : public Thread::Runner
    {
    public:

        enum BuildState
        {
            DONE,
            INCOMPLETE,
        };

        using PathAdded      = std::function<size_t(const String&)>;
        using DirectoryAdded = std::function<void(const Directory&)>;

    private:
        BuildParams    _input{};
        PathAdded      _pathAdded;
        DirectoryAdded _directoryAdded;

        bool sync();

        void packDirectory(const DirectoryEntry& root,
                           DirectoryEntryArray&  files,
                           size_t                total);

    public:
        Builder();
        ~Builder() override;

        void setParams(const BuildParams& params);

        void bind(const PathAdded& path);

        void bind(const DirectoryAdded& path);

        void update() override;
    };

}  // namespace Rt2::View::Builder
