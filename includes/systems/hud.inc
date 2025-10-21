#if defined _hud_included
    #endinput
#endif
#define _hud_included

new PlayerText:welcomeText[MAX_PLAYERS];

stock CreatePlayerHUD(playerid) {
    welcomeText[playerid] = CreatePlayerTextDraw(playerid, 200, 100, "Welcome to San Andreas GP!");

    PlayerTextDrawShow(playerid, welcomeText[playerid]);
    SetTimerEx("HideText", 10000, false, "i", playerid);
}

stock UpdatePlayerMoney(playerid) {
    // TODO
}

stock UpdatePlayerLevel(playerid) {
    // TODO
}

stock DestroyPlayerHUD(playerid) {
    PlayerTextDrawDestroy(playerid, welcomeText[playerid]);
}

forward HideText(playerid);
public HideText(playerid) {
    PlayerTextDrawHide(playerid, welcomeText[playerid]);
    return 1;
}
