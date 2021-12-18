class FalconATM extends ItemBase
{
	override void EEInit()
    {
        super.EEInit();
		
		SetAllowDamage(false);
    }
	
	override void SetActions()
	{	
		AddAction(ActionATM);
	}
	
	override bool CanPutIntoHands(EntityAI parent)
	{
		return false;
	}
	
	override bool CanPutInCargo( EntityAI parent )
	{
		return false;
	}
	
	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		Delete();
		
		return true;
	}
}