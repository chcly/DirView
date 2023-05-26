#include "DirectoryView/Directory/Events.h"

namespace Rt2::DirectoryView
{
    DirectoryEvent::DirectoryEvent(const Directory& dir):
        QEvent((Type)DIR_EVENT),
        _directory(dir)
    {
    }

    const Directory& DirectoryEvent::directory() const
    {
        return _directory;
    }
}  // namespace Rt2::DirectoryView
