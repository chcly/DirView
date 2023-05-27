#include "DirView/Content/Builder/Builder.h"
#include <QSizeF>
#include "DirView/Content/Cache/ColorCache.h"
#include "Math/Bin/Pack.h"
#include "Utils/Hash.h"

namespace Rt2::View::Builder
{
    bool Builder::sync()
    {
        return !isRunningUnlocked();
    }

    Builder::Builder() = default;

    Builder::~Builder() = default;

    void Builder::setParams(const BuildParams& params)
    {
        _input = params;
    }

    void Builder::bind(const PathAdded& path)
    {
        _pathAdded = path;
    }

    void Builder::bind(const DirectoryAdded& path)
    {
        _directoryAdded = path;
    }

    void Builder::packDirectory(const DirectoryEntry& root,
                                DirectoryEntryArray&  files,
                                const size_t          total)
    {
        if (const size_t path = _pathAdded(root.path().generic_string()); path == Npos)
            Console::println("skipping path, ", root.path().generic_string(), " failed to cache entry");
        else
        {
            Math::BinPack::Pack pack;
            pack.setOptions(_input.flags);

            Directory directory;
            directory.setIndex(path);
            directory.setSizeInBytes(total);
            directory.reserve(files.size());

            while (!files.empty())
            {
                if (sync())
                    return;

                const DirectoryEntry& fn = files.front();

                const size_t     id   = _pathAdded(fn.path().generic_string());
                const size_t     size = FileSystem::fileSize(fn);
                const Math::Real rt   = RtSqrt(size);

                String ext = fn.path().extension().generic_string();
                ColorCache::reference().cacheExtension(ext);

                File file;
                file.index      = id;
                file.colorIndex = Hash(ext);
                file.rect.setSize(rt, rt);

                if (const auto idx = directory.addFile(file);
                    idx != Npos32)
                    pack.push(idx, file.colorIndex, file.rect);

                files.pop_front();
            }

            if (_input.sort > 0)
                pack.modSort(_input.sort);
            else
                pack.sort();

            pack.pack({1, 1});

            for (const auto& ir : pack.output())
            {
                if (sync())
                    return;
                directory.update(ir.index, ir.rect);
            }

            _directoryAdded(directory);
        }
    }

    void Builder::update()
    {
        const DirectoryEntry ent(_input.path);

        if (sync())
            return;

        DirectoryEntryArray dirs, files;

        size_t total = 0;
        Fs::list(ent, &dirs, &files, &total);
        packDirectory(ent, files, total);

        DirectoryEntryArray subs;

        while (!dirs.empty())
        {
            if (sync())
                return;

            const DirectoryEntry& de = dirs.back();

            DirectoryEntryArray fArray;
            Fs::list(de, nullptr, &fArray, &total);
            packDirectory(de, fArray, total);

            dirs.pop_back();
        }
    }

}  // namespace Rt2::View::Builder
