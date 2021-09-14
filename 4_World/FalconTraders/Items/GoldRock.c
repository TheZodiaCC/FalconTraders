class GoldRock extends Inventory_Base
{	
	private int goldAmmount;
	
	
	override void EEInit()
    {
        super.EEInit();
		
		goldAmmount = Math.RandomInt(GoldMiningConsts.MIN_GOLD_AMMOUNT, GoldMiningConsts.MAX_GOLD_AMMOUNT);
	}
	
	int getGoldAmmount()
	{
		return goldAmmount;
	}
	
	void reduceGoldAmmount()
	{
		goldAmmount -= GoldMiningConsts.GOLD_PER_DROP;
		
		if (goldAmmount <= 0)
		{
			Delete();
		}
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