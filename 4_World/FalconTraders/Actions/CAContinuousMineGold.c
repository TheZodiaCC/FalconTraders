class CAContinuousMineGold : CAContinuousMineWood
{	
	void CAContinuousMineGold(float time_between_drops)
	{
		m_TimeBetweenMaterialDrops = time_between_drops;
	}
	
	override bool GetMiningData(ActionData action_data )
	{
		GoldRock ntarget;
		
		if ( Class.CastTo(ntarget, action_data.m_Target.GetObject()) )
		{
			return true;
		}
		
		return false;
	}
	
	override int Execute( ActionData action_data )
	{
		GoldRock targetObject;
		Class.CastTo(targetObject, action_data.m_Target.GetObject());
		
		if ( !action_data.m_Player || !m_DataLoaded )
		{
			return UA_ERROR;
		}
		
		if ( (action_data.m_MainItem && action_data.m_MainItem.IsDamageDestroyed()) || targetObject.IsDamageDestroyed() )
		{
			return UA_FINISHED;
		}
		else
		{
			if ( m_TimeElpased < m_AdjustedTimeBetweenMaterialDrops )
			{
				m_TimeElpased += action_data.m_Player.GetDeltaT();
			}
			else
			{
				if ( GetGame().IsServer() )
				{
					if (action_data.m_MainItem)
					{
						action_data.m_MainItem.DecreaseHealth( "", "", GoldMiningConsts.MINING_TOOL_DAMAGE );
					}
					
				}
				
				m_TimeElpased = m_TimeElpased - m_AdjustedTimeBetweenMaterialDrops;
				OnCompletePogress(action_data);
			}
			return UA_PROCESSING;
		}
	}
}