class FalconSafeZoneUtils
{
	static vector safeZonePos = Vector(9997, 10, 1663);
	static int safeZoneRadius = 20;
	
	
	static void checkPlayersInSafezone(array<Man> players) {
		float playerSafeZoneDistance;
		
		PlayerBase p;
		string playerID;
		
		ref FalconSafeZoneHelpers SafeZoneHelpers = new FalconSafeZoneHelpers();
		
		foreach (Man player : players)
		{
			playerSafeZoneDistance = vector.Distance(safeZonePos, player.GetPosition());
			
			if (playerSafeZoneDistance <= safeZoneRadius) 
			{
				p = PlayerBase.Cast(player);
				playerID = p.GetIdentity().GetId();
				
				p.setIsInSafeZone(true);
				p.setHasGM(true);
				
				SafeZoneHelpers.turnOnMarks(playerID);
			}
			else
			{
				p = PlayerBase.Cast(player);
				playerID = p.GetIdentity().GetId();
				
				p.setIsInSafeZone(false);
				p.setHasGM(false);
				
				SafeZoneHelpers.turnOffMarks(playerID);
			}
		}
	}
}