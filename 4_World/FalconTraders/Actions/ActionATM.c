class ActionATM extends ActionInteractBase
{
	void ActionATM()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_HUDCursorIcon = CursorIcons.CloseHood;
	}

	override string GetText()
	{
		return "ATM";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		Object target_object = target.GetObject();
		if ( target_object.IsItemBase() )
		{
			FalconATM ntarget = FalconATM.Cast( target_object );
			if (ntarget)
			{
				return true;
			}
		}
		
		return false;
	}

	override void OnExecuteServer( ActionData action_data )
	{
		Object target_object = action_data.m_Target.GetObject();
		FalconATM ntarget = FalconATM.Cast(target_object);
		
		PlayerBase player = PlayerBase.Cast(action_data.m_Player);
		
		if (ntarget)
		{			
			GetRPCManager().SendRPC("FalconTraders", "openATMMenuC", new Param1<string>(""), true,  player.GetIdentity());
		}
		else
		{
			GetRPCManager().SendRPC("FalconTraders", "FTmessagePlayerC", new Param1<string>(TradersMessagesConsts.CANT_OPEN_ATM), true,  player.GetIdentity());
		}
	}
}