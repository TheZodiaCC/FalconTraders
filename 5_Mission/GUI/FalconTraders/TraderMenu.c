class TraderMenu extends UIScriptedMenu
{
	private Widget widgetRoot;
	
	private bool isInitialized;
    private bool isMenuOpen;
	
	private int traderId;
	private string safeZoneName;
	private string currentItemName;
	
	private TextWidget traderNameTEXT;
	private TextWidget safeZoneNameTEXT;
	private TextWidget moneyBalanceTEXT;
	
	private TextWidget currentItemTEXT;
	private TextWidget buyForTEXT;
	private TextWidget sellForTEXT; 
	
	private TextListboxWidget traderItemsLIST;
	private ItemPreviewWidget itemPreviewWIDGET;
	
	private ButtonWidget buyBUTTON;
	private ButtonWidget sellBUTTON;
	
	private ref Timer buttonsTimer = new Timer(CALL_CATEGORY_SYSTEM);

	ref TraderMenuBack traderMenuBack;
	
	//Constructor
	void TraderMenu() {	
		traderMenuBack = new ref TraderMenuBack();
		
		GetRPCManager().AddRPC( "FalconTraders", "getTraderNameC", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTraders", "getTraderItemsC", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTraders", "getTraderItemDetailsC", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTraders", "getMoneyBalanceC", this, SingeplayerExecutionType.Server );
	}
	
	//Deconstructor
	void ~TraderMenu() {
        PPEffects.SetBlurMenu(0);
        GetGame().GetUIManager().Back();
        g_Game.GetUIManager().ShowCursor(true);
        g_Game.GetUIManager().ShowUICursor(false);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetMission().PlayerControlEnable(false);
        GetGame().GetMission().GetHud().Show( true );

		delete traderMenuBack;
		
        if ( widgetRoot )
        	widgetRoot.Unlink();
    }
	
	override Widget Init() {
		if (!isInitialized) {
			widgetRoot = GetGame().GetWorkspace().CreateWidgets("FalconTraders/GUI/Layouts/TraderMenu.layout");
			
			traderNameTEXT = TextWidget.Cast(widgetRoot.FindAnyWidget("TraderNameTEXT"));
			safeZoneNameTEXT = TextWidget.Cast(widgetRoot.FindAnyWidget("SafeZoneNameTEXT"));
			moneyBalanceTEXT = TextWidget.Cast(widgetRoot.FindAnyWidget("MoneyBalanceTEXT"));
			
			currentItemTEXT = TextWidget.Cast(widgetRoot.FindAnyWidget("CurrentItemTEXT"));
			buyForTEXT = TextWidget.Cast(widgetRoot.FindAnyWidget("BuyForTEXT"));
			sellForTEXT = TextWidget.Cast(widgetRoot.FindAnyWidget("SellForTEXT"));
			
			traderItemsLIST = TextListboxWidget.Cast(widgetRoot.FindAnyWidget("TraderItemsLIST"));
			itemPreviewWIDGET = ItemPreviewWidget.Cast(widgetRoot.FindAnyWidget("ItemPreviewWIDGET"));
			
			buyBUTTON = ButtonWidget.Cast(widgetRoot.FindAnyWidget("BuyBUTTON")); 
			sellBUTTON = ButtonWidget.Cast(widgetRoot.FindAnyWidget("SellBUTTON")); 
			
			WidgetEventHandler.GetInstance().RegisterOnClick( traderItemsLIST, this, "selectItem" );
			WidgetEventHandler.GetInstance().RegisterOnClick( buyBUTTON, this, "buyItem" );
			WidgetEventHandler.GetInstance().RegisterOnClick( sellBUTTON, this, "sellItem" );
			
			widgetRoot.Show(false);
			
			isInitialized = true;
		}
		
		return widgetRoot;		
	}

	override void OnHide() {
		super.OnHide();
        PPEffects.SetBlurMenu(0);

        g_Game.GetUIManager().ShowCursor(true);
        g_Game.GetUIManager().ShowUICursor(false);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetMission().PlayerControlEnable(false);
        GetGame().GetMission().GetHud().Show( true );
		
		unlockControls();
	}
	
	override void OnShow() {
        super.OnShow();
        PPEffects.SetBlurMenu(0.5);
		lockControls();
		initWidgets();
    }
	
	private void initWidgets() {
		currentItemName = "";
		
		moneyBalanceTEXT.SetText("");
		traderNameTEXT.SetText("");
		safeZoneNameTEXT.SetText("");
		traderItemsLIST.ClearItems();
		itemPreviewWIDGET.Show(false);
		currentItemTEXT.SetText("");
		buyForTEXT.SetText("");
		sellForTEXT.SetText("");
		safeZoneNameTEXT.SetText(safeZoneName);
		
		getTraderItems(traderId);
		getTraderName(traderId);
		getSafeZoneName();
		getMoneyBalance();
		
		//markOwnedItems();
	}
	
	private void updateItems()
	{
		traderItemsLIST.ClearItems();
		getTraderItems(traderId);
		markOwnedItems();
	}
	
	void setTraderId(int value) {
        traderId = value;
    }
	
	int getTraderId() {
        return traderId;
    }
	
	void setSafeZoneName(string value) {
        safeZoneName = value;
    }
	
	string getSafeZoneName() {
        return safeZoneName;
    }
	
	void setMenuOpened(bool state) {
        isMenuOpen = state;
        if (isMenuOpen)
		{
			PPEffects.SetBlurMenu(0.5);
		}
        else
		{
			PPEffects.SetBlurMenu(0);
		}
    }
	
	bool isMenuOpened() {
        return isMenuOpen;
    }
	
	private void lockControls()
    {
        GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_ALL);
        GetGame().GetUIManager().ShowUICursor( true );
        GetGame().GetMission().GetHud().Show( false );
    }

    private void unlockControls()
    {
        GetGame().GetMission().PlayerControlEnable(false);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetUIManager().ShowUICursor( false );
        GetGame().GetMission().GetHud().Show( true );
    }
	
	private void markOwnedItems()
	{
		array<string> items = new array<string>();
		string tmp;
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		ItemBase item;
		
		for (int i = 0; i < traderItemsLIST.GetNumItems(); i++)
		{
			traderItemsLIST.GetItemText(i, 0, tmp);
			items.Insert(tmp);
		}
		
		for (int j = 0; j < items.Count(); j++)
		{
			item = FalconSafeZoneUtils.getItemFromInventoryC(player, items[j]);
			
			if (item)
			{
				traderItemsLIST.SetItemColor(j, 0, ARGB(255, 0, 255, 0));
			}
			else
			{
				traderItemsLIST.SetItemColor(j, 0, ARGB(255, 255, 255, 255));
			}
		}
	}
	
	private void getTraderNameC(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		
		Param1<string> data;
        if ( !ctx.Read(data)) return;
		
		if (type == CallType.Client)
        {
			if (data.param1)
			{
				traderNameTEXT.SetText(data.param1);
			}
		}
	}
	
	private void getTraderName(int traderId) {
		traderMenuBack.getTraderName(traderId);
	}
	
	private void getTraderItemsC(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		
		Param1<array<string>> data;
        if ( !ctx.Read(data)) return;
		
		if (type == CallType.Client)
        {
			if (data.param1)
			{
				array<string> items = new array<string>();
				
				items = data.param1;
				
				for (int i = 0; i < items.Count(); i++)
				{
					traderItemsLIST.AddItem(items[i], null, 0);
				}
				
				markOwnedItems();
			}
		}
	}
	
	private void getTraderItems(int traderId) {
		traderMenuBack.getTraderItems(traderId);
	}
	
	private void getTraderItemDetailsC(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		
		Param1<FTraderItem> data;
        if ( !ctx.Read(data)) return;
		
		if (type == CallType.Client)
        {
			if (data.param1)
			{
				FTraderItem item = data.param1;
				
				currentItemTEXT.SetText(item.getName());
				buyForTEXT.SetText(item.getBuyPrice().ToString());
				sellForTEXT.SetText(item.getSellPrice().ToString());
			}
		}
	}
	
	private void getTraderItemDetails(string itemName) {
		traderMenuBack.getTraderItemDetails(itemName);
	}
	
	private void selectItem() {
		//if (!buttonsTimer.IsRunning())
		//{
		int ind = traderItemsLIST.GetSelectedRow();
		string itemName;
		
		if (ind >= 0)
		{
			traderItemsLIST.GetItemText(ind, 0, itemName);
		
			EntityAI previewItem = EntityAI.Cast(GetGame().CreateObject(itemName, vector.Zero, true, false));
	
			if (previewItem)
			{
				itemPreviewWIDGET.SetItem(previewItem);
				itemPreviewWIDGET.SetModelPosition( Vector(0, 0, 0.5));
				itemPreviewWIDGET.SetModelOrientation(vector.Zero);
				itemPreviewWIDGET.SetView(itemPreviewWIDGET.GetItem().GetViewIndex());
				itemPreviewWIDGET.Show(true);
			} 
			else
			{
				itemPreviewWIDGET.Show(false);
			}
			
			getTraderItemDetails(itemName);
			
			currentItemName = itemName;
		}
			
			//startButtonsTimer();
		//}
	}
	
	private void getMoneyBalanceC(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		
		Param1<int> data;
        if ( !ctx.Read(data)) return;
		
		if (type == CallType.Client)
        {
			moneyBalanceTEXT.SetText(data.param1.ToString());
		}
	}
	
	private void getMoneyBalance() {
		traderMenuBack.getMoneyBalance();
	}
	
	private void buyItem() {
		if (!buttonsTimer.IsRunning())
		{
			traderMenuBack.buyItem(currentItemName);
		
			getMoneyBalance();
			updateItems();
			
			startButtonsTimer();
		}
	}
	
	private void sellItem() {
		if (!buttonsTimer.IsRunning())
		{
			traderMenuBack.sellItem(currentItemName);
		
			getMoneyBalance(); 
			updateItems();
			
			startButtonsTimer();
		}
	}
	
	void startButtonsTimer()
	{
		buttonsTimer.Run(1, null, "");
	}
}
	
	
