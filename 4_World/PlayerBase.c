modded class PlayerBase
{
	private bool isInSafeZone = false;
	private bool hasGM = false;
		
	bool getIsInSafeZone() {
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
	
	override bool CanBeRestrained() {
		if (getIsInSafeZone())
		{
			return false;
		}

		return super.CanBeRestrained();
	}
}