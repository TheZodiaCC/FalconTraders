modded class PlayerBase
{
	private bool isInSafeZone = false;
	private bool hasGM = false;
		
	bool isInSafeZone() {
		return isInSafeZone;
	}
	
	void setIsInSafeZone(bool value) {
		isInSafeZone = value;
	}
	
	void setHasGM(bool value) {
		hasGM = value;
		
		SetAllowDamage(!value);
	}
	
	bool ifHasGM() {
		return hasGM;
	}
}