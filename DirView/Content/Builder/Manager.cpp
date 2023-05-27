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
#include <QApplication>
#include "DirView/Content/Cache/PathCache.h"
#include "DirView/Content/DirViewCanvas.h"
#include "DirView/Content/Builder/Types.h"
#include "DirView/Content/Builder/Manager.h"
#include "DirView/Content/Builder/Events.h"
#include "DirView/Content/Builder/Builder.h"
#include "Utils/Directory/Path.h"

namespace Rt2::View::Builder
{
    size_t Manager::onPathAdded(const String& path)
    {
        return PathCache::reference().save(path);
    }

    void Manager::onDirAdded(const Directory& path) const
    {
        QApplication::postEvent(_view,
                                new DirPushEvent(path),
                                Qt::EventPriority::LowEventPriority);
    }

    Manager::Manager(DirViewCanvas* view) :
        _view(view)
    {
        _builder = new Builder();
        _builder->bind([this](const String& path)
                       { return onPathAdded(path); });
        _builder->bind([this](const Directory& path)
                       { return onDirAdded(path); });
    }

    Manager::~Manager()
    {
        delete _builder;
        _builder = nullptr;
    }

    void Manager::build(const BuildParams& path) const
    {
        if (_builder->isRunning())
            _builder->stop();

        PathCache::reference().clear();

        _builder->setParams(path);
        _builder->start();
    }

}  // namespace Rt2::View::Builder
