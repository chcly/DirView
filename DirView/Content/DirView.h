#pragma once
#include <QLineEdit>
#include <QWidget>
#include "DirViewEditPath.h"
#include "Utils/String.h"
#include "View/Definitions.h"
#include "View/LayoutView.h"

namespace Rt2::View
{
    class DirView final : public LayoutView
    {
        Q_OBJECT
    private:
        EditPath*   _path{nullptr};
        StringModel _model;

    public:
        explicit DirView(QWidget* parent = nullptr);
        ~DirView() override;

        void setPath(const String& path);

    private:
        void construct();
    };

}  // namespace Rt2::View
