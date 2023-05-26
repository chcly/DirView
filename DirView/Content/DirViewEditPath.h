#pragma once
#include <QLineEdit>
#include <QWidget>
#include "Utils/String.h"
#include "View/Definitions.h"
#include "View/LayoutView.h"

namespace Rt2::View
{
    class EditPath final : public LayoutView
    {
        Q_OBJECT
    private:
        StringModel   _model;
        TextEditView* _edit{nullptr};

    public:
        explicit EditPath(QWidget* parent = nullptr);
        ~EditPath() override;

        void setPath(const String& path);

        void addOutput(const StringModel::Observer& ot);

    private:
        void construct();
    };

}  // namespace Rt2::View
