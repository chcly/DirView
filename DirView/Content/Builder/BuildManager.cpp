#include "DirectoryView/Directory/BuildManager.h"
#include <QApplication>
#include "Builder.h"
#include "DirectoryView/Definitions.h"
#include "DirectoryView/GraphView.h"
#include "DirectoryView/PathCache.h"
#include "Events.h"
#include "Utils/Directory/Path.h"

namespace Rt2::DirectoryView
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

    Manager::Manager(GraphView* view) :
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

    void Manager::build(const BuildParams& path)
    {
        if (_builder->isRunning())
            _builder->stop();

        PathCache::reference().clear();

        _builder->setParams(path);
        _builder->start();
    }

}  // namespace Rt2::DirectoryView
