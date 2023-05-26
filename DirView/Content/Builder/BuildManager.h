#pragma once
#include "DirView/Content/Declarations.h"

namespace Rt2::DirectoryView
{
    class Builder;

    class Manager
    {
    private:
        Builder*                        _builder{nullptr};
        DirectoryArray                  _dirs;
        GraphView*                      _view{nullptr};

        size_t onPathAdded(const String& path);

        void onDirAdded(const Directory& path) const;

    public:
        explicit Manager(GraphView* view);
        ~Manager();

        void build(const BuildParams& path);
    };
}  // namespace Rt2::DirectoryView
