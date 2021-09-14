class HumanityHelpers
{
	const static string logsRoot = "$profile:/FH/";
	
	private static FT_HumanityData loadPlayerHumanityData(string playerID)
	{
		string playerJsonPath = logsRoot + playerID + ".json";
		
		if (FileExist(playerJsonPath))
		{
			FT_HumanityData playerHumanityData = new FT_HumanityData();
			
			JsonFileLoader<FT_HumanityData>.JsonLoadFile(playerJsonPath, playerHumanityData);
			
			return playerHumanityData;
		}	
		
		return null;
	}
	
	static bool checkIfPlayerHasEnoughtHumanity(string playerId, FalconTrader trader)
	{
		FT_HumanityData humanityData = loadPlayerHumanityData(playerId);
		
		if (humanityData)
		{
			int playerHumanity = humanityData.getHumanity();
			
			int traderMinHumanity = trader.getMinHumanity();
			int traderMaxHumanity = trader.getMaxHumanity();
			
			return playerHumanity.InRange(traderMinHumanity, traderMaxHumanity);
		}
		else
		{
			return false;
		}
	}
	
	static string getHumanityMessage(string playerId, FalconTrader trader)
	{
		FT_HumanityData humanityData = loadPlayerHumanityData(playerId);
		string message = "";
		
		if (humanityData)
		{
			int playerHumanity = humanityData.getHumanity();
			
			int traderMinHumanity = trader.getMinHumanity();
			int traderMaxHumanity = trader.getMaxHumanity();
			
			if (playerHumanity < traderMinHumanity)
			{
				message = "Your humanity is too low, trader requires at least: " + traderMinHumanity;
			}
			
			else if (playerHumanity > traderMaxHumanity)
			{
				message = "Your humanity is too high, trader requires at least: " + traderMaxHumanity;
			}
		}
		
		return message;
	}
}