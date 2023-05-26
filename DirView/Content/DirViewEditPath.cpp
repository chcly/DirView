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
#include "DirViewEditPath.h"
#include <QHBoxLayout>
#include <QLineEdit>
#include <QWidget>
#include "Utils/Directory/Path.h"
#include "Utils/FileSystem.h"
#include "Utils/String.h"
#include "View/Definitions.h"
#include "View/LayoutView.h"
#include "View/Metrics.h"
#include "View/Qu.h"
#include "View/TextEditView.h"

namespace Rt2::View
{
    EditPath::EditPath(QWidget* parent) :
        LayoutView(parent)
    {
        construct();
    }

    EditPath::~EditPath() = default;

    void EditPath::construct()
    {
        const auto lo = Qu::horizontal();
        constructView(lo);
        setPadding(0);

        const auto up = Qu::icon(IconBack);
        lo->addWidget(up);

        _edit = new TextEditView();
        lo->addWidget(_edit, 1);

        // this -> edit
        _model.addInput(
            [this](const String& str)
            {
                if (_edit)
                    _edit->setText(str);
            });

        // edit -> this
        _edit->addOutput(
            [this](const String& str)
            {
                if (FileSystem::isDirectory(DirectoryEntry(str)))
                    _model.setValue(str, ViewModel::OUTPUT);
            });

        // click -> back 
        connect(up,
                &IconButtonView::clicked,
                this,
                [this]
                {
                    const Directory::Path val = Directory::Path(_model.value()).parentDir();
                    _model.setValue(val.full(), ViewModel::BOTH);
                });

    }

    void EditPath::setPath(const String& path)
    {
        _model.setValue(path, ViewModel::BOTH);
    }

    void EditPath::addOutput(const StringModel::Observer& ot)
    {
        _model.addOutput(ot);
    }
}  // namespace Rt2::View
