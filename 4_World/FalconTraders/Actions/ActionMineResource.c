class ActionMineResourceCB : ActionContinuousBaseCB
{
	private const float TIME_BETWEEN_MATERIAL_DROPS = MiningConsts.TIME_TO_MINE_GOLD;

	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousMineResource(TIME_BETWEEN_MATERIAL_DROPS);
	}
};

class ActionMineResource: ActionContinuousBase
{
	void ActionMineResource()
	{
		m_CallbackClass = ActionMineResourceCB;
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

		MiningRock rock = MiningRock.Cast(target.GetObject());
		
		if (rock)
		{
			return true;
		}
		
		return false;
	}

	override string GetText()
	{
		return "Mine Resource";
	}
	
	override void OnFinishProgressServer( ActionData action_data )
	{	
		if (action_data)
		{
			MiningRock rock = MiningRock.Cast(action_data.m_Target.GetObject());
			
			if (rock)
			{
				rock.reduceResourcesAmmount();
				rock.spawnResources(action_data.m_Player.GetPosition());
			}
		}
	}
};