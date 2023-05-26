#pragma once
#include "DirView/Content/Declarations.h"
#include "Thread/Runner.h"

namespace Rt2::View::Builder
{

    class Builder final : public Thread::Runner
    {
    public:
        enum BuildState
        {
            DONE,
            INCOMPLETE,
        };

        using PathAdded      = std::function<size_t(const String&)>;
        using DirectoryAdded = std::function<void(const Directory&)>;

    private:
        BuildParams    _input{};
        PathAdded      _pathAdded;
        DirectoryAdded _directoryAdded;

        bool sync();

        void packDirectory(const DirectoryEntry& root,
                           DirectoryEntryArray&  files,
                           size_t                total);

    public:
        Builder();
        ~Builder() override;

        void setParams(const BuildParams& params);

        void bind(const PathAdded& path);

        void bind(const DirectoryAdded& path);

        void update() override;
    };

}  // namespace Rt2::DirectoryView
