modded class MissionServer
{
	private ref array<Man> players = new array<Man>;
	private static int updateTick = 5;
	private int currentTime;
	static int nTime = 0;
	
	ref FalconSafeZoneHelpers SafeZoneHelpers;
	
	
	void MissionServer()
	{
		 SafeZoneHelpers = new FalconSafeZoneHelpers();
	}
	
	override void OnInit()
	{
		super.OnInit();
	}
	
	override void TickScheduler( float timeslice )
	{	
		super.TickScheduler( timeslice );
		//Future use for spawning missions etc.
		
		currentTime = GetGame().GetTime() * 0.001;
		
		if(currentTime >= nTime + updateTick)
		{
			GetGame().GetPlayers(players);
			
			FalconSafeZoneUtils.checkPlayersInSafezone(players);
			
			nTime = currentTime;
		}
	}
}