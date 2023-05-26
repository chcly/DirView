#include "DirViewEditPath.h"
#include <QHBoxLayout>
#include <QLineEdit>
#include <QWidget>
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
        setPadding(Metrics::indent);

        const auto up = Qu::icon(IconBack);
        lo->addWidget(up);

        _edit = new TextEditView();
        lo->addWidget(_edit, 1);

        _model.addOutput([this](const String& str)
                         { _edit->setText(str); });
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
