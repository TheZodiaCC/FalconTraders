class FTradersStock
{
	private ref array<string> weaponsNames = new ref array<string>();
	private ref array<string> hardwareTradersItems = new ref array<string>();
	private ref array<string> medicalTradersItems = new ref array<string>();
	private ref array<string> currencyTradersItems = new ref array<string>();
	private ref array<string> foodTradersItems = new ref array<string>();
	
	
	array<string> getWeaponsNames()
	{
		return weaponsNames;
	}
	
	array<string> getHardwareTradersItems()
	{
		return hardwareTradersItems;
	}
	
	array<string> getMedicalTradersItems()
	{
		return medicalTradersItems;
	}
	
	array<string> getCurrencyTradersItems()
	{
		return currencyTradersItems;
	}
	
	array<string> getFoodTradersItems()
	{
		return foodTradersItems;
	}
}