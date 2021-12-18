class GoldRock extends MiningRock
{	
	override void EEInit()
    {
        super.EEInit();
		
		setResourcesAmmount(Math.RandomInt(MiningConsts.MIN_GOLD_AMMOUNT, MiningConsts.MAX_GOLD_AMMOUNT));
		setReseourcesPerDrop(MiningConsts.GOLD_PER_DROP);
		setResourceItem(MiningConsts.GOLD_NUGGET_ITEM);
	}
}