class ATMMenu extends UIScriptedMenu
{
	private Widget widgetRoot;
	
	private bool isInitialized;
    private bool isMenuOpen;

	private TextWidget yourAccountBalanceTEXT;
	private TextWidget moneyInInventoryTEXT;
	private TextWidget maxBankBalanceTEXT; 
	
	private EditBoxWidget moneyINPUT;
	
	private ButtonWidget withdrawBUTTON;
	private ButtonWidget depositBUTTON;
	
	private ref Timer buttonsTimer = new Timer(CALL_CATEGORY_SYSTEM);

	ref ATMMenuBack atmMenuBack;
	
	//Constructor
	void ATMMenu() {	
		atmMenuBack = new ref ATMMenuBack();
		
		GetRPCManager().AddRPC( "FalconTraders", "getMaxMoneyBalanceC", this, SingeplayerExecutionType.Server );
		GetRPCManager().AddRPC( "FalconTraders", "getYourAccountBalanceC", this, SingeplayerExecutionType.Server );
	}
	
	//Deconstructor
	void ~ATMMenu() {
        PPEffects.SetBlurMenu(0);
        GetGame().GetUIManager().Back();
        g_Game.GetUIManager().ShowCursor(true);
        g_Game.GetUIManager().ShowUICursor(false);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetMission().PlayerControlEnable(false);
        GetGame().GetMission().GetHud().Show( true );

		delete atmMenuBack;
		
        if ( widgetRoot )
        	widgetRoot.Unlink();
    }
	
	override Widget Init() {
		if (!isInitialized) {
			widgetRoot = GetGame().GetWorkspace().CreateWidgets("FalconTraders/GUI/Layouts/ATMMenu.layout");
			
			yourAccountBalanceTEXT = TextWidget.Cast(widgetRoot.FindAnyWidget("YourAccountBalanceTEXT"));
			moneyInInventoryTEXT = TextWidget.Cast(widgetRoot.FindAnyWidget("MoneyInInventoryTEXT"));
			maxBankBalanceTEXT = TextWidget.Cast(widgetRoot.FindAnyWidget("MaxBankBalanceTEXT"));
			
			withdrawBUTTON = ButtonWidget.Cast(widgetRoot.FindAnyWidget("WithdrawBUTTON")); 
			depositBUTTON = ButtonWidget.Cast(widgetRoot.FindAnyWidget("DepositBUTTON")); 
			
			moneyINPUT = EditBoxWidget.Cast(widgetRoot.FindAnyWidget("MoneyINPUT"));
			
			WidgetEventHandler.GetInstance().RegisterOnClick( withdrawBUTTON, this, "withdraw" );
			WidgetEventHandler.GetInstance().RegisterOnClick( depositBUTTON, this, "deposit" );
			
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
	
	private void initWidgets()
	 {
		yourAccountBalanceTEXT.SetText("");
		moneyInInventoryTEXT.SetText("");
		maxBankBalanceTEXT.SetText("");
		
		getMaxMoneyBalance();
		getYourAccountBalance();
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(getCurrentMoneyBalance,  500, false);
	}
	
	void setMaxMoneyBalance(int value) 
	{
        maxBankBalanceTEXT.SetText(value.ToString());
    }
	
	void setYourAccountBalance(int value) 
	{
        yourAccountBalanceTEXT.SetText(value.ToString());
    }
	
	void setMoneyInInventory(int value) 
	{
        moneyInInventoryTEXT.SetText(value.ToString());
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
	
	private void getAccountBalanceC(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
		
		Param1<int> data;
        if ( !ctx.Read(data)) return;
		
		if (type == CallType.Client)
        {
			setYourAccountBalance(data.param1);
		}
	}
	
	private void deposit() {
		if (!buttonsTimer.IsRunning())
		{
			startButtonsTimer();
			
			string moneyText = moneyINPUT.GetText();
					
			if (moneyText)
			{
				atmMenuBack.deposit(moneyText.ToInt());
				initWidgets();
			}
		}
	}
	
	private void withdraw() {
		if (!buttonsTimer.IsRunning())
		{
			startButtonsTimer();
			
			string moneyText = moneyINPUT.GetText();
		
			if (moneyText)
			{
				atmMenuBack.withdraw(moneyText.ToInt());
				initWidgets();
			}
		}
	}
	
	void startButtonsTimer()
	{
		if (!buttonsTimer.IsRunning())
		{
			buttonsTimer.Run(1, null, "");
		}
	}
	
	void getMaxMoneyBalanceC(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) 
	{
		Param1<int> data;
        if ( !ctx.Read(data)) return;
		
		if (type == CallType.Client)
        {
			setMaxMoneyBalance(data.param1);
		}
	}
	
	void getMaxMoneyBalance()
	{
		atmMenuBack.getMaxMoneyBalance();
	}
	
	
	void getYourAccountBalanceC(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) 
	{
		Param1<int> data;
        if ( !ctx.Read(data)) return;
		
		if (type == CallType.Client)
        {
			setYourAccountBalance(data.param1);
		}
	}
	
	void getYourAccountBalance()
	{
		atmMenuBack.getYourAccountBalance();
	}
	
	void getCurrentMoneyBalance()
	{
		int money = FalconATMUtils.getPlayerMoneyBalance(PlayerBase.Cast(GetGame().GetPlayer()));
		
		setMoneyInInventory(money);
	}
}