#pragma once
#include <QEvent>
#include "DirView/Content/Builder/Types.h"

namespace Rt2::View::Builder
{
    enum EventCodes
    {
        DIR_PUSH_EVENT = QEvent::Type::User + 5,
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

}  // namespace Rt2::View::Builder
