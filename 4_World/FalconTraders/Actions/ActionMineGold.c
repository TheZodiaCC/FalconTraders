class ActionMineGoldCB : ActionContinuousBaseCB
{
	private const float TIME_BETWEEN_MATERIAL_DROPS = GoldMiningConsts.TIME_TO_MINE_GOLD;

	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousMineGold(TIME_BETWEEN_MATERIAL_DROPS);
	}
};

class ActionMineGold: ActionContinuousBase
{
	void ActionMineGold()
	{
		m_CallbackClass = ActionMineGoldCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_MINEROCK;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT;
		m_SpecialtyWeight = UASoftSkillsWeight.ROUGH_HIGH;
	}
	
	override void CreateConditionComponents()  
	{		
		m_ConditionTarget = new CCTCursor(UAMaxDistances.DEFAULT);
		m_ConditionItem = new CCINonRuined;
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
		//Action not allowed if player has broken legs
		if (player.m_BrokenLegState == eBrokenLegs.BROKEN_LEGS)
		{
			return false;
		}

		GoldRock rock = GoldRock.Cast(target.GetObject());
		
		if (rock)
		{
			return true;
		}
		
		return false;
	}

	override string GetText()
	{
		return "Mine Gold";
	}
	
	override void OnFinishProgressServer( ActionData action_data )
	{	
		if (action_data)
		{
			GoldRock goldRock = GoldRock.Cast(action_data.m_Target.GetObject());
			
			if (goldRock)
			{
				goldRock.reduceGoldAmmount();
				
				for (int i = 0; i < GoldMiningConsts.GOLD_PER_DROP; i++)
				{
					GetGame().CreateObject("GoldNugget", action_data.m_Player.GetPosition(), false, false, false);
				}
			}
		}
	}
};