#if defined _player_included
    #endinput
#endif
#define _player_included

enum PlayerData {
    pDBID,              // database id
    bool:pLoggedIn,
    pMoney,
    pLevel,
    pRep,
    pTotalRaces,
    pRacesWon,
    pRacesLost,
    Float:pTotalDistance,
    pPlaytime,          // in seconds
    pLoginTime          // gettime() when they logged in, for playtime calc
}

new Player[MAX_PLAYERS][PlayerData];

stock ResetPlayerData(playerid) {
    if(playerid < 0 || playerid >= MAX_PLAYERS) {
        return 0;
    }

    Player[playerid][pDBID] = 0;
    Player[playerid][pLoggedIn] = false;
    Player[playerid][pMoney] = 0;
    Player[playerid][pLevel] = 0;
    Player[playerid][pRep] = 0;
    Player[playerid][pTotalRaces] = 0;
    Player[playerid][pRacesWon] = 0;
    Player[playerid][pRacesLost] = 0;
    Player[playerid][pTotalDistance] = 0.0;
    Player[playerid][pPlaytime] = 0;
    Player[playerid][pLoginTime] = 0;

    return 1;
}

stock bool:IsPlayerLoggedIn(playerid) {
    if(playerid < 0 || playerid >= MAX_PLAYERS) {
        return false;
    }

    if(!IsPlayerConnected(playerid)) {
        return false;
    }

    return Player[playerid][pLoggedIn];
}

stock GetPlayerDBID(playerid) {
    if(playerid < 0 || playerid >= MAX_PLAYERS) {
        return 0;
    }

    return Player[playerid][pDBID];
}

stock SetPlayerLoggedIn(playerid, dbid) {
    if(playerid < 0 || playerid >= MAX_PLAYERS) {
        return 0;
    }

    Player[playerid][pDBID] = dbid;
    Player[playerid][pLoggedIn] = true;
    Player[playerid][pLoginTime] = gettime();

    return 1;
}

stock UpdatePlaytime(playerid) {
    if(playerid < 0 || playerid >= MAX_PLAYERS) {
        return 0;
    }

    if(!IsPlayerLoggedIn(playerid)) {
        return 0;
    }

    new sessionTime = gettime() - Player[playerid][pLoginTime];
    Player[playerid][pPlaytime] += sessionTime;

    return 1;
}

stock Player_OnConnect(playerid) {
    ResetPlayerData(playerid);
    Auth_CheckPlayerAccount(playerid);

    return 1;
}

stock Player_OnDisconnect(playerid) {
    if(IsPlayerLoggedIn(playerid)) {
        UpdatePlaytime(playerid);     // calculate session time
        SavePlayerData(playerid);     // save player/vehicle etc.. to database
        SaveVehicleData(playerid);
    }

    ResetPlayerData(playerid);
    return 1;
}
