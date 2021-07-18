class SafeZoneMark
{
	private Widget widgetRoot;
	
	private bool isMarkOn = false;
	
	//Constructor
	void SafeZoneMark() {		
		widgetRoot = GetGame().GetWorkspace().CreateWidgets("FalconTraders/GUI/Layouts/SafeZoneMark.layout");
		widgetRoot.Show(false);
	}
	
	//Deconstructor
	void ~SafeZoneMark() {
        if ( widgetRoot )
        	widgetRoot.Unlink();
    }
	
	bool getIsMarkOn() {
		return isMarkOn;
	}
	
	void setIsMarkOn(bool value) {
		isMarkOn = value;
	}
	
	void showMark() {
		if (!isMarkOn)
		{
			widgetRoot.Show(true);
			setIsMarkOn(true);
		}
	}
	
	void hideMark() {
		if (isMarkOn)
		{
			widgetRoot.Show(false);
			setIsMarkOn(false);
		}
	}
}
	
	
