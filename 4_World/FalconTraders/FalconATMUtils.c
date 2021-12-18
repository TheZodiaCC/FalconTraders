class FalconATMUtils
{
	const static string atmsConfigDataPath = TradersConsts.ATMS_CONFIG_DATA_PATH;
	const static string atmsDataPath = TradersConsts.ATMS_DATA_PATH;
	const static string coinName = TradersConsts.COIN_ITEM_NAME;
	const static string accountsDataPath = TradersConsts.ATMS_ACCOUNTS_DATA_DIR_PATH;
	
	static ref array<string> getATMs() 
	{
		ref array<string> atms = new array<string>();
		
		JsonFileLoader<ref array<string>>.JsonLoadFile(atmsDataPath, atms);
		
		return atms;
	}
	
	static FalconATMConfig getATMsConfig() 
	{
		FalconATMConfig atmsConfig = new FalconATMConfig();
		
		JsonFileLoader<FalconATMConfig>.JsonLoadFile(atmsConfigDataPath, atmsConfig);
		
		return atmsConfig;
	}
	
	static PlayerBase getPlayerByIdentity(PlayerIdentity identity)
	{
	    int highBits, lowBits;
	
	    if (!GetGame().IsMultiplayer())
	        return PlayerBase.Cast(GetGame().GetPlayer());
	
	    if (identity == null)
	        return null;
	
	    GetGame().GetPlayerNetworkIDByIdentityID(identity.GetPlayerId(), lowBits, highBits);
			
	    return PlayerBase.Cast(GetGame().GetObjectByNetworkId(lowBits, highBits));
	}
	
	static void initATMs() 
	{
		array<string> atms = new array<string>();
		atms = getATMs();
		
		vector atmPos;
		
		FalconATMConfig config = getATMsConfig();
		
		if (config.ifSpawnATMs())
		{
			for (int i = 0; i < atms.Count(); i++)
			{
				atmPos = atms[i].ToVector();
				
				atmPos[1] = GetGame().SurfaceY(atmPos[0], atmPos[2]);
				
				FalconATM atm = FalconATM.Cast(GetGame().CreateObject("FalconATM", atmPos, false, false));
				
				atm.PlaceOnSurface();
			}
		}
	}
	
	static FalconATMAccount getAccountData(string playerID)
	{
		string dataPath = accountsDataPath + playerID + ".json";
		FalconATMAccount accountData = new FalconATMAccount();
		
		if (FileExist(dataPath))
		{
			JsonFileLoader<FalconATMAccount>.JsonLoadFile(dataPath, accountData);
		}
		
		else
		{
			accountData.init();
			JsonFileLoader<FalconATMAccount>.JsonSaveFile(dataPath, accountData);
		}
		
		return accountData;
	}
	
	static void dumpAccountData(string playerID, FalconATMAccount data)
	{
		string dataPath = accountsDataPath + playerID + ".json";
		
		if (FileExist(dataPath))
		{
			JsonFileLoader<FalconATMAccount>.JsonSaveFile(dataPath, data);
		}
	}
	
	static void depositMoney(string playerID, int moneyAmmount)
	{
		FalconATMAccount data = getAccountData(playerID);
		data.depositMoney(moneyAmmount);
		
		dumpAccountData(playerID, data);
	}
	
	static void withdrawMoney(string playerID, int moneyAmmount)
	{
		FalconATMAccount data = getAccountData(playerID);
		data.withdrawMoney(moneyAmmount);
		
		dumpAccountData(playerID, data);
	}
	
	private static array<string> getBodyParts()
	{
		array<string> bodyParts = new array<string>();
		
		bodyParts.Insert("Body");
		bodyParts.Insert("Back");
		bodyParts.Insert("Vest");
		bodyParts.Insert("Legs");
		
		return bodyParts;
	}
	
	private static array<string> getEmptyBodyParts()
	{
		array<string> bodyEmptyParts = new array<string>();
		
		bodyEmptyParts.Insert("Shoulder");
		bodyEmptyParts.Insert("Melee");
		bodyEmptyParts.Insert("Head");
		bodyEmptyParts.Insert("Headgear");
		bodyEmptyParts.Insert("Mask");
		bodyEmptyParts.Insert("Eyewear");
		bodyEmptyParts.Insert("Gloves");
		bodyEmptyParts.Insert("Feet");
		
		return bodyEmptyParts;
	}
	
	static int getPlayerMoneyBalance(PlayerBase player)
	{
		int moneyBalance = 0;
		ItemBase bodyPart;
		ItemBase item;
		array<string> bodyParts = new array<string>();
		
		bodyParts = getBodyParts();
		
		for (int i = 0; i < bodyParts.Count(); i++)
		{
			bodyPart =  ItemBase.Cast(player.GetInventory().FindAttachmentByName(bodyParts[i]));
		
			if (bodyPart)
			{
				for (int j = 0; j < bodyPart.GetInventory().GetCargo().GetItemCount(); j++)
				{
					item = ItemBase.Cast(bodyPart.GetInventory().GetCargo().GetItem(j));
					
					//Getting Goldcoin class name from var doesnt work, dunno why
					if (item.ClassName() == "Goldcoin")
					{
						moneyBalance += item.GetQuantity();
					}
				}
			}
		}
		
		return moneyBalance;
	}
	
	static ItemBase getItemFromInventoryC(PlayerBase player, string itemName)
	{
		ItemBase bodyPart;
		ItemBase item;
		array<string> bodyParts = new array<string>();
		array<string> emptyBodyParts = new array<string>();
		
		item = ItemBase.Cast(player.GetItemInHands());
		
		if (item)
		{			
			if (item.ClassName() == itemName)
			{
				return item;
			}
			else if (item.ClassName() == (itemName + "_Base"))
			{
				return item;
			}
		}
		
		emptyBodyParts = getEmptyBodyParts();
		
		for (int k = 0; k < emptyBodyParts.Count(); k++)
		{
			item = ItemBase.Cast(player.GetItemOnSlot(emptyBodyParts[k]));
		
			if (item)
			{
				if (item.ClassName() == itemName)
				{
					return item;
				}
				else if (item.ClassName() == (itemName + "_Base"))
				{
					return item;
				}
			}
		}
		
		bodyParts = getBodyParts();
		
		for (int i = 0; i < bodyParts.Count(); i++)
		{
			bodyPart =  ItemBase.Cast(player.GetInventory().FindAttachmentByName(bodyParts[i]));
		
			if (bodyPart)
			{
				for (int j = 0; j < bodyPart.GetInventory().GetCargo().GetItemCount(); j++)
				{				
					item = ItemBase.Cast(bodyPart.GetInventory().GetCargo().GetItem(j));
					
					if (item)
					{
						if (item.ClassName() == itemName)
						{
							return item;
						}
						else if (item.ClassName() == (itemName + "_Base"))
						{
							return item;
						}
					}
				}
			}
		}
		
		return null;
	}
	
	static ItemBase getItemFromInventory(PlayerBase player, string itemName)
	{
		ItemBase bodyPart;
		ItemBase item;
		array<string> bodyParts = new array<string>();
		array<string> emptyBodyParts = new array<string>();
		
		item = ItemBase.Cast(player.GetItemInHands());
		
		emptyBodyParts = getEmptyBodyParts();
		
		for (int k = 0; k < emptyBodyParts.Count(); k++)
		{
			item = ItemBase.Cast(player.GetItemOnSlot(emptyBodyParts[k]));
		
			if (item)
			{
				return item;
			}
		}
		
		bodyParts = getBodyParts();
		
		for (int i = 0; i < bodyParts.Count(); i++)
		{
			bodyPart =  ItemBase.Cast(player.GetInventory().FindAttachmentByName(bodyParts[i]));
		
			if (bodyPart)
			{
				for (int j = 0; j < bodyPart.GetInventory().GetCargo().GetItemCount(); j++)
				{				
					item = ItemBase.Cast(bodyPart.GetInventory().GetCargo().GetItem(j));
					
					if (item)
					{
						return item;
					}
				}
			}
		}
		
		return null;
	}
	
	private static array<ItemBase> getItemsFromInventory(PlayerBase player, string itemName)
	{
		ItemBase bodyPart;
		array<ItemBase> items = new array<ItemBase>();
		ItemBase item;
		array<string> bodyParts = new array<string>();
		
		bodyParts = getBodyParts();
		
		for (int i = 0; i < bodyParts.Count(); i++)
		{
			bodyPart =  ItemBase.Cast(player.GetInventory().FindAttachmentByName(bodyParts[i]));
		
			if (bodyPart)
			{
				for (int j = 0; j < bodyPart.GetInventory().GetCargo().GetItemCount(); j++)
				{
					item = ItemBase.Cast(bodyPart.GetInventory().GetCargo().GetItem(j));
					
					if (item.ClassName() == itemName)
					{
						items.Insert(item);
					}
				}
			}
		}
		
		return items;
	}
	
	private static void removeItemsFromInventory(PlayerBase player, string itemName)
	{
		ItemBase bodyPart;
		ItemBase item;
		array<string> bodyParts = new array<string>();
		
		bodyParts = getBodyParts();
		
		for (int i = 0; i < bodyParts.Count(); i++)
		{
			bodyPart =  ItemBase.Cast(player.GetInventory().FindAttachmentByName(bodyParts[i]));
			
			if (bodyPart)
			{
				for (int j = 0; j < bodyPart.GetInventory().GetCargo().GetItemCount(); j++)
				{
					item = ItemBase.Cast(bodyPart.GetInventory().GetCargo().GetItem(j));
					
					if (item.ClassName() == itemName)
					{
						item.Delete();
					}
				}
			}
		}
	}
	
	static void addMoney(PlayerBase player, int moneyAmount)
	{
		int maxMoneyQuantity = (ItemBase.Cast(GetGame().CreateObject(coinName, vector.Zero, true, false))).GetQuantityMax();
		int restMoney = moneyAmount;
		ItemBase money;
		
		if (restMoney < maxMoneyQuantity)
		{
			money = ItemBase.Cast(player.GetInventory().CreateInInventory(coinName));
			money.SetQuantity(restMoney);
		}
		else
		{
			while (restMoney > 0)
			{
				money = ItemBase.Cast(player.GetInventory().CreateInInventory(coinName));
				money.SetQuantity(restMoney);
				
				restMoney -= maxMoneyQuantity;
			}
		}
	}
	
	static void takeMoney(PlayerBase player, int moneyAmount)
	{
		array<ItemBase> moneyItems = new array<ItemBase>();
		moneyItems = getItemsFromInventory(player, coinName);
		int restMoney = moneyAmount;
		
		int maxMoneyQuantity = (ItemBase.Cast(GetGame().CreateObject(coinName, vector.Zero, true, false))).GetQuantityMax();
		int moneyQuantity;
		
		while (restMoney > 0)
		{
			for (int i = 0; i < moneyItems.Count(); i++)
			{
				moneyQuantity = moneyItems[i].GetQuantity();
				
				if (restMoney >= moneyQuantity)
				{
					moneyItems[i].SetQuantity(0);
					
					restMoney -= moneyQuantity; 
				}
				else
				{
					moneyItems[i].SetQuantity(moneyQuantity - restMoney);
					
					restMoney = 0;
				}
			}
		}
	}
}