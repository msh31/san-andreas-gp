#if defined _database_included
    #endinput
#endif
#define _database_included

new MySQL:g_SQL;

Database_Connect() {
    g_SQL = mysql_connect(MYSQL_HOST, MYSQL_USER, MYSQL_PASS, MYSQL_DB);

    if(mysql_errno(g_SQL) != 0) {
        print("[MySQL] Failed to connect to database!");
        return 0;
    }
    print("[MySQL] Successfully connected to database!");
    return 1;
}

Database_Disconnect() {
    mysql_close(g_SQL);
}

stock MySQL:Database_GetHandle() {
    return g_SQL;
}
