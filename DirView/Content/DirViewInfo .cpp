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
#include <QLabel>
#include <QVBoxLayout>
#include "DirView/Content/DirViewInfo.h"
#include "Utils/Char.h"
#include "Utils/FileSystem.h"
#include "Utils/String.h"
#include "View/Qu.h"
#include "View/TitleListWidget.h"

namespace Rt2::View
{
    DirViewInfo::DirViewInfo(QWidget* parent) :
        LayoutView(parent)
    {
        construct();
    }

    DirViewInfo::~DirViewInfo() = default;

    void DirViewInfo::construct()
    {
        const auto lo = Style::Layout::v0(Style::Spacing::Small);
        constructView(lo);
        setBackgroundColor(Style::Window::Swatches::Qb15::Qs0);
        
        _dirs        = Style::Widget::label();
        _files       = Style::Widget::label();
        _sizeInBytes = Style::Widget::label();

        const auto title = Style::Views::title("Info");
        title->setBackgroundColor(Style::Window::Swatches::Qb15::Qs1);

        lo->addWidget(title);
        lo->addWidget(_dirs);
        lo->addWidget(_files);
        lo->addWidget(_sizeInBytes);
        lo->addSpacing(Style::Icon::Normal);
        lo->addStretch();

        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    }

    void DirViewInfo::setPath(const String& path)
    {
        if (!FileSystem::isDirectory(DirectoryEntry(path)))
            return;

        _counts[0] = _counts[1] = _counts[2] = 0;
        FileSystem::count(path, _counts[0], _counts[1], _counts[2]);

        _dirs->clear();
        _dirs->setText(Qsu::to(Su::join(" Directories, ", _counts[0]+1)));

        _files->clear();
        _files->setText(Qsu::to(Su::join(" Files, ", _counts[1])));

        _sizeInBytes->clear();
        _sizeInBytes->setText(Qsu::to(Su::join(" Size in bytes, ",
                                               Char::commaInt(_counts[2]))));
        update();
    }

}  // namespace Rt2::View
