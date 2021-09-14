modded class PlayerBase
{
	private bool isInSafeZone = false;
	private bool hasGM = false;
	private string safeZoneName;
	
	void PlayerBase()
	{
		//Used in actions conditions
		RegisterNetSyncVariableBool("isInSafeZone");
	}
	
	bool getIsInSafeZone() {
		return isInSafeZone;
	}
	
	void setIsInSafeZone(bool value) {
		isInSafeZone = value;
		
		if (!hasGM)
		{
			SetAllowDamage(!value);
		}
	}
	
	void setSafeZoneName(string name) {
		safeZoneName = name;
	}
	
	string getSafeZoneName() {
		return safeZoneName;
	}
	
	override bool CanBeRestrained() {
		if (getIsInSafeZone())
		{
			return false;
		}

		return super.CanBeRestrained();
	}
}