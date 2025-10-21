#if defined _auth_included
    #endinput
#endif
#define _auth_included

stock Auth_OnConnect(playerid) {
    ShowRegisterDialog(playerid);

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
