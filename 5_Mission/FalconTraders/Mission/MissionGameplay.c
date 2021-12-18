modded class MissionGameplay {

	private ref SafeZoneMark sZMark = new SafeZoneMark();
	ref TraderMenu traderMenu;
	ref ATMMenu atmMenu;
	
	
	void MissionGameplay() {
		GetRPCManager().AddRPC( "FalconTraders", "openTradeMenuC", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTraders", "switchSZMarkC", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTraders", "FTmessagePlayerC", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTraders", "openATMMenuC", this, SingeplayerExecutionType.Server );
	}
	
	private void FTmessagePlayerC( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<string> data;
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Client ) 
		{
			string message = data.param1;
			
			if (message)
			{
				string finalMessage = "[FalconTraders]: " + message;
			
				GetGame().Chat(finalMessage, "colorAction");
			}
       	}
    }
	
	private void openTradeMenuC(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		Param1<TraderMenuInitPackage> data;
		
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Client ) {
			if (data.param1)
			{
				TraderMenuInitPackage package = data.param1;
				
				if (traderMenu) 
				{						
					if (!traderMenu.isMenuOpened()) 
					{
						traderMenu.setTraderId(package.traderId);
						traderMenu.setSafeZoneName(package.safeZoneName);
						
	                    openTraderMenu();
	               	}
            	} 
				else if (!traderMenu) 
				{
					traderMenu = TraderMenu.Cast(GetUIManager().EnterScriptedMenu(2138142, null));
					
					traderMenu.setTraderId(package.traderId);
					traderMenu.setSafeZoneName(package.safeZoneName);
					
	                openTraderMenu();
	            }
			}
        }
	}
	
	private void openATMMenuC(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		Param1<string> data;
		
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Client ) {
			if (atmMenu) 
			{						
				if (!atmMenu.isMenuOpened()) 
				{
                    openATMMenu();
               	}
           	} 
			else if (!atmMenu) 
			{
				atmMenu = ATMMenu.Cast(GetUIManager().EnterScriptedMenu(1214649, null));
				
                openATMMenu();
            }
        }
	}
	
	private void switchSZMarkC( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<bool> data;
        if ( !ctx.Read( data ) ) return;
        
		
        if( type == CallType.Client ) {
			PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());

			if (data.param1)
			{
				//player.setIsInSafeZone(true);
				sZMark.showMark();
			}
			else
			{
				//player.setIsInSafeZone(false);
				sZMark.hideMark();
			}
        }
    }
	
	override void OnKeyPress(int key)
    {
        super.OnKeyPress(key);
		if (key == KeyCode.KC_ESCAPE) 
		{
			if (traderMenu) 
			{
                if (traderMenu.isMenuOpened()) 
				{
                    closeTraderMenu();
                } 
            } 
			
			if (atmMenu)
			{
				if (atmMenu.isMenuOpened())
				{
					closeATMMenu();
				}
			}
		}
	}
	
	private void openTraderMenu()
	{
		GetGame().GetUIManager().ShowScriptedMenu(traderMenu, NULL);
        traderMenu.setMenuOpened(true);
	}
	
	private void closeTraderMenu()
	{
		traderMenu.setMenuOpened(false);
        GetGame().GetUIManager().HideScriptedMenu(traderMenu);
	}
	
	private void openATMMenu()
	{
		GetGame().GetUIManager().ShowScriptedMenu(atmMenu, NULL);
        atmMenu.setMenuOpened(true);
	}
	
	private void closeATMMenu()
	{
		atmMenu.setMenuOpened(false);
        GetGame().GetUIManager().HideScriptedMenu(atmMenu);
	}
}