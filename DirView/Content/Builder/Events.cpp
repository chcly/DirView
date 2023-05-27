#include "DirView/Content/Builder/Events.h"

namespace Rt2::View::Builder
{
    DirectoryEvent::DirectoryEvent(const Directory& dir) :
        QEvent((Type)DIR_PUSH_EVENT),
        _directory(dir)
    {
    }

    const Directory& DirectoryEvent::directory() const
    {
        return _directory;
    }
}  // namespace Rt2::View::Builder
