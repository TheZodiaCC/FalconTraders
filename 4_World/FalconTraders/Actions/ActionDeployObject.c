modded class ActionDeployObject: ActionDeployObject
{		
	override void OnStartServer( ActionData action_data )
	{
		PlayerBase player = action_data.m_Player;

		if (!player.getIsInSafeZone())
		{
			super.OnStartServer(action_data);
		}
	}
}