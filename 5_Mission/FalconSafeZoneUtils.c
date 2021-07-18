class FalconSafeZoneUtils
{
	static vector safeZonePos = Vector(9997, 10, 1663);
	static int safeZoneRadius = 20;
	
	static void checkPlayersInSafezone(array<Man> players) {
		float playerSafeZoneDistance;
		
		ref FalconSafeZoneHelpers SafeZoneHelpers = new FalconSafeZoneHelpers();
		
		foreach (Man player : players)
		{
			playerSafeZoneDistance = vector.Distance(safeZonePos, player.GetPosition());
			
			if (playerSafeZoneDistance <= safeZoneRadius) 
			{
				Print(player.GetIdentity().GetName() + " " + playerSafeZoneDistance);
				
				PlayerBase.Cast(player).setIsInSafeZone(true);
				
				SafeZoneHelpers.turnOnMarks();
			}
			else
			{
				PlayerBase.Cast(player).setIsInSafeZone(false);
				
				SafeZoneHelpers.turnOffMarks();
			}
		}
	}
}