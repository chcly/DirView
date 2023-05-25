#pragma once
#include <QLineEdit>
#include <QWidget>
#include  "View/LayoutView.h"


namespace Rt2::QtTemplate
{
    class MainWindow final : public View::LayoutView
    {
        Q_OBJECT
    public:
        explicit MainWindow( QWidget* parent = nullptr);
        ~MainWindow() override;

        void post();

    private:
        
        void construct();
    };

}  // namespace Rt2::DirectoryView
