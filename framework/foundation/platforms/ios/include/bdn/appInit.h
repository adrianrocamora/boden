#pragma once

#include <bdn/ios/appEntry.h>
#include <bdn/platform/iosplatform.h>

#define BDN_APP_INIT_WITH_CONTROLLER_CREATOR(appControllerCreator)                                                     \
    int main(int argc, char *argv[])                                                                                   \
    {                                                                                                                  \
        bdn::platform::IOSHooks::init();                                                                               \
        return bdn::ios::appEntry(appControllerCreator, argc, argv);                                                   \
    }

#define BDN_APP_INIT(appControllerClass)                                                                               \
    BDN_APP_INIT_WITH_CONTROLLER_CREATOR((([]() { return bdn::newObj<appControllerClass>(); })))
