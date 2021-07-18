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
				//Print(player.GetIdentity().GetName() + " " + playerSafeZoneDistance);
				
				p = PlayerBase.Cast(player);
				playerID = p.GetIdentity().GetId();
				
				p.setIsInSafeZone(true);
				
				SafeZoneHelpers.turnOnMarks(playerID);
			}
			else
			{
				p = PlayerBase.Cast(player);
				playerID = p.GetIdentity().GetId();
				
				p.setIsInSafeZone(false);
				
				SafeZoneHelpers.turnOffMarks(playerID);
			}
		}
	}
}