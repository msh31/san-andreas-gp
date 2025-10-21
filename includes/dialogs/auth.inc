#if defined _auth_included
    #endinput
#endif
#define _auth_included

#define STARTING_MONEY 5000
#define STARTING_LEVEL 1

stock Auth_OnConnect(playerid) {
    Auth_CheckPlayerAccount(playerid);

    return 1;
}

stock ShowRegisterDialog(playerid) {
    ShowPlayerDialog(
        playerid,
        DIALOG_REGISTER,
        DIALOG_STYLE_PASSWORD,
        "Register Account",
        "Welcome to San Andreas GP!\n\nThis account is not registered.\nPlease enter a password to create your account:",
        "Register",
        "Quit"
    );
}

stock ShowLoginDialog(playerid, const reason[] = "") {
    new dialog_text[256];

    if(strlen(reason) > 0) {
        format(dialog_text, sizeof(dialog_text),
            "Welcome back to San Andreas GP!\n\n{FF0000}%s{FFFFFF}\n\nPlease enter your password to login:",
            reason
        );
    } else {
        format(dialog_text, sizeof(dialog_text),
            "Welcome back to San Andreas GP!\n\nPlease enter your password to login:"
        );
    }

    ShowPlayerDialog(
        playerid,
        DIALOG_LOGIN,
        DIALOG_STYLE_PASSWORD,
        "Login to Account",
        dialog_text,
        "Login",
        "Quit"
    );
}

stock Auth_CheckPlayerAccount(playerid) {
    new query[128], name[MAX_PLAYER_NAME];
    GetPlayerName(playerid, name, sizeof(name));

    mysql_format(Database_GetHandle(), query, sizeof(query),
        "SELECT `id` FROM `players` WHERE `name` = '%e'", name);

    mysql_tquery(Database_GetHandle(), query, "CheckPlayerAccount", "d", playerid);
}

forward CheckPlayerAccount(playerid);
public CheckPlayerAccount(playerid) {
    if(!IsPlayerConnected(playerid)) {
        return 0;
    }

    if(cache_num_rows() > 0) {
        ShowLoginDialog(playerid);
    } else {
        ShowRegisterDialog(playerid);
    }

    return 1;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {
    if(!response) {
        Kick(playerid);
        return 1;
    }

    switch(dialogid) {
        case DIALOG_REGISTER: {
            if(strlen(inputtext) < 6) {
                SendClientMessage(playerid, COLOR_ERROR, "Password must be at least 6 characters!");
                ShowRegisterDialog(playerid);
                return 1;
            }

            bcrypt_hash(playerid, "OnPasswordHashed", inputtext, BCRYPT_COST);
        }
        case DIALOG_LOGIN: {
            new query[256], name[MAX_PLAYER_NAME];
            GetPlayerName(playerid, name, sizeof(name));

            mysql_format(Database_GetHandle(), query, sizeof(query),
                "SELECT `id`, `password` FROM `players` WHERE `name` = '%e'", name);

            mysql_tquery(Database_GetHandle(), query, "OnPasswordLoad", "ds", playerid, inputtext);
        }
    }

    return 1;
}

forward OnPasswordHashed(playerid);
public OnPasswordHashed(playerid) {
    if(!IsPlayerConnected(playerid)) {
        return 0;
    }

    new hash[BCRYPT_HASH_LENGTH];
    bcrypt_get_hash(hash);

    new query[512], name[MAX_PLAYER_NAME];
    GetPlayerName(playerid, name, sizeof(name));

    mysql_format(Database_GetHandle(), query, sizeof(query),
        "INSERT INTO `players` (`name`, `password`, `money`, `level`) VALUES ('%e', '%e', %d, %d)",
        name, hash, STARTING_MONEY, STARTING_LEVEL
    );

    mysql_tquery(Database_GetHandle(), query, "OnPlayerRegistered", "d", playerid);

    return 1;
}

forward OnPasswordChecked(playerid, bool:success);
public OnPasswordChecked(playerid, bool:success) {
    if(!IsPlayerConnected(playerid)) {
        return 0;
    }

    if(success) {
        //LoadPlayerData(playerid);
    } else {
        SendClientMessage(playerid, COLOR_ERROR, "Incorrect password!");
        ShowLoginDialog(playerid, "Incorrect password!");
    }

    return 1;
}

forward OnPlayerRegistered(playerid);
public OnPlayerRegistered(playerid) {
    if(!IsPlayerConnected(playerid)) {
        return 0;
    }

    new dbid = cache_insert_id();
    SetPlayerLoggedIn(playerid, dbid);

    Player[playerid][pMoney] = STARTING_MONEY;
    Player[playerid][pLevel] = STARTING_LEVEL;
    Player[playerid][pBank] = 0;
    Player[playerid][pRep] = 0;
    Player[playerid][pExp] = 0;
    Player[playerid][pTotalRaces] = 0;
    Player[playerid][pRacesWon] = 0;
    Player[playerid][pRacesLost] = 0;
    Player[playerid][pTotalDistance] = 0.0;

    SendClientMessage(playerid, COLOR_SUCCESS, "Account created successfully!");
    SpawnPlayer(playerid);
    return 1;
}

forward OnPasswordLoad(playerid, inputtext[]);
public OnPasswordLoad(playerid, inputtext[]) {
    if(!IsPlayerConnected(playerid)) {
        return 0;
    }

    if(cache_num_rows() == 0) {
        // account doesnt exist somehow
        Kick(playerid);
        return 0;
    }

    new hash[BCRYPT_HASH_LENGTH];
    cache_get_value_name(0, "password", hash);

    bcrypt_verify(playerid, "OnPasswordChecked", inputtext, hash);
    return 1;
}
