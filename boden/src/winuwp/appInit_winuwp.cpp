#include <bdn/init.h>
#include <bdn/appInit.h>

#include <bdn/Thread.h>

namespace bdn
{
	
ref class App sealed : public Windows::ApplicationModel::Core::IFrameworkView
{
internal:
	App(AppControllerBase* pAppController, AppLaunchInfo* pLaunchInfo)
	{
		_pAppController = pAppController;
		_pLaunchInfo = pLaunchInfo;
	}

public:
	virtual ~App()
	{
	}


	// IFrameworkView methods
 
	/** Called when the app is launched.*/
	virtual void Initialize(Windows::ApplicationModel::Core::CoreApplicationView^ applicationView)
	{
		Thread::_setMainId( Thread::getCurrentId() );

		// Register event handlers for app lifecycle. This example includes Activated, so that we
		// can make the CoreWindow active and start rendering on the window.
		applicationView->Activated +=
			ref new Windows::Foundation::TypedEventHandler
				<Windows::ApplicationModel::Core::CoreApplicationView^,
				 Windows::ApplicationModel::Activation::IActivatedEventArgs^>
				(this, &App::activated);
 
		Windows::ApplicationModel::Core::CoreApplication::Suspending +=
			ref new Windows::Foundation::EventHandler< Windows::ApplicationModel::SuspendingEventArgs^ >(this, &App::suspending);
 
		Windows::ApplicationModel::Core::CoreApplication::Resuming +=
			ref new Windows::Foundation::EventHandler< Platform::Object^ >(this, &App::resuming);


		_pAppController->beginLaunch(*_pLaunchInfo);
		_pAppController->finishLaunch(*_pLaunchInfo);
	}

	/** This is called when the app's core window has changed. Initially this gets called before
		Run is called, but it may be called multiple times again later, if the window is recreated.
		
		The "core window" represents the main app window. It is provided by the system.
		*/
	virtual void SetWindow(Windows::UI::Core::CoreWindow^ window)
	{
		int x=0;
	}

	/** Loads or activates any external resources used by the app view before Run is called.*/
	virtual void Load(Platform::String^ entryPoint)
	{
		// do nothing
		int x=0;
	}


	/** Run the app event loop.*/
	virtual void Run()
	{
		// run the event loop.
		while(true)
			Windows::UI::Core::CoreWindow::GetForCurrentThread()->Dispatcher->ProcessEvents(Windows::UI::Core::CoreProcessEventsOption::ProcessOneAndAllPending);
	}


	/** Clean up any external resources created during Load.*/
	virtual void Uninitialize()
	{
	}
 
protected:	
	void activated(	Windows::ApplicationModel::Core::CoreApplicationView^ applicationView,
					Windows::ApplicationModel::Activation::IActivatedEventArgs^ args)
	{
		_pAppController->onActivate();
	}

	void suspending(Platform::Object^ sender, Windows::ApplicationModel::SuspendingEventArgs^ args)
	{
		_pAppController->onSuspend();
	}

	void resuming(Platform::Object^ sender, Platform::Object^ args)
	{
		_pAppController->onResume();
	}
 
	// Window event handlers.
	void OnWindowSizeChanged(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::WindowSizeChangedEventArgs^ args);
	void OnVisibilityChanged(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::VisibilityChangedEventArgs^ args);
	void OnWindowClosed(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::CoreWindowEventArgs^ args);
 
	// DisplayInformation event handlers.
	void OnDpiChanged(Windows::Graphics::Display::DisplayInformation^ sender, Platform::Object^ args);
	void OnOrientationChanged(Windows::Graphics::Display::DisplayInformation^ sender, Platform::Object^ args);
	void OnDisplayContentsInvalidated(Windows::Graphics::Display::DisplayInformation^ sender, Platform::Object^ args);
 
private:
	P<AppControllerBase> _pAppController;
	P<AppLaunchInfo>	 _pLaunchInfo;
};


ref class AppFrameworkViewSource : Windows::ApplicationModel::Core::IFrameworkViewSource
{
internal:
	AppFrameworkViewSource(AppControllerBase* pAppController, AppLaunchInfo* pLaunchInfo)
	{
		_pAppController = pAppController;
		_pLaunchInfo = pLaunchInfo;
	}

public:

    virtual Windows::ApplicationModel::Core::IFrameworkView^ CreateView()
    {
        return ref new App(_pAppController, _pLaunchInfo);
    }

private:
	P<AppControllerBase>	_pAppController;
	P<AppLaunchInfo>		_pLaunchInfo;
};


int _uiAppMain(AppControllerBase* pAppController, Platform::Array<Platform::String^>^ args)
{
	P<AppLaunchInfo> pLaunchInfo = newObj<AppLaunchInfo>();


	// note: apparently the args array is always empty (there does not seem to be a way
	// to pass commandline arguments to a universal app from the outside).
	// One can apparently add arguments via a XAML, if there is one. But since we do not
	// have one (at least not at launch) it will probably always be empty. But we
	// handle it nevertheless.
	std::vector<String> argVector;
	for(auto a: args)
		argVector.push_back( a->Data() );

	if(argVector.empty())
		argVector.push_back("");

	pLaunchInfo->setArguments(argVector);
	
	auto frameworkViewSource = ref new AppFrameworkViewSource(pAppController, pLaunchInfo);

    ::Windows::ApplicationModel::Core::CoreApplication::Run(frameworkViewSource);

    return 0;
}


}



