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
                                new DirectoryEvent(path),
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
