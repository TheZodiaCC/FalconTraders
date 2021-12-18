class ActionSmeltGoldCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(UATimeSpent.DEFAULT_DEPLOY);
	}
};

class ActionSmeltGold: ActionContinuousBase
{
	void ActionSmeltGold()
	{
		m_CallbackClass = ActiondeployObjectCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_CRAFTING;
		m_FullBody = true;
	}
	
	override void CreateConditionComponents()  
	{
		
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTDummy;
	}
		
	override string GetText()
	{
		return "Smelt Gold";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{	
		Object target_object = target.GetObject();
		
		if (target_object.IsFireplace())
		{
			FireplaceBase fireplace_target = FireplaceBase.Cast(target_object);
			
			if (fireplace_target.IsBurning() && fireplace_target.IsOven())
			{
				GoldFrame frame = GoldFrame.Cast(item);
				
				if (frame.checkIfCanSmeltGold())
				{
					return true;
				}
			}		
		}
		
		return false;
	}
	
	override void OnFinishProgressServer(ActionData action_data)
	{	
		GoldFrame frame = GoldFrame.Cast(action_data.m_MainItem);
		
		if (frame.checkIfCanSmeltGold())
		{
			PlayerBase player = PlayerBase.Cast(action_data.m_Player);
		
			frame.clearNuggets();
			
			GetGame().CreateObject("Goldbar", player.GetPosition(), false, false, true);
		}
	}	
}