#pragma once
#include <QLineEdit>
#include <QWidget>
#include "Utils/String.h"
#include "View/Definitions.h"
#include "View/LayoutView.h"
#include "View/StringListView.h"

namespace Rt2::View
{
    class DirListView final : public LayoutView
    {
        Q_OBJECT
    private:
        StringListView _model;

    public:
        explicit DirListView(QWidget* parent = nullptr);
        ~DirListView() override;

        void setPath(const String& path);

    private:
        void construct();
    };

}  // namespace Rt2::View
