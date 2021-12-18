class GoldFrame extends Inventory_Base
{
	bool checkIfCanSmeltGold()
	{
		bool cond = false;
		
		GoldNugget nugget = GoldNugget.Cast(FindAttachmentBySlotName("GoldNuggetSlot"));
		
		if (nugget)
		{
			if (nugget.GetQuantity() == nugget.GetQuantityMax())
			{
				cond = true;
			}
		}
		
		return cond;
	}
	
	void clearNuggets()
	{
		GoldNugget nugget = GoldNugget.Cast(FindAttachmentBySlotName("GoldNuggetSlot"));
		
		if (nugget)
		{
			nugget.Delete();
		}
	}
	
	override bool CanPutInCargo(EntityAI parent)
	{
		GoldNugget nugget = GoldNugget.Cast(FindAttachmentBySlotName("GoldNuggetSlot"));
		
		if (nugget)
		{
			return false;
		}
		else
		{
			return super.CanPutInCargo(parent);
		}
	}
	
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionSmeltGold);
	}
}
