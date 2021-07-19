class FalconSafeZoneUtils
{
	static vector safeZonePos = Vector(9997, 10, 1663);
	static int safeZoneRadius = 20;
	
	static ref FalconSafeZoneHelpers SafeZoneHelpers = new FalconSafeZoneHelpers();
	
	
	static void checkPlayersInSafezone(array<Man> players) {
		float playerSafeZoneDistance;
		
		PlayerBase playerInSafeZone;
		string playerID;
		
		foreach (Man player : players)
		{
			playerSafeZoneDistance = vector.Distance(safeZonePos, player.GetPosition());
			
			if (playerSafeZoneDistance <= safeZoneRadius) 
			{
				playerInSafeZone = PlayerBase.Cast(player);
				playerID = playerInSafeZone.GetIdentity().GetId();
				
				playerInSafeZone.setIsInSafeZone(true);
				playerInSafeZone.setHasGM(true);
				
				SafeZoneHelpers.turnOnMarks(playerID);
			}
			else
			{
				playerInSafeZone = PlayerBase.Cast(player);
				playerID = playerInSafeZone.GetIdentity().GetId();
				
				playerInSafeZone.setIsInSafeZone(false);
				playerInSafeZone.setHasGM(false);
				
				SafeZoneHelpers.turnOffMarks(playerID);
			}
		}
	}
}