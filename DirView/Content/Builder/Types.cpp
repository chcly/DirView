/*
-------------------------------------------------------------------------------
    Copyright (c) Charles Carley.

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
-------------------------------------------------------------------------------
*/
#include "Thread/ParallelFor.h"
// ^^ conflict with emit
#include "DirView/Content/Builder/Types.h"
#include "Math/Rect.h"

namespace Rt2::View
{
    void Directory::copy(const FileArray& arr)
    {
        if (arr.size() < 10)
            _objects = arr;
        else
        {
            _objects.resize(arr.size());
            Thread::Copy<File>::invoke(
                _objects.data(),
                arr.data(),
                _objects.size());
        }
    }

    Directory::Directory(const Directory& rhs) :
        IndexedDirectory(rhs),
        _size(rhs._size),
        _min(rhs._min),
        _max(rhs._max)
    {
        _index = rhs._index,
        copy(rhs._objects);
    }

    Directory& Directory::operator=(const Directory& rhs)
    {
        if (this != &rhs)
        {
            _index = rhs._index;
            _size  = rhs._size;
            _min   = rhs._min;
            _max   = rhs._max;
            copy(rhs._objects);
        }
        return *this;
    }

    uint32_t Directory::addFile(const File& v)
    {
        if (const uint32_t size = _objects.size();
            size < 0x800)
        {
            _objects.push_back(v);
            return size;
        }
        return Npos32;
    }

    void Directory::update(const uint32_t idx, const Math::Rect& r)
    {
        if (idx < _objects.size())
        {
            _objects.at(idx).rect = r;
            merge(r.lt(), r.rb());
        }
    }

    void Directory::merge(const Math::Vec2& lt, const Math::Vec2& rb)
    {
        _min = _min.minOf(lt);
        _max = _max.maxOf(rb);
    }

    void Directory::reserve(const size_t size)
    {
        _objects.reserve(U32(Min<size_t>(size, 0x800)));
    }

}  // namespace Rt2::View
