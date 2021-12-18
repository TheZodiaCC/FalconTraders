class MiningRock extends Inventory_Base
{
	private int resourcesAmmount;
	private int resourcesPerDrop;
	private string resourceItem;
	
	
	override void EEInit()
    {
        super.EEInit();
	}
	
	int getResourcesAmmount()
	{
		return resourcesAmmount;
	}
	
	void setResourcesAmmount(int ammount)
	{
		resourcesAmmount = ammount;
	}
	
	void setReseourcesPerDrop(int ammount)
	{
		resourcesPerDrop = ammount;
	}
	
	void reduceResourcesAmmount()
	{
		resourcesAmmount -= resourcesPerDrop;
		
		if (resourcesAmmount <= 0)
		{
			Delete();
		}
	}
	void setResourceItem(string itemName)
	{
		resourceItem = itemName;
	}
	
	void spawnResources(vector position)
	{
		for (int i = 0; i < resourcesPerDrop; i++)
		{
			GetGame().CreateObject(resourceItem, position, false, false, false);
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