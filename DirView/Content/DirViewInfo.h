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
#pragma once
#include "Utils/String.h"
#include "View/Definitions.h"
#include "View/LayoutView.h"

class QLabel;

namespace Rt2::View
{
    class DirViewInfo final : public LayoutView
    {
        Q_OBJECT
    private:
        QLabel* _dirs{nullptr};
        QLabel* _files{nullptr};
        QLabel* _sizeInBytes{nullptr};
        size_t  _counts[3]{0, 0, 0};

    public:
        explicit DirViewInfo(QWidget* parent = nullptr);

        ~DirViewInfo() override;

        void setPath(const String& path);

    private:
        void construct();
    };

}  // namespace Rt2::View
