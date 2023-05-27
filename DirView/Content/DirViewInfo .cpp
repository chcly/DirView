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
#include <QPainter>
#include <QVBoxLayout>
#include "DirViewInfo.h"
#include "Utils/Char.h"
#include "Utils/FileSystem.h"
#include "Utils/String.h"
#include "View/Colors.h"
#include "View/CustomView.h"
#include "View/Definitions.h"
#include "View/Metrics.h"
#include "View/Qu.h"

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
        const auto lo = Qu::vertical();
        constructView(lo);
        setBorder(0);
        setPadding(0);
        setMinimumSize(Metrics::minPanel);

        _dirs = Qu::text("", Colors::Foreground);
        _files = Qu::text("", Colors::Foreground);
        _sizeInBytes = Qu::text("", Colors::Foreground);

        lo->addLayout(Qu::titleList("Info", {}));
        lo->addWidget(_dirs);
        lo->addWidget(_files);
        lo->addWidget(_sizeInBytes);
        lo->addSpacing(Metrics::iconWidth);
        lo->addStretch();

        lo->setSizeConstraint(QLayout::SetMinimumSize);
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    }

    void DirViewInfo::setPath(const String& path)
    {
        if(!FileSystem::isDirectory(DirectoryEntry(path)))
            return;

        FileSystem::count(path, _counts[0], _counts[1], _counts[2]);

        _dirs->setText(Qsu::to(Su::join(" Directories, ", _counts[0])));
        _files->setText(Qsu::to(Su::join(" Files, ", _counts[1])));
        _sizeInBytes->setText(Qsu::to(Su::join(" Size in bytes, ",
                                               Char::commaInt(_counts[2]))));
        update();
    }

}  // namespace Rt2::View
