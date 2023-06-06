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
#include "DirListView.h"
#include <QApplication>
#include <QVBoxLayout>
#include "DirViewEvent.h"
#include "Thread/Runner.h"
#include "Utils/Directory/Path.h"
#include "Utils/FileSystem.h"
#include "Utils/String.h"
#include "View/LayoutView.h"
#include "View/Metrics.h"
#include "View/Qu.h"

namespace Rt2::View
{
    class ListRunner final : public Thread::Runner
    {
    public:
        using PushFunc = std::function<void(const String&)>;

    private:
        String   _path{};
        PushFunc _push{nullptr};

    public:
        ListRunner() = default;

        void setPath(const String& path)
        {
            _path = path;
        }

        void bind(const PushFunc& fnc)
        {
            _push = fnc;
        }

        bool sync()
        {
            Thread::Thread::sleep(5);
            return !isRunning();
        }

        bool pushList(DirectoryEntryArray& de)
        {
            while (!de.empty())
            {
                if (sync())
                    return false;

                const auto& dir = de.back();
                _push(dir.path().generic_string());
                de.pop_back();
            }
            return true;
        }

        void update() override
        {
            DirectoryEntryArray de, fl;
            FileSystem::list(DirectoryEntry(_path), &de, &fl, nullptr);

            if (pushList(de))
                pushList(fl);
        }
    };

    DirListView::DirListView(QWidget* parent) :
        LayoutView(parent)
    {
        construct();
    }

    DirListView::~DirListView()
    {
        delete _runner;
        _runner = nullptr;
    }

    void DirListView::construct()
    {
        const auto lo = Qu::vertical();
        constructView(lo);
        setBorder(0);
        setPadding(0);
        setMinimumSize(Metrics::minPanel);

        lo->addLayout(Qu::titleList("Listing", {}));

        _view = new StringListView();
        lo->addWidget(_view, 1);
        lo->setSizeConstraint(QLayout::SetMaximumSize);
        setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    }

    bool DirListView::event(QEvent* event)
    {
        if ((int)event->type() == DirListEventCode)
        {
            if (const auto path = Directory::Path(((DirListEvent*)event)->directory());
                path.exists())
            {
                _view->addEntry(path.base(), Qsu::variant(path.full()));
            }
            return true;
        }
        return LayoutView::event(event);
    }

    void DirListView::push(const String& str)
    {
        QApplication::postEvent(this, new DirListEvent(str));
    }

    void DirListView::setPath(const String& path)
    {
        if (!_runner)
        {
            _runner = new ListRunner();
            _runner->bind(
                [this](const String& item)
                { push(item); });
        }

        if (FileSystem::isDirectory(DirectoryEntry(path)))
        {
            _runner->stop();
            _view->clear();
            _runner->setPath(path);
            _runner->start();
        }
    }

    void DirListView::addOutput(const VariantModel::Observer& ot) const
    {
        if (_view)
            _view->addDoubleClickOutput(ot);
    }

}  // namespace Rt2::View
