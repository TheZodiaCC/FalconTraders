modded class ActionConstructor
{
	override void RegisterActions(TTypenameArray actions)
	{
		super.RegisterActions(actions);
		
		actions.Insert(ActionTrade);
		actions.Insert(ActionMineResource);
		actions.Insert(ActionATM);
		actions.Insert(ActionSmeltGold);
	}
}