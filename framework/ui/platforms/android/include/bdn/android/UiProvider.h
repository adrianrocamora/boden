#ifndef BDN_ANDROID_UiProvider_H_
#define BDN_ANDROID_UiProvider_H_

namespace bdn
{
    namespace android
    {

        class UiProvider;
    }
}

#include <bdn/IUiProvider.h>
#include <bdn/LayoutCoordinator.h>
#include <bdn/ITextUi.h>

#include <bdn/android/ViewCore.h>
#include <bdn/android/JTextView.h>

#include <cmath>

namespace bdn
{
    namespace android
    {

        class UiProvider : public Base, BDN_IMPLEMENTS IUiProvider
        {
          public:
            UiProvider()
            {
                _semDips = -1;
                _layoutCoordinator = newObj<LayoutCoordinator>();
            }

            String getName() const override;

            P<IViewCore> createViewCore(const String &coreTypeName, View *view) override;

            P<ITextUi> getTextUi() override;

            double getSemSizeDips(ViewCore &viewCore);

            /** Returns the layout coordinator that is used by view cores
             * created by this UI provider.*/
            P<LayoutCoordinator> getLayoutCoordinator() { return _layoutCoordinator; }

            static UiProvider &get();

          private:
            double _semDips;
            P<LayoutCoordinator> _layoutCoordinator;

            Mutex _textUiInitMutex;
            P<ITextUi> _textUi;
        };
    }
}

#endif
