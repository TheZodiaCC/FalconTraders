modded class ActionForceConsume: ActionContinuousBase
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
	override void OnStartServer( ActionData action_data )
	{
		PlayerBase player = action_data.m_Player;

		Print("feeding");
		
		if (!player.getIsInSafeZone())
		{
			//super.OnStartServer(action_data);
		}
	}*/
}