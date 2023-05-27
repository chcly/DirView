#pragma once
#include "DirView/Content/DirViewCanvas.h"
#include "Types.h"

namespace Rt2::View::Builder
{
    class Builder;

    class Manager
    {
    private:
        Builder*       _builder{nullptr};
        DirectoryArray _dirs;
        DirViewCanvas* _view{nullptr};

        static size_t onPathAdded(const String& path);

        void onDirAdded(const Directory& path) const;

    public:
        explicit Manager(DirViewCanvas* view);
        ~Manager();

        void build(const BuildParams& path) const;
    };
}  // namespace Rt2::View::Builder
