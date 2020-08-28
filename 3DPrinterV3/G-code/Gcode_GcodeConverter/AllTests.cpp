//- Copyright (c) 2008-2009 James Grenning --- All rights reserved
//- For exclusive use by participants in Renaissance Software Consulting training courses.
//- Cannot be used by attendees to train others without written permission.
//- www.renaissancesoftware.net james@renaissancesoftware.net

//START: main
#include <vector>
#include "CppUTest/CommandLineTestRunner.h"

int main(int argc, char** argv)
{
    std::vector<const char*> args(argv, argv + argc);
    //args.push_back("-v");
    args.push_back("-c");

    return RUN_ALL_TESTS(args.size(), &args[0]);
}
//END: main

