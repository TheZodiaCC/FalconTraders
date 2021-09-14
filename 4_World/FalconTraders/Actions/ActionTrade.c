class ActionTrade: ActionInteractBase
{		
	void ActionTrade()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_HUDCursorIcon = CursorIcons.CloseHood;
	}
	
	override void CreateConditionComponents()  
	{
		m_ConditionTarget = new CCTMan(UAMaxDistances.DEFAULT);
		m_ConditionItem = new CCINone;
	}

	override string GetText()
	{
		return "Trade";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		FalconTrader targetTrader = FalconTrader.Cast(target.GetObject());
		
		if( targetTrader && targetTrader.IsAlive())
		{
			return true;
		}

		return false;
	}

	override void OnExecuteServer( ActionData action_data )
	{
		FalconTrader trader = FalconTrader.Cast( action_data.m_Target.GetObject() );
		PlayerBase player = action_data.m_Player;
		
		if (HumanityHelpers.checkIfPlayerHasEnoughtHumanity(player.GetIdentity().GetId(), trader))
		{
			TraderMenuInitPackage package = new TraderMenuInitPackage(trader.getTraderId(), player.getSafeZoneName());
		
			GetRPCManager().SendRPC("FalconTraders", "openTradeMenuC", new Param1<TraderMenuInitPackage>(package), true,  player.GetIdentity());
		}
		
		GetRPCManager().SendRPC("FalconTraders", "FTmessagePlayerC", new Param1<string>(HumanityHelpers.getHumanityMessage(player.GetIdentity().GetId(), trader)), true,  player.GetIdentity());
	}
	
	
	override void OnExecuteClient( ActionData action_data )
	{
		;
	}
}