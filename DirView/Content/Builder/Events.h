#pragma once
#include <QEvent>
#include "DirView/Content/Builder/Types.h"
#include "View/Definitions.h"

namespace Rt2::View::Builder
{
    constexpr int DirPushEvent = EC_002;

    class DirectoryEvent final : public QEvent
    {
    private:
        const Directory _directory;

    public:
        explicit DirectoryEvent(const Directory& dir);

        const Directory& directory() const;
    };

}  // namespace Rt2::View::Builder
