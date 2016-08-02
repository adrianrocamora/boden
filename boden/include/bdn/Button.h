#ifndef BDN_Button_H_
#define BDN_Button_H_

#include <bdn/View.h>
#include <bdn/IButtonCore.h>
#include <bdn/ClickEvent.h>

namespace bdn
{

/** A simple button with a text label.*/
class Button :	public View
{
public:
	Button()
	{
		initProperty<String, IButtonCore, &IButtonCore::setLabel>(_label);
	}

	/** Returns the button's label property.
		It is safe to use from any thread.
		*/
	Property<String>& label()
	{
		return _label;
	}

	const ReadProperty<String>& label() const
	{
		return _label;
	}
		

	Notifier<const ClickEvent&>& onClick()
	{
		return _onClick;
	}


	/** Static function that returns the type name for #Button objects.*/
	static String getButtonCoreTypeName()
	{
		return "bdn.ButtonCore";
	}

	String getCoreTypeName() const override
	{
		return getButtonCoreTypeName();
	}


protected:	
	void layout() override
	{
		// nothing to do. The button does not have child views.
	}


	DefaultProperty<String>		_label;

	Notifier<const ClickEvent&> _onClick;
};


}

#endif