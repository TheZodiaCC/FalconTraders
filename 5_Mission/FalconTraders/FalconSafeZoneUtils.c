class FalconSafeZoneUtils
{	
	const static string safeZonesDataPath = "$profile:/FValues/FSafeZones.json";
	const static string tradersDataPath = "$profile:/FValues/FTraders.json";
	const static string tradersStocksPath = "$profile:/FValues/FTradersStock.json";
	const static string traderItemsDetailsPath = "$profile:/FValues/FTradersPrices.json";
	const static string coinName = "Goldcoin";
	
	static ref array<ref FalconSafeZone> getSafeZones() 
	{
		ref array<ref FalconSafeZone> safeZones = new ref array<ref FalconSafeZone>();
		
		JsonFileLoader<ref array<ref FalconSafeZone>>.JsonLoadFile(safeZonesDataPath, safeZones);
		
		return safeZones;
	}
	
	static ref array<ref FalconTraderCharacterData> getTradersData() 
	{
		ref array<ref FalconTraderCharacterData> tradersData = new ref array<ref FalconTraderCharacterData>();
		
		JsonFileLoader<ref array<ref FalconTraderCharacterData>>.JsonLoadFile(tradersDataPath, tradersData);
		
		return tradersData;
	}
	
	static FTradersStock getTraderStocks() 
	{
		FTradersStock tradersStocks;
		
		JsonFileLoader<FTradersStock>.JsonLoadFile(tradersStocksPath, tradersStocks);
		
		return tradersStocks;
	}
	
	static ref array<ref FTraderItem> getTraderItemsDetails() {
		ref array<ref FTraderItem> traderItemsDetails = new ref array<ref FTraderItem>();
		
		JsonFileLoader<ref array<ref FTraderItem>>.JsonLoadFile(traderItemsDetailsPath, traderItemsDetails);
		
		return traderItemsDetails;
	}
	
	static FTraderItem getTraderItemDetailsByName(string itemName) 
	{
		ref array<ref FTraderItem> traderItemsDetails = new ref array<ref FTraderItem>();
		FTraderItem item;
		
		traderItemsDetails = getTraderItemsDetails();
		
		for (int i = 0; i < traderItemsDetails.Count(); i++)
		{
			if (traderItemsDetails[i].getName() == itemName)
			{
				item = traderItemsDetails[i];
			}
		}
		
		return item;
	}
	
	static array<string> processTradadersStocksItems(int traderId) 
	{
		array<string> items = new array<string>();
		FTradersStock traderStocks = getTraderStocks();
		
		FalconTraderCharacterData traderData = getTradersDataById(traderId);
		
		switch(traderData.getTraderName())
		{
			case "Hardware":
				items = traderStocks.getHardwareTradersItems();
				break;
	
			case "Medical":
				items = traderStocks.getMedicalTradersItems();
				break;
			
			case "Currency":
				items = traderStocks.getCurrencyTradersItems();
				break;
	
			default:
				break;
		}
		
		return items;
	}
	
	static FalconTraderCharacterData getTradersDataById(int traderId) {
		ref array<ref FalconTraderCharacterData> tradersData = new ref array<ref FalconTraderCharacterData>();
		
		tradersData = getTradersData();
		
		FalconTraderCharacterData traderData;
		
		for (int i = 0; i < tradersData.Count(); i++)
		{
			if (traderId == tradersData[i].getTraderId())
			{
				traderData = tradersData[i];
				break;
			}	
		}
		
		return traderData;
	}
	
	static void checkPlayersInSafezone(array<Man> players, array<ref FalconSafeZone> safeZones) 
	{
		float playerSafeZoneDistance;
		
		PlayerBase playerInSafeZone;
		
		Man player;
		FalconSafeZone safeZone;
		
		for (int i = 0; i < players.Count(); i++)
		{
			player = players.Get(i);
			
			for (int j = 0; j< safeZones.Count(); j++)
			{
				safeZone = safeZones.Get(j);
				
				playerSafeZoneDistance = vector.Distance(safeZone.getSafeZonePos().ToVector(), player.GetPosition());
				
				playerInSafeZone = PlayerBase.Cast(player);
				
				if (playerSafeZoneDistance <= safeZone.getSafeZoneRadius()) 
				{
					if (!playerInSafeZone.getIsInSafeZone())
					{
						playerInSafeZone.setIsInSafeZone(true);
						playerInSafeZone.setSafeZoneName(safeZone.getSafeZoneName());
					
						GetRPCManager().SendRPC( "FalconTraders", "switchSZMarkC", new Param1<bool>(true), true, playerInSafeZone.GetIdentity());
					}
				}
				else
				{
					if (playerInSafeZone.getIsInSafeZone()) 
					{
						playerInSafeZone.setIsInSafeZone(false);
						playerInSafeZone.setSafeZoneName("");						
			
						GetRPCManager().SendRPC( "FalconTraders", "switchSZMarkC", new Param1<bool>(false), true, playerInSafeZone.GetIdentity());
					}
				}
			}
		}
	}
	
	static void initSafezones() 
	{
		ref array<ref FalconTraderCharacterData> tradersData = new ref array<ref FalconTraderCharacterData>();
		
		tradersData = getTradersData();
		
		for (int i = 0; i < tradersData.Count(); i++)
		{
			FalconTrader trader = FalconTrader.Cast(GetGame().CreateObject(tradersData[i].getTraderType(), tradersData[i].getTraderSpawnPoint().ToVector(), false, false));
			
			trader.SetDirection(tradersData[i].getTraderDirection().ToVector());
			trader.SetAllowDamage(false);
			trader.setTraderId(tradersData[i].getTraderId());
			trader.setMaxHumanity(tradersData[i].getMaxHumanity());
			trader.setMinHumanity(tradersData[i].getMinHumanity());
			
			trader.GetInventory().CreateInInventory(tradersData[i].getTraderHead());
			trader.GetInventory().CreateInInventory(tradersData[i].getTraderBody());
			trader.GetInventory().CreateInInventory(tradersData[i].getTraderPants());
			trader.GetInventory().CreateInInventory(tradersData[i].getTraderBoots());
		}
	}
	
	static void clearSafeZones(array<ref FalconSafeZone> safeZones) 
	{
		array<Object> objects = new array<Object>();
		FalconSafeZone safeZone;
		int safeZoneRadius;
		
		for (int i = 0; i < safeZones.Count(); i++)
		{
			safeZone = safeZones[i];
			
			GetGame().GetObjectsAtPosition(safeZone.getSafeZonePos().ToVector(), safeZone.getSafeZoneRadius(), objects, null);
			
			for (int j = 0; j < objects.Count(); j++)
			{
				if (!objects[j].IsInherited(SurvivorBase))
				{
					GetGame().ObjectDelete(objects[j]);
				}
			}
		}
	}
	
	static void clearZombies(array<ref FalconSafeZone> safeZones) 
	{
		array<Object> objects = new array<Object>();
		FalconSafeZone safeZone;
		
		for (int i = 0; i < safeZones.Count(); i++)
		{
			safeZone = safeZones[i];
			
			GetGame().GetObjectsAtPosition(safeZone.getSafeZonePos().ToVector(), safeZone.getSafeZoneRadius(), objects, null);
			
			for (int j = 0; j < objects.Count(); j++)
			{
				if (objects[j].IsInherited(ZombieBase))
				{
					GetGame().ObjectDelete(objects[j]);
				}
			}
		}
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
	
	static bool checkIfTraderHasItem(int traderId, string itemName)
	{
		array<string> items = new array<string>();
			
		items = FalconSafeZoneUtils.processTradadersStocksItems(traderId);
		
		for (int i = 0; i < items.Count(); i++)
		{
			if (items[i] == itemName)
			{
				return true;
			}
		}
		
		return false;
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
	
	/*static bool checkIfPlayerHasItem(PlayerBase player, string itemName)
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
						return true;
					}
				}
			}
		}
		
		return false;
	}*/
	
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
		
		if (item)
		{
			if (processItem(item, itemName))
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
				if (processItem(item, itemName))
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
						if (processItem(item, itemName))
						{
							return item;
						}
					}
				}
			}
		}
		
		return null;
	}
	
	private static bool processItem(ItemBase item, string itemName)
	{
		string newItemName;
		
		if (checkIfWeapon(itemName))
		{
			newItemName = itemName + "_Base";	
		}
		else
		{
			newItemName = itemName;
		}
		
		if (item.ClassName() == newItemName)
		{
			return true;
		}
		else 
		{
			return false;
		}
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
	
	static void addMoney(PlayerBase player, int sellPrice)
	{
		int maxMoneyQuantity = (ItemBase.Cast(GetGame().CreateObject(coinName, vector.Zero, true, false))).GetQuantityMax();
		int restMoney = sellPrice;
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
	
	static void takeMoney(PlayerBase player, int buyPrice)
	{
		array<ItemBase> moneyItems = new array<ItemBase>();
		moneyItems = getItemsFromInventory(player, coinName);
		int restMoney = buyPrice;
		
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
	
	private static bool checkIfWeapon(string itemName)
	{
		FTradersStock stocks = getTraderStocks();
		
		array<string> weaponNames = new array<string>();
		
		weaponNames = stocks.getWeaponsNames();
		
		for (int i = 0; i < weaponNames.Count(); i++)
		{
			if (itemName == weaponNames[i])
			{
				return true;
			}
		}
		
		return false;
	}
}