#pragma once
#include <QEvent>
#include "DirView/Content/Declarations.h"

namespace Rt2::View::Builder
{
    enum EventCodes
    {
        DIR_EVENT = QEvent::Type::User + 1,
        BUILD_EVENT,
    };

    class DirectoryEvent final : public QEvent
    {
    private:
        const Directory _directory;

    public:
        explicit DirectoryEvent(const Directory& dir);

        const Directory& directory() const;
    };

}  // namespace Rt2::DirectoryView
