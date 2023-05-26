#pragma once
#include "Utils/String.h"

namespace Rt2::Samples
{
    class Application
    {
    private:
        String _path;

    public:
        bool parse(int argc, char** argv);

        int go() const;
    };

}  // namespace Rt2::Samples
