class TraderMenuBack
{
	void TraderMenuBack()
	{
		GetRPCManager().AddRPC( "FalconTraders", "getTraderNameS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTraders", "getTraderItemsS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTraders", "getTraderItemDetailsS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTraders", "getMoneyBalanceS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTraders", "sellItemS", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTraders", "buyItemS", this, SingeplayerExecutionType.Server );
	}
	
	private void getTraderNameS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<int> data;
		
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {
			if (data.param1)
			{
				int traderId = data.param1;
				
				FalconTraderCharacterData traderData = FalconSafeZoneUtils.getTradersDataById(traderId);
			
				GetRPCManager().SendRPC( "FalconTraders", "getTraderNameC", new Param1<string>(traderData.getTraderName()), true, sender );
			}	
       	 }
    }
	
	void getTraderName(int traderId) {		
		GetRPCManager().SendRPC( "FalconTraders", "getTraderNameS", new Param1<int>(traderId) );
	}
	
	private void getTraderItemsS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<int> data;
		
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {	
			if (data.param1)
			{
				int traderId = data.param1;
				
				array<string> items = new array<string>();
			
				items = FalconSafeZoneUtils.processTradadersStocksItems(traderId);
			
				GetRPCManager().SendRPC( "FalconTraders", "getTraderItemsC", new Param1<array<string>>(items), true, sender );
			}
       	 }
    }
	
	void getTraderItems(int traderId) {		
		GetRPCManager().SendRPC( "FalconTraders", "getTraderItemsS", new Param1<int>(traderId) );
	}
	
	private void getTraderItemDetailsS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<string> data;
		
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {	
			if (data.param1)
			{
				FTraderItem itemDetails;
				
				itemDetails = FalconSafeZoneUtils.getTraderItemDetailsByName(data.param1);
				
				GetRPCManager().SendRPC( "FalconTraders", "getTraderItemDetailsC", new Param1<FTraderItem>(itemDetails), true, sender );
			}
       	 }
    }
	
	void getTraderItemDetails(string itemName) {		
		GetRPCManager().SendRPC( "FalconTraders", "getTraderItemDetailsS", new Param1<string>(itemName) );
	}
	
	private void getMoneyBalanceS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<string> data;
		
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {	
			PlayerBase player = FalconSafeZoneUtils.getPlayerByIdentity(sender);
		
			int moneyBalance = FalconSafeZoneUtils.getPlayerMoneyBalance(player);
			
			GetRPCManager().SendRPC( "FalconTraders", "getMoneyBalanceC", new Param1<int>(moneyBalance), true, sender );
       	 }
    }
	
	void getMoneyBalance() {		
		GetRPCManager().SendRPC( "FalconTraders", "getMoneyBalanceS", new Param1<string>("") );
	}
	
	private void sellItemS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<string> data;
		
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {	
			if (data.param1 != "")
			{
				string itemName = data.param1;
				PlayerBase player = FalconSafeZoneUtils.getPlayerByIdentity(sender);
				
				ItemBase item = FalconSafeZoneUtils.getItemFromInventory(player, itemName);
				
				if (item)
				{
					if (!item.IsRuined())
					{
						FTraderItem traderItem = FalconSafeZoneUtils.getTraderItemDetailsByName(itemName);
						int sellPrice = traderItem.getSellPrice();
						
						GetGame().ObjectDelete(item);
						
						item = null;
						
						if (item == null)
						{
							FalconSafeZoneUtils.addMoney(player, sellPrice);
						}
					}
					else
					{
						GetRPCManager().SendRPC("FalconTraders", "FTmessagePlayerC", new Param1<string>("Can't sell ruined item"), true,  player.GetIdentity());
					}
				}
				else
				{
					GetRPCManager().SendRPC("FalconTraders", "FTmessagePlayerC", new Param1<string>("Can't sell item that is not in your inventory"), true,  player.GetIdentity());
				}
			}
       	}
    }
	
	void sellItem(string itemName) {		
		GetRPCManager().SendRPC( "FalconTraders", "sellItemS", new Param1<string>(itemName) );
	}
	
	private void buyItemS( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1<string> data;
		
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Server ) {	
			if (data.param1 != "")
			{
				string itemName = data.param1;
				PlayerBase player = FalconSafeZoneUtils.getPlayerByIdentity(sender);
				
				FTraderItem traderItem = FalconSafeZoneUtils.getTraderItemDetailsByName(itemName);
				int buyPrice = traderItem.getBuyPrice();
				
				if (FalconSafeZoneUtils.getPlayerMoneyBalance(player) >= buyPrice)
				{
					ItemBase item = ItemBase.Cast(player.GetInventory().CreateInInventory(itemName));
					
					if (item)
					{
						FalconSafeZoneUtils.takeMoney(player, buyPrice);
					}
				}
				else
				{
					GetRPCManager().SendRPC("FalconTraders", "FTmessagePlayerC", new Param1<string>("You don't have enought money to buy this item"), true,  player.GetIdentity());
				}
			}
       	}
    }
	
	void buyItem(string itemName) {		
		GetRPCManager().SendRPC( "FalconTraders", "buyItemS", new Param1<string>(itemName) );
	}
}