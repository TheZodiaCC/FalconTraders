modded class MissionGameplay {

	private PlayerBase player;
	private ref SafeZoneMark sZMark = new SafeZoneMark();
	private ref FalconSafeZoneHelpers SafeZoneHelpers;
	private static int updateTick = 5;
	private int currentTime;
	static int nTime = 0;
	
	
	void MissionGameplay() {
		SafeZoneHelpers = new FalconSafeZoneHelpers();
	}
	
	override void TickScheduler( float timeslice )
	{	
		super.TickScheduler( timeslice );
		
		currentTime = GetGame().GetTime() * 0.001;
	
		if(currentTime >= nTime + updateTick)
		{		
			player = PlayerBase.Cast(GetGame().GetPlayer());
			
			if (player) {
				Print(player.isInSafeZone());
			
				if (player.isInSafeZone())
				{
					sZMark.showMark();
				}
				else
				{
					sZMark.hideMark();
				}
				
				nTime = currentTime;
			}
		}
	}
}