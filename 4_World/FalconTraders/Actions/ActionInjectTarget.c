modded class ActionInjectTarget: ActionSingleUseBase
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (player.getIsInSafeZone())
		{
			return false;
		}
		else
		{
			return super.ActionCondition(player, target, item);
		}
	}
	
	/*Doesnt work
	override void OnExecuteServer( ActionData action_data )
	{
		PlayerBase player = action_data.m_Player;
		
		if (!player.getIsInSafeZone())
		{
			//super.OnExecuteServer(action_data);
		}
	}*/
}