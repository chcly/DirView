#pragma once
#include "Math/Rect.h"
#include "Math/Vec2.h"
#include "Utils/Array.h"
#include "Utils/FileSystem.h"
#include "Utils/IndexCache.h"
#include "Utils/String.h"

class QPainter;

namespace Rt2::View
{
    class IndexedDirectory;
    class Directory;
    class File;

    using PathTable             = IndexCache<String>;
    using FileArray             = SimpleArray<File>;
    using DirectoryArray        = SimpleArray<Directory>;
    using IndexedDirectoryArray = SimpleArray<IndexedDirectory>;

    class File
    {
    public:
        File()                = default;
        File(const File& rhs) = default;

        size_t     index{0};
        size_t     colorIndex{0};
        Math::Rect rect{};
    };

    class IndexedDirectory
    {
    protected:
        size_t _index{0};

    public:
        IndexedDirectory()                            = default;
        IndexedDirectory(const IndexedDirectory& rhs) = default;

        size_t index() const;

        void setIndex(size_t index);
    };

    class Directory : public IndexedDirectory
    {
    private:
        size_t     _size{0};
        FileArray  _objects{};
        Math::Vec2 _min{Math::Infinity, Math::Infinity};
        Math::Vec2 _max{0, 0};

        void copy(const FileArray& arr);

    public:
        Directory() = default;
        Directory(const Directory& rhs);

        Directory& operator=(const Directory& rhs);

        const FileArray& files() const;

        size_t sizeInBytes() const;

        uint32_t addFile(const File& v);

        void update(uint32_t idx, const Math::Rect& r);

        void setSizeInBytes(size_t size);

        void merge(const Math::Vec2& lt, const Math::Vec2& rb);

        void reserve(size_t size);
    };

    inline size_t IndexedDirectory::index() const
    {
        return _index;
    }

    inline size_t Directory::sizeInBytes() const
    {
        return _size;
    }

    inline const FileArray& Directory::files() const
    {
        return _objects;
    }

    inline void IndexedDirectory::setIndex(const size_t index)
    {
        _index = index;
    }

    inline void Directory::setSizeInBytes(const size_t size)
    {
        _size = size;
    }

    class BuildParams
    {
    public:
        BuildParams() = default;
        String path{};
        int    flags{0};
        int    sort{0};
    };

}  // namespace Rt2::View
