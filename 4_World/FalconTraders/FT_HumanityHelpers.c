class FT_HumanityHelpers
{
	static bool checkIfPlayerHasEnoughtHumanity(string playerId, FalconTrader trader)
	{
		#ifdef FALCON_HEROES
			PlayerHumanityValues humanityData = FalconHeroesLogger.loadPlayerHumanityData(playerId);
			
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
		#else
			return true;
		#endif
	}
	
	static string getHumanityMessage(string playerId, FalconTrader trader)
	{
		string message = "";
		
		#ifdef FALCON_HEROES
			PlayerHumanityValues humanityData = FalconHeroesLogger.loadPlayerHumanityData(playerId);
			
			if (humanityData)
			{
				int playerHumanity = humanityData.getHumanity();
				
				int traderMinHumanity = trader.getMinHumanity();
				int traderMaxHumanity = trader.getMaxHumanity();
				
				if (playerHumanity < traderMinHumanity)
				{
					message = TradersMessagesConsts.HUMANITY_TO_LOW + traderMinHumanity;
				}
				
				else if (playerHumanity > traderMaxHumanity)
				{
					message = TradersMessagesConsts.HUMANITY_TO_HIGH + traderMaxHumanity;
				}
			}
		#endif
		
		return message;
	}
}