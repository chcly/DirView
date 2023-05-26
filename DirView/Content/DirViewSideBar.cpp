#include "DirViewSidebar.h"
#include "Thread/Runner.h"
#include "Utils/FileSystem.h"
#include "Utils/String.h"
#include "View/LayoutView.h"

namespace Rt2::View
{
    class ListRunner final : public Thread::Runner
    {
    private:
        String _path;
    public:
        ListRunner()
        {
        }

        void setPath(const String &path)
        {
            stop();
            _path = path;
        }

        void update() override
        {
            DirectoryEntryArray de,fl;
            FileSystem::list(DirectoryEntry(_path), &de, &fl, nullptr);


            for(const auto ent : de)
            {
                // push
            }

            for(const auto ent : fl)
            {
                // push
            }
        }
    };



    DirListView::DirListView(QWidget* parent)
        : LayoutView(parent)
    {
        construct();
    }

    DirListView::~DirListView() = default;

    void DirListView::construct()
    {
        
    }

    void DirListView::setPath(const String& path)
    {
    }


    

}  // namespace Rt2::View
