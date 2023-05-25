#pragma once

namespace Rt2::QtTemplate
{

    class Application
    {
    public:
        bool parse(int argc, char** argv);

        int go();
    };

}  // namespace Rt2::QtTemplate
