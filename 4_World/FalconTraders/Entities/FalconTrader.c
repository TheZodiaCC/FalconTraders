class FalconTrader extends SurvivorBase
{
	private int traderId;
	private int maxHumanity;
	private int minHumanity;
	
	int getTraderId()
	{
		return traderId;
	}
	
	void setTraderId(int value)
	{
		traderId = value;
	}
	
	int getMaxHumanity()
	{
		return maxHumanity;
	}
	
	void setMaxHumanity(int value)
	{
		maxHumanity = value;
	}
	
	int getMinHumanity()
	{
		return minHumanity;
	}
	
	void setMinHumanity(int value)
	{
		minHumanity = value;
	}
	
	override void SetActionsRemoteTarget( out TInputActionMap InputActionMap)
	{		
		AddAction(ActionTrade, InputActionMap);
	}
	
	override bool CanBeRestrained()
	{
		return false;
	}
}